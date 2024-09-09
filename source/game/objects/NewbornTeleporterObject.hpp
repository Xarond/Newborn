#pragma once

#include "NewbornWarpTargetEntity.hpp"
#include "NewbornObject.hpp"

namespace Newborn {

class TeleporterObject : public Object, public WarpTargetEntity {
public:
  TeleporterObject(ObjectConfigConstPtr config, Json const& parameters = JsonObject());

  Vec2F footPosition() const override;
};

}
