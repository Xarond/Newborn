#include "NewbornPointableItem.hpp"

namespace Newborn {

float PointableItem::getAngleDir(float angle, Direction) {
  return getAngle(angle);
}

float PointableItem::getAngle(float angle) {
  return angle;
}

}
