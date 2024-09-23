#pragma once

#include "NewbornPane.hpp"
#include "NewbornUuid.hpp"
#include "NewbornMainInterfaceTypes.hpp"
#include "NewbornProgressWidget.hpp"
#include "NewbornLabelWidget.hpp"

namespace Newborn {

NEWBORN_CLASS(TeamBar);
NEWBORN_CLASS(MainInterface);
NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(Player);

NEWBORN_CLASS(TeamInvite);
NEWBORN_CLASS(TeamInvitation);
NEWBORN_CLASS(TeamMemberMenu);
NEWBORN_CLASS(TeamBar);

class TeamInvite : public Pane {
public:
  TeamInvite(TeamBar* owner);

  virtual void show() override;

private:
  TeamBar* m_owner;

  void ok();
  void close();
};

class TeamInvitation : public Pane {
public:
  TeamInvitation(TeamBar* owner);

  void open(Uuid const& inviterUuid, String const& inviterName);

private:
  TeamBar* m_owner;
  Uuid m_inviterUuid;

  void ok();
  void close();
};

class TeamMemberMenu : public Pane {
public:
  TeamMemberMenu(TeamBar* owner);

  void open(Uuid memberUuid, Vec2I position);

  virtual void update(float dt) override;

private:
  void updateWidgets();

  void close();
  void beamToShip();
  void makeLeader();
  void removeFromTeam();

  TeamBar* m_owner;
  Uuid m_memberUuid;
  bool m_canBeam;
};

class TeamBar : public Pane {
public:
  TeamBar(MainInterface* mainInterface, UniverseClientPtr client);

  bool sendEvent(InputEvent const& event) override;

  void invitePlayer(String const& playerName);
  void acceptInvitation(Uuid const& inviterUuid);

protected:
  virtual void update(float dt) override;

private:
  void updatePlayerResources();

  void inviteButton();

  void buildTeamBar();

  void showMemberMenu(Uuid memberUuid, Vec2I position);

  MainInterface* m_mainInterface;
  UniverseClientPtr m_client;

  GuiContext* m_guiContext;

  TextStyle m_nameStyle;
  Vec2F m_nameOffset;

  TeamInvitePtr m_teamInvite;
  TeamInvitationPtr m_teamInvitation;
  TeamMemberMenuPtr m_teamMemberMenu;

  ProgressWidgetPtr m_healthBar;
  ProgressWidgetPtr m_energyBar;
  ProgressWidgetPtr m_foodBar;

  LabelWidgetPtr m_nameLabel;

  Color m_energyBarColor;
  Color m_energyBarRegenMixColor;
  Color m_energyBarUnusableColor;

  friend class TeamMemberMenu;
};

}