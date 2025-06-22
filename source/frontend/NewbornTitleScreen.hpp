#pragma once

#include "NewbornSky.hpp"
#include "NewbornAmbient.hpp"
#include "NewbornRegisteredPaneManager.hpp"
#include "NewbornInterfaceCursor.hpp"
#include "NewbornUniverseClient.hpp"

namespace Newborn {

NEWBORN_CLASS(Player);
NEWBORN_CLASS(PlayerStorage);
NEWBORN_CLASS(CharCreationPane);
NEWBORN_CLASS(CharSelectionPane);
NEWBORN_CLASS(OptionsMenu);
NEWBORN_CLASS(ModsMenu);
NEWBORN_CLASS(GuiContext);
NEWBORN_CLASS(Pane);
NEWBORN_CLASS(PaneManager);
NEWBORN_CLASS(Mixer);
NEWBORN_CLASS(EnvironmentPainter);
NEWBORN_CLASS(CelestialMasterDatabase);
NEWBORN_CLASS(ButtonWidget);

NEWBORN_CLASS(TitleScreen);

enum class TitleState {
  Main,
  Options,
  Mods,
  SinglePlayerSelectCharacter,
  SinglePlayerCreateCharacter,
  MultiPlayerSelectCharacter,
  MultiPlayerCreateCharacter,
  MultiPlayerConnect,
  StartSinglePlayer,
  StartMultiPlayer,
  Quit
};

class TitleScreen {
public:
  TitleScreen(PlayerStoragePtr playerStorage, MixerPtr mixer, UniverseClientPtr client);

  void renderInit(RendererPtr renderer);

  void render();

  bool handleInputEvent(InputEvent const& event);
  void update(float dt);

  bool textInputActive() const;

  TitleState currentState() const;
  // TitleState is StartSinglePlayer, StartMultiPlayer, or Quit
  bool finishedState() const;
  void resetState();
  // Switches to multi player select character screen immediately, skipping the
  // connection screen if 'skipConnection' is true.  If the player backs out of
  // the multiplayer menu, the skip connection is forgotten.
  void goToMultiPlayerSelectCharacter(bool skipConnection);

  void stopMusic();

  PlayerPtr currentlySelectedPlayer() const;

  String multiPlayerAddress() const;
  void setMultiPlayerAddress(String address);

  String multiPlayerPort() const;
  void setMultiPlayerPort(String port);

  String multiPlayerAccount() const;
  void setMultiPlayerAccount(String account);

  String multiPlayerPassword() const;
  void setMultiPlayerPassword(String password);

private:
  void initMainMenu();
  void initCharSelectionMenu();
  void initCharCreationMenu();
  void initMultiPlayerMenu();
  void initOptionsMenu(UniverseClientPtr client);
  void initModsMenu();

  void renderCursor();

  void switchState(TitleState titleState);
  void back();

  float interfaceScale() const;
  unsigned windowHeight() const;
  unsigned windowWidth() const;

  GuiContext* m_guiContext;

  RendererPtr m_renderer;
  EnvironmentPainterPtr m_environmentPainter;
  PanePtr m_multiPlayerMenu;

  RegisteredPaneManager<String> m_paneManager;

  Vec2I m_cursorScreenPos;
  InterfaceCursor m_cursor;
  TitleState m_titleState;

  PanePtr m_mainMenu;
  List<pair<ButtonWidgetPtr, Vec2I>> m_rightAnchoredButtons;

  PlayerPtr m_mainAppPlayer;
  PlayerStoragePtr m_playerStorage;

  bool m_skipMultiPlayerConnection;
  String m_connectionAddress;
  String m_connectionPort;
  String m_account;
  String m_password;

  CelestialMasterDatabasePtr m_celestialDatabase;

  MixerPtr m_mixer;

  SkyPtr m_skyBackdrop;

  AmbientNoisesDescriptionPtr m_musicTrack;
  AudioInstancePtr m_currentMusicTrack;
  AmbientManager m_musicTrackManager;
};

}
