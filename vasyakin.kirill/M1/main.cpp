#include "utils.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <stdexcept>
#include <thread>

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

    if (argc == max_args)
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

  int r = 0, dop_task_param = 0, x = 0, y = 0;
  while (std::cin >> r >> dop_task_param >> x >> y)
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

  const vasyakin::Rectangle rect = vasyakin::findRectangleRange(circles);

  try
  {
    long long actual_threads = threads;

    const unsigned int hw_cores = std::thread::hardware_concurrency();
    long long max_threads = (hw_cores == 0) ? 12 : hw_cores;

    if (max_threads > 12)
    {
      max_threads = 12;
    }

    if (actual_threads > max_threads)
    {
      actual_threads = max_threads;
    }

    if (actual_threads > tries)
    {
      actual_threads = tries;
    }

    const auto pair = vasyakin::area(actual_threads, tries, seed, circles, rect);

    const double area_union = pair.first;
    const double area_intersect = pair.second;

    std::cout << std::setprecision(std::numeric_limits< double >::max_digits10);
    std::cout << area_union << " " << area_intersect << '\n';
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return bad_exit;
  }

  return good_exit;
}
