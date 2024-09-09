#pragma once

#include "NewbornUuid.hpp"
#include "NewbornJson.hpp"

namespace Newborn {

NEWBORN_CLASS(Codex);
NEWBORN_STRUCT(CodexEntry);
NEWBORN_CLASS(UniverseClient);

class PlayerCodexes {
public:
  typedef pair<CodexConstPtr, bool> CodexEntry;

  PlayerCodexes(Json const& json = {});

  Json toJson() const;

  List<CodexEntry> codexes() const;

  bool codexKnown(String const& codexId) const;
  CodexConstPtr learnCodex(String const& codexId, bool markRead = false);

  bool codexRead(String const& codexId) const;
  bool markCodexRead(String const& codexId);
  bool markCodexUnread(String const& codexId);

  void learnInitialCodexes(String const& playerSpecies);

  CodexConstPtr firstNewCodex() const;

private:
  StringMap<CodexEntry> m_codexes;
};

typedef shared_ptr<PlayerCodexes> PlayerCodexesPtr;
}
