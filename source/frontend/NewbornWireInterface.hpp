#pragma once

#include "NewbornPane.hpp"
#include "NewbornWiring.hpp"

namespace Newborn {

NEWBORN_CLASS(WorldClient);
NEWBORN_CLASS(WorldPainter);
NEWBORN_CLASS(Player);
NEWBORN_CLASS(WirePane);

class WirePane : public Pane, public WireConnector {
public:
  WirePane(WorldClientPtr worldClient, PlayerPtr player, WorldPainterPtr worldPainter);
  virtual ~WirePane() {}

  virtual void update(float dt) override;
  virtual bool sendEvent(InputEvent const& event) override;

  virtual SwingResult swing(WorldGeometry const& geometry, Vec2F position, FireMode mode) override;
  virtual bool connecting() override;

  virtual void reset();

protected:
  void renderImpl() override;

private:
  void renderWire(Vec2F from, Vec2F to, Color baseColor);

  WorldClientPtr m_worldClient;
  PlayerPtr m_player;
  WorldPainterPtr m_worldPainter;
  Vec2I m_mousePos;
  bool m_connecting;
  WireDirection m_sourceDirection;
  WireConnection m_sourceConnector;

  Vec2F m_inSize;
  Vec2F m_outSize;
  Vec2F m_nodeSize;

  float m_beamWidthDev;
  float m_minBeamWidth;
  float m_maxBeamWidth;
  float m_beamTransDev;
  float m_minBeamTrans;
  float m_maxBeamTrans;
  float m_innerBrightnessScale;
  float m_firstStripeThickness;
  float m_secondStripeThickness;
};

}
