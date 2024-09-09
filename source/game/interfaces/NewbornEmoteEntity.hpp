#pragma once

#include "NewbornHumanoid.hpp"
#include "NewbornEntity.hpp"

namespace Newborn {

NEWBORN_CLASS(EmoteEntity);

class EmoteEntity : public virtual Entity {
public:
  virtual void playEmote(HumanoidEmote emote) = 0;
};

}
