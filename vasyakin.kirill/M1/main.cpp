#include "utils.hpp"

#include <iostream>
#include <iomanip>
#include <limits>

int main(int argc, char** argv)
{
  constexpr int min_args = 3;
  constexpr int max_args = 4;

  constexpr int threads_idx = 1;
  constexpr int tries_idx = 2;
  constexpr int seed_idx = 3;

  constexpr int bad_exit = 1;
  constexpr int good_exit = 0;

  if (argc < min_args || argc > max_args)
  {
    std::cerr << "Too much" << '\n';
    return bad_exit;
  }

  long long threads = 0, tries = 0, seed = 0;

  try
  {
    threads = vasyakin::parseArgument(argv[threads_idx], "threads");
    tries = vasyakin::parseArgument(argv[tries_idx], "tries");

    if (argc == 4)
    {
      seed = vasyakin::parseArgument(argv[seed_idx], "seed");
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return bad_exit;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << "Number is out of range: " << e.what() << '\n';
    return bad_exit;
  }

  if (threads < 0 || tries <= 0 || seed < 0)
  {
    std::cerr << "threads, tries and seed must be positive" << '\n';
    return bad_exit;
  }

  threads = threads > 0 ? threads : 1;

  std::vector< vasyakin::Circle > circles;

  int r = 0, dopTaskParam = 0, x = 0, y = 0;
  while (std::cin >> r >> dopTaskParam >> x >> y)
  {
    circles.emplace_back(r, x, y);
  }

  if (!std::cin.eof())
  {
    std::cerr << "Error: cannot parse figure parameters" << '\n';
    return bad_exit;
  }

  if (circles.empty())
  {
    std::cerr << "Vector of circles is empty" << '\n';
    return bad_exit;
  }

  vasyakin::Rectangle rect = vasyakin::findRectangleRange(circles);

  try
  {
    auto pair = vasyakin::area(threads, tries, seed, circles, rect);

    double areaUnion = pair.first;
    double areaIntersect = pair.second;

    std::cout << std::setprecision(std::numeric_limits< double >::max_digits10);
    std::cout << areaUnion << " " << areaIntersect << '\n';
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return bad_exit;
  }

  return good_exit;
}
