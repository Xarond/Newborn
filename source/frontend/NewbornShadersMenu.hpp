#pragma once

#include "NewbornBaseScriptPane.hpp"
#include "NewbornUniverseClient.hpp"

namespace Newborn {

NEWBORN_CLASS(ShadersMenu);

class ShadersMenu : public BaseScriptPane {
public:
  ShadersMenu(Json const& config, UniverseClientPtr client);

  virtual void show() override;
  void displayed() override;
  void dismissed() override;

private:
  UniverseClientPtr m_client;
};

}
