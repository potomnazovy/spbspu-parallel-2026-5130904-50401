#include "utils.hpp"
#include <stdexcept>

vasyakin::Circle::Circle(double radius, double x, double y) noexcept:
  radius_(radius),
  x_(x),
  y_(y)
{}

bool vasyakin::Circle::contains(double dx, double dy) const noexcept
{
  return (dx - x_) * (dx - x_) + (dy - y_) * (dy - y_ ) <= radius_ * radius_;
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

vasyakin::Rectangle findRectangleRange(const std::vector< vasyakin::Circle >& circles)
{
  vasyakin::Rectangle rect =
  {
    circles[0].getMinX(), circles[0].getMinY(), circles[0].getMaxX(), circles[0].getMaxY()
  };

  for (size_t i = 1; i < circles.size(); ++i)
  {
    rect.minX = std::min(rect.minX, circles[i].getMinX());
    rect.minY = std::min(rect.minY, circles[i].getMinY());
    rect.maxX = std::max(rect.maxX, circles[i].getMaxX());
    rect.maxY = std::max(rect.maxY, circles[i].getMaxY());
  }

  return rect;
}

int parseArgument(const char* arg, const std::string& param)
{
  size_t pos = 0;
  int value = std::stoi(arg, &pos);

  if (pos != std::string(arg).length())
  {
    throw std::invalid_argument("Invalid characters in " + param);
  }

  return value;
}
