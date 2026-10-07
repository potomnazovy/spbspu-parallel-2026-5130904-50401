#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>

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
    double minX, minY, maxX, maxY;
  };

  Rectangle findRectangleRange(const std::vector< vasyakin::Circle >& circles);

  int parseArgument(const char* arg, const std::string& param);

  std::pair< int, int > calc(int tries, int seed,
    double minX, double maxX, double minY, double maxY, const std::vector< vasyakin::Circle >& circles);

  std::pair< double, double > area(int threads, int tries, int seed,
    const std::vector< vasyakin::Circle >& circles, Rectangle rect);
}

#endif
