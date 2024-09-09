#pragma once

#include "NewbornItem.hpp"
#include "NewbornInstrumentItem.hpp"
#include "NewbornStatusEffectItem.hpp"
#include "NewbornEffectSourceItem.hpp"
#include "NewbornToolUserItem.hpp"
#include "NewbornActivatableItem.hpp"
#include "NewbornPointableItem.hpp"

namespace Newborn {

NEWBORN_CLASS(World);
NEWBORN_CLASS(ToolUserEntity);
NEWBORN_CLASS(InstrumentItem);

class InstrumentItem : public Item,
                       public StatusEffectItem,
                       public EffectSourceItem,
                       public ToolUserItem,
                       public ActivatableItem,
                       public PointableItem {
public:
  InstrumentItem(Json const& config, String const& directory, Json const& data);

  ItemPtr clone() const override;

  List<PersistentStatusEffect> statusEffects() const override;
  StringSet effectSources() const override;

  void update(float dt, FireMode fireMode, bool shifting, HashSet<MoveControlType> const& moves) override;

  bool active() const override;
  void setActive(bool active) override;
  bool usable() const override;
  void activate() override;

  List<Drawable> drawables() const override;
  float getAngle(float angle) override;

private:
  List<PersistentStatusEffect> m_activeStatusEffects;
  List<PersistentStatusEffect> m_inactiveStatusEffects;
  StringSet m_activeEffectSources;
  StringSet m_inactiveEffectSources;
  List<Drawable> m_drawables;
  List<Drawable> m_activeDrawables;
  int m_activeCooldown;

  float m_activeAngle;
  String m_kind;
};

}
