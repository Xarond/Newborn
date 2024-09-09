#pragma once

#include "NewbornItem.hpp"
#include "NewbornFireableItem.hpp"
#include "NewbornBeamItem.hpp"

namespace Newborn {

NEWBORN_CLASS(ObjectItem);

class ObjectItem : public Item, public FireableItem, public BeamItem {
public:
  ObjectItem(Json const& config, String const& directory, Json const& objectParameters);
  virtual ~ObjectItem() {}

  ItemPtr clone() const override;

  void init(ToolUserEntity* owner, ToolHand hand) override;
  void update(float dt, FireMode fireMode, bool shifting, HashSet<MoveControlType> const& moves) override;

  List<Drawable> nonRotatedDrawables() const override;

  float cooldownTime() const override;
  void fire(FireMode mode, bool shifting, bool edgeTriggered) override;

  String objectName() const;
  Json objectParameters() const;

  bool placeInWorld(FireMode mode, bool shifting);
  bool canPlace(bool shifting) const;

private:
  bool m_shifting;
};

}
