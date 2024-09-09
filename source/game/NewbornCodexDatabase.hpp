#pragma once

#include "NewbornJson.hpp"
#include "NewbornCodex.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(CodexDatabaseException, NewbornException);

NEWBORN_CLASS(CodexDatabase);

class CodexDatabase {
public:
  CodexDatabase();

  StringMap<CodexConstPtr> codexes() const;
  CodexConstPtr codex(String const& codexId) const;

private:
  StringMap<CodexConstPtr> m_codexes;
};

}
