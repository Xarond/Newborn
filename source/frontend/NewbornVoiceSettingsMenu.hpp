#pragma once

#include "NewbornBaseScriptPane.hpp"

namespace Newborn {

NEWBORN_CLASS(VoiceSettingsMenu);

class VoiceSettingsMenu : public BaseScriptPane {
public:
  VoiceSettingsMenu(Json const& config);

  virtual void show() override;
  void displayed() override;
  void dismissed() override;

private:

};

}
