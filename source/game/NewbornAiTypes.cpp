#include "NewbornAiTypes.hpp"
#include "NewbornJsonExtra.hpp"

namespace Newborn {

AiState::AiState() {}

AiState::AiState(Json const& v) {
  availableMissions.addAll(jsonToStringList(v.get("availableMissions", JsonArray())));
  completedMissions.addAll(jsonToStringList(v.get("completedMissions", JsonArray())));
}

Json AiState::toJson() const {
  return JsonObject{{"availableMissions", jsonFromStringList(availableMissions.values())},
      {"completedMissions", jsonFromStringList(completedMissions.values())}};
}

}
