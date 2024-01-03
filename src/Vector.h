
#ifndef SFMLGAME_VECTOR_H
#define SFMLGAME_VECTOR_H

#include <cmath>
#include <tuple>

class Vector
{
 public:
  Vector(float x_, float y_);
  float getX();
  void setX(float x_);
  float getY();
  void setY(float y_);
  float getMagnitude();
  std::tuple<float, float> getNormalised();

 private:
  float x;
  float y;
  float magnitude;

};

#endif // SFMLGAME_VECTOR_H
