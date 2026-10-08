#include "utils.hpp"

#include <stdexcept>
#include <random>
#include <thread>
#include <algorithm>
#include <cstddef>
#include <vector>
#include <string>
#include <utility>

vasyakin::Circle::Circle(double radius, double x, double y) noexcept:
  radius_(radius),
  x_(x),
  y_(y)
{}

bool vasyakin::Circle::contains(double dx, double dy) const noexcept
{
  return (dx - x_) * (dx - x_) + (dy - y_) * (dy - y_) <= radius_ * radius_;
}

double vasyakin::Circle::getMinX() const noexcept
{
  return x_ - radius_;
}

double vasyakin::Circle::getMinY() const noexcept
{
  return y_ - radius_;
}

double vasyakin::Circle::getMaxX() const noexcept
{
  return x_ + radius_;
}

double vasyakin::Circle::getMaxY() const noexcept
{
  return y_ + radius_;
}

vasyakin::Rectangle vasyakin::findRectangleRange(const std::vector< vasyakin::Circle >& circles)
{
  vasyakin::Rectangle rect = {circles[0].getMinX(), circles[0].getMinY(), circles[0].getMaxX(), circles[0].getMaxY()};

  for (size_t i = 1; i < circles.size(); ++i)
  {
    rect.min_x = std::min(rect.min_x, circles[i].getMinX());
    rect.min_y = std::min(rect.min_y, circles[i].getMinY());
    rect.max_x = std::max(rect.max_x, circles[i].getMaxX());
    rect.max_y = std::max(rect.max_y, circles[i].getMaxY());
  }

  return rect;
}

long long vasyakin::parseArgument(const char* arg, const std::string& param)
{
  size_t pos = 0;
  const long long value = std::stoll(arg, &pos);

  if (pos != std::string(arg).length())
  {
    throw std::invalid_argument("Invalid characters in " + param);
  }

  return value;
}

std::pair< long long, long long > vasyakin::calc(long long tries, long long seed, double min_x, double max_x,
    double min_y, double max_y, const std::vector< vasyakin::Circle >& circles)
{
  long long count_in_one_circle = 0;
  long long count_in_all_circles = 0;

  std::default_random_engine engine(static_cast< unsigned int >(seed));
  std::uniform_real_distribution< double > dist_x(min_x, max_x);
  std::uniform_real_distribution< double > dist_y(min_y, max_y);

  for (long long i = 0; i < tries; ++i)
  {
    const double x = dist_x(engine);
    const double y = dist_y(engine);

    bool in_any = false;
    bool in_all = true;

    for (size_t j = 0; j < circles.size(); ++j)
    {
      if (circles[j].contains(x, y))
      {
        in_any = true;
      }
      else
      {
        in_all = false;
      }
    }

    if (in_any)
    {
      ++count_in_one_circle;
    }

    if (in_all)
    {
      ++count_in_all_circles;
    }
  }

  return std::make_pair(count_in_one_circle, count_in_all_circles);
}

std::pair< double, double > vasyakin::area(long long threads, long long tries, long long seed,
    const std::vector< vasyakin::Circle >& circles, vasyakin::Rectangle rect)
{
  int local_tries = tries;

  const long long chunk = tries / threads;
  const long long remainder = tries % threads;

  std::vector< std::pair< long long, long long > > results(threads);

  std::vector< std::thread > thread_pool;
  thread_pool.reserve(threads);

  for (long long j = 0; j < threads; ++j)
  {
    const long long local_seed = seed + j;
    local_tries = (j == threads - 1) ? chunk + remainder : chunk;

    thread_pool.emplace_back(
        [&, j, local_tries, local_seed]()
        {
          results[j] = vasyakin::calc(local_tries, local_seed, rect.min_x, rect.max_x, rect.min_y, rect.max_y, circles);
        });
  }

  for (size_t i = 0; i < thread_pool.size(); ++i)
  {
    thread_pool[i].join();
  }

  long long total_union_hits = 0;
  long long total_intersect_hits = 0;

  for (size_t i = 0; i < results.size(); ++i)
  {
    total_union_hits += results[i].first;
    total_intersect_hits += results[i].second;
  }

  const double rect_area = (rect.max_x - rect.min_x) * (rect.max_y - rect.min_y);

  const double area_union = static_cast< double >(total_union_hits) / static_cast< double >(tries) * rect_area;
  const double area_intersect = static_cast< double >(total_intersect_hits) / static_cast< double >(tries) * rect_area;

  return std::make_pair(area_union, area_intersect);
}
