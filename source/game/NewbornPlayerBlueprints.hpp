#pragma once

#include "NewbornByteArray.hpp"
#include "NewbornSet.hpp"
#include "NewbornItemDescriptor.hpp"

namespace Newborn {

NEWBORN_CLASS(PlayerBlueprints);

class PlayerBlueprints {
public:
  PlayerBlueprints();
  PlayerBlueprints(Json const& json);

  Json toJson() const;

  bool isKnown(ItemDescriptor const& itemDescriptor) const;
  bool isNew(ItemDescriptor const& itemDescriptor) const;
  void add(ItemDescriptor const& itemDescriptor);
  void markAsRead(ItemDescriptor const& itemDescriptor);

private:
  HashSet<ItemDescriptor> m_knownBlueprints;
  HashSet<ItemDescriptor> m_newBlueprints;
};

}
