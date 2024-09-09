#pragma once

#include "NewbornHumanoid.hpp"

namespace Newborn {

NEWBORN_CLASS(EmoteProcessor);

class EmoteProcessor {
public:
  EmoteProcessor();

  HumanoidEmote detectEmotes(String const& chatter) const;

private:
  struct EmoteBinding {
    EmoteBinding() : emote() {}
    String text;
    HumanoidEmote emote;
  };
  List<EmoteBinding> m_emoteBindings;
};

}
