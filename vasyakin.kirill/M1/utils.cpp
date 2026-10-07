#include "utils.hpp"

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