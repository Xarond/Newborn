#pragma once

#include "NewbornPane.hpp"
#include "NewbornConfiguration.hpp"
#include "NewbornMainInterfaceTypes.hpp"
#include "NewbornUniverseClient.hpp"

namespace Newborn {

NEWBORN_CLASS(SliderBarWidget);
NEWBORN_CLASS(ButtonWidget);
NEWBORN_CLASS(LabelWidget);
NEWBORN_CLASS(VoiceSettingsMenu);
NEWBORN_CLASS(KeybindingsMenu);
NEWBORN_CLASS(GraphicsMenu);
NEWBORN_CLASS(BindingsMenu);
NEWBORN_CLASS(OptionsMenu);

class OptionsMenu : public Pane {
public:
  OptionsMenu(PaneManager* manager, UniverseClientPtr client);

  virtual void show() override;

  void toggleFullscreen();

private:
  static StringList const ConfigKeys;

  void initConfig();

  void updateInstrumentVol();
  void updateSFXVol();
  void updateMusicVol();
  void updateTutorialMessages();
  void updateClientIPJoinable();
  void updateClientP2PJoinable();
  void updateAllowAssetsMismatch();
  void updateHeadRotation();

  void syncGuiToConf();

  void displayControls();
  void displayVoiceSettings();
  void displayModBindings();
  void displayGraphics();

  SliderBarWidgetPtr m_instrumentSlider;
  SliderBarWidgetPtr m_sfxSlider;
  SliderBarWidgetPtr m_musicSlider;
  ButtonWidgetPtr m_tutorialMessagesButton;
  ButtonWidgetPtr m_interactiveHighlightButton;
  ButtonWidgetPtr m_clientIPJoinableButton;
  ButtonWidgetPtr m_clientP2PJoinableButton;
  ButtonWidgetPtr m_allowAssetsMismatchButton;
  ButtonWidgetPtr m_headRotationButton;

  LabelWidgetPtr m_instrumentLabel;
  LabelWidgetPtr m_sfxLabel;
  LabelWidgetPtr m_musicLabel;
  LabelWidgetPtr m_p2pJoinableLabel;

  //TODO: add instrument range (or just use one range for all 3, it's kinda silly.)
  Vec2I m_sfxRange;
  Vec2I m_musicRange;

  JsonObject m_origConfig;
  JsonObject m_localChanges;

  VoiceSettingsMenuPtr m_voiceSettingsMenu;
  BindingsMenuPtr m_modBindingsMenu;
  KeybindingsMenuPtr m_keybindingsMenu;
  GraphicsMenuPtr m_graphicsMenu;
  PaneManager* m_paneManager;
};

}
