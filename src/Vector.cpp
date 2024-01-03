//
// Created by sl2-non on 20/11/2023.
//

#include "Vector.h"

Vector::Vector(float x_, float y_)
{
  x = x_;
  y = y_;
  magnitude = sqrt(x * x + y * y);
}

float Vector::getX()
{
  return x;
}

void Vector::setX(float x_)
{
  x = x_;
  magnitude = sqrt(x * x + y * y);
}

float Vector::getY()
{
  return y;
}

void Vector::setY(float y_)
{
  y = y_;
  magnitude = sqrt(x * x + y * y);
}

float Vector::getMagnitude()
{
  return magnitude;
}

std::tuple<float, float> Vector::getNormalised()
{
  if (magnitude == 0)
  {
    return std::make_tuple<float, float>(0, 0);
  }
  return std::make_tuple<float, float>(x / magnitude, y / magnitude);
}