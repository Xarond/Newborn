#pragma once

#include "NewbornChatAction.hpp"
#include "NewbornEntity.hpp"

namespace Newborn {

NEWBORN_CLASS(ChattyEntity);

class ChattyEntity : public virtual Entity {
public:
  virtual Vec2F mouthPosition() const = 0;
  virtual Vec2F mouthPosition(bool) const = 0;
  virtual List<ChatAction> pullPendingChatActions() = 0;
};

}
