#include "NewbornContainerEntity.hpp"
#include "NewbornItemBag.hpp"

namespace Newborn {

size_t ContainerEntity::containerSize() const {
  return itemBag()->size();
}

List<ItemPtr> ContainerEntity::containerItems() const {
  return itemBag()->items();
}

}

