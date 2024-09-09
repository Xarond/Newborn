#include "NewbornVoiceSettingsMenu.hpp"
#include "NewbornVoiceLuaBindings.hpp"

namespace Newborn {

VoiceSettingsMenu::VoiceSettingsMenu(Json const& config) : BaseScriptPane(config) {
  m_script.setLuaRoot(make_shared<LuaRoot>());
  m_script.addCallbacks("voice", LuaBindings::makeVoiceCallbacks());
}

void VoiceSettingsMenu::show() {
  BaseScriptPane::show();
}

void VoiceSettingsMenu::displayed() {
  BaseScriptPane::displayed();
}

void VoiceSettingsMenu::dismissed() {
  BaseScriptPane::dismissed();
}

}