#pragma once

#include "NewbornSpline.hpp"
#include "NewbornGameTypes.hpp"
#include "NewbornNonRotatedDrawablesItem.hpp"
#include "NewbornToolUserItem.hpp"

namespace Newborn {

NEWBORN_CLASS(Item);
NEWBORN_CLASS(ToolUserEntity);
NEWBORN_CLASS(World);

NEWBORN_CLASS(BeamItem);

class BeamItem : public virtual NonRotatedDrawablesItem, public virtual ToolUserItem {
public:
  enum class EndType { Invalid = -1, Object, Tile, TileGroup, Wire };

  BeamItem(Json config);
  virtual ~BeamItem() = default;

  virtual void init(ToolUserEntity* owner, ToolHand hand) override;
  virtual void update(float dt, FireMode fireMode, bool shifting, HashSet<MoveControlType> const& moves) override;

  virtual List<Drawable> nonRotatedDrawables() const override;

  virtual float getAngle(float angle);
  virtual List<Drawable> drawables() const;
  virtual Vec2F handPosition() const;
  virtual Vec2F firePosition() const;
  virtual void setRange(float range);
  virtual float getAppropriateOpacity() const;
  virtual void setEnd(EndType type);

protected:
  List<Drawable> beamDrawables(bool canPlace = true) const;

  String m_image;
  StringList m_endImages;
  EndType m_endType;

  float m_segmentsPerUnit;
  float m_nearControlPointElasticity;
  float m_farControlPointElasticity;
  float m_nearControlPointDistance;
  Vec2F m_handPosition;
  Vec2F m_firePosition;
  float m_range;

  float m_targetSegmentRun;
  float m_minBeamWidth;
  float m_maxBeamWidth;
  float m_beamWidthDev;
  float m_minBeamJitter;
  float m_maxBeamJitter;
  float m_beamJitterDev;
  float m_minBeamTrans;
  float m_maxBeamTrans;
  float m_beamTransDev;
  int m_minBeamLines;
  int m_maxBeamLines;
  float m_innerBrightnessScale;
  float m_firstStripeThickness;
  float m_secondStripeThickness;
  Color m_color;

  mutable bool m_inRangeLastUpdate;
  mutable Color m_lastUpdateColor;
  mutable float m_particleGenerateCooldown;

  CSplineF m_beamCurve;
};

}
