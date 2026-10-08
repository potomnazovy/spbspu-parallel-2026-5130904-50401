#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <utility>

namespace vasyakin
{
  class Circle
  {
  public:
    Circle(double radius, double x, double y) noexcept;

    bool contains(double dx, double dy) const noexcept;

    double getMinX() const noexcept;
    double getMinY() const noexcept;
    double getMaxX() const noexcept;
    double getMaxY() const noexcept;

  private:
    double radius_;
    double x_, y_;
  };

  struct Rectangle
  {
    double min_x, min_y, max_x, max_y;
  };

  Rectangle findRectangleRange(const std::vector< vasyakin::Circle >& circles);

  long long parseArgument(const char* arg, const std::string& param);

  std::pair< long long, long long > calc(long long tries, long long seed, double min_x, double max_x, double min_y,
      double max_y, const std::vector< vasyakin::Circle >& circles);

  std::pair< double, double > area(long long threads, long long tries, long long seed,
      const std::vector< vasyakin::Circle >& circles, Rectangle rect);
}

#endif
