#pragma once

#include "NewbornItem.hpp"
#include "NewbornWorld.hpp"
#include "NewbornSwingableItem.hpp"

namespace Newborn {

NEWBORN_CLASS(BlueprintItem);

class BlueprintItem : public Item, public SwingableItem {
public:
  BlueprintItem(Json const& config, String const& directory, Json const& data);
  virtual ItemPtr clone() const override;

  virtual List<Drawable> drawables() const override;

  virtual void fireTriggered() override;

  virtual List<Drawable> iconDrawables() const override;
  virtual List<Drawable> dropDrawables() const override;

private:
  ItemDescriptor m_recipe;
  Drawable m_recipeIconUnderlay;
  List<Drawable> m_inHandDrawable;
};

}
