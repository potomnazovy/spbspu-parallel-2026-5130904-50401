#include "utils.hpp"

#include <iostream>
#include <iomanip>
#include <limits>

int main(int argc, char** argv)
{
  if (argc < 3 || argc > 4)
  {
    std::cerr << "Too much" << '\n';
    return 1;
  }

  long long threads = 0, tries = 0, seed = 0;

  try
  {
    threads = vasyakin::parseArgument(argv[1], "threads");
    tries = vasyakin::parseArgument(argv[2], "tries");

    if (argc == 4)
    {
      seed = vasyakin::parseArgument(argv[3], "seed");
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << "Number is out of range: " << e.what() << '\n';
    return 1;
  }

  if (threads < 0 || tries <= 0 || seed < 0)
  {
    std::cerr << "threads, tries and seed must be positive" << '\n';
    return 1;
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
    return 1;
  }

  if (circles.empty())
  {
    std::cerr << "Vector of circles is empty" << '\n';
    return 1;
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
    return 1;
  }

  return 0;
}
