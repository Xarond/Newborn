#pragma once

#include "NewbornOrderedSet.hpp"
#include "NewbornItemDescriptor.hpp"
#include "NewbornAnimation.hpp"
#include "NewbornQuestDescriptor.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(AiException, NewbornException);

struct AiSpeech {
  String animation;
  String text;
  float speedModifier;
};

struct AiState {
  AiState();
  AiState(Json const& v);

  Json toJson() const;

  OrderedHashSet<String> availableMissions;
  OrderedHashSet<String> completedMissions;
};

struct AiSpeciesMissionText {
  String buttonText;
  String repeatButtonText;
  AiSpeech selectSpeech;
};

struct AiMission {
  String missionName;
  String missionUniqueWorld;
  Maybe<String> warpAnimation;
  Maybe<bool> warpDeploy;
  String icon;
  StringMap<AiSpeciesMissionText> speciesText;
};

}
