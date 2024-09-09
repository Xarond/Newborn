#include "NewbornAugmentItem.hpp"
#include "NewbornRoot.hpp"
#include "NewbornAssets.hpp"
#include "NewbornItemDatabase.hpp"
#include "NewbornLuaComponents.hpp"
#include "NewbornItemLuaBindings.hpp"
#include "NewbornConfigLuaBindings.hpp"
#include "NewbornJsonExtra.hpp"

namespace Newborn {

AugmentItem::AugmentItem(Json const& config, String const& directory, Json const& parameters)
  : Item(config, directory, parameters) {}

AugmentItem::AugmentItem(AugmentItem const& rhs) : AugmentItem(rhs.config(), rhs.directory(), rhs.parameters()) {}

ItemPtr AugmentItem::clone() const {
  return make_shared<AugmentItem>(*this);
}

StringList AugmentItem::augmentScripts() const {
  return jsonToStringList(instanceValue("scripts")).transformed(bind(&AssetPath::relativeTo, directory(), _1));
}

ItemPtr AugmentItem::applyTo(ItemPtr const item) {
  return Root::singleton().itemDatabase()->applyAugment(item, this);
}

}
