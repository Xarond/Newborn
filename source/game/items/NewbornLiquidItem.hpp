#pragma once

#include "NewbornItem.hpp"
#include "NewbornFireableItem.hpp"
#include "NewbornBeamItem.hpp"
#include "NewbornEntityRendering.hpp"
#include "NewbornPreviewTileTool.hpp"

namespace Newborn {

NEWBORN_CLASS(LiquidItem);

class LiquidItem : public Item, public FireableItem, public PreviewTileTool, public BeamItem {
public:
  LiquidItem(Json const& config, String const& directory, Json const& settings);
  virtual ~LiquidItem() {}

  ItemPtr clone() const override;

  void init(ToolUserEntity* owner, ToolHand hand) override;
  void update(float dt, FireMode fireMode, bool shifting, HashSet<MoveControlType> const& moves) override;

  List<Drawable> nonRotatedDrawables() const override;

  void fire(FireMode mode, bool shifting, bool edgeTriggered) override;

  LiquidId liquidId() const;
  float liquidQuantity() const;

  List<PreviewTile> previewTiles(bool shifting) const override;

  bool canPlace(bool shifting) const;
  bool canPlaceAtTile(Vec2I pos) const;
  bool multiplaceEnabled() const;

private:
  LiquidId m_liquidId;
  float m_quantity;

  float m_blockRadius;
  float m_altBlockRadius;
  bool m_shifting;
};

}
