#pragma once

#include "NewbornWidget.hpp"

namespace Newborn {

NEWBORN_CLASS(FuelWidget);

class FuelWidget : public Widget {
public:
  FuelWidget();
  virtual ~FuelWidget() {}

  virtual void update(float dt);

  void setCurrentFuelLevel(float amount);
  void setMaxFuelLevel(float amount);
  void setPotentialFuelAmount(float amount);
  void setRequestedFuelAmount(float amount);

  void ping();

protected:
  virtual void renderImpl();

  float m_fuelLevel;
  float m_maxLevel;
  float m_potential;
  float m_requested;

  float m_pingTimeout;

  TextStyle m_textStyle;

private:
};

}
