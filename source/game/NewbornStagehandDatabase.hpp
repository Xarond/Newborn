#pragma once

#include "NewbornJson.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(StagehandDatabaseException, NewbornException);

NEWBORN_CLASS(Stagehand);

NEWBORN_CLASS(StagehandDatabase);

class StagehandDatabase {
public:
  StagehandDatabase();

  StagehandPtr createStagehand(String const& stagehandType, Json const& extraConfig = Json()) const;

private:
  StringMap<Json> m_stagehandTypes;
};

}
