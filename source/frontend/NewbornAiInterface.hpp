#pragma once

#include "NewbornAiTypes.hpp"
#include "NewbornGameTimers.hpp"
#include "NewbornWarping.hpp"
#include "NewbornAnimation.hpp"
#include "NewbornItemDescriptor.hpp"
#include "NewbornPane.hpp"
#include "NewbornMainInterfaceTypes.hpp"
#include "NewbornTechDatabase.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(AiDatabase);
NEWBORN_CLASS(Cinematic);
NEWBORN_CLASS(LabelWidget);
NEWBORN_CLASS(ImageWidget);
NEWBORN_CLASS(ImageStretchWidget);
NEWBORN_CLASS(CanvasWidget);
NEWBORN_CLASS(ListWidget);
NEWBORN_CLASS(ButtonWidget);
NEWBORN_CLASS(QuestManager);
NEWBORN_CLASS(StackWidget);
NEWBORN_CLASS(TabSetWidget);
NEWBORN_CLASS(Companion);

NEWBORN_CLASS(AiInterface);

NEWBORN_EXCEPTION(AiInterfaceException, NewbornException);

class AiInterface : public Pane {
public:
  AiInterface(UniverseClientPtr client, CinematicPtr cinematic, MainInterfacePaneManager* paneManager);

  void update(float dt) override;

  void displayed() override;
  void dismissed() override;

  void setSourceEntityId(EntityId sourceEntityId);

private:
  enum class AiPages : uint8_t {
    StatusPage,
    MissionList,
    MissionPage,
    CrewList,
    CrewPage
  };

  void updateBreadcrumbs();
  void showStatus();

  void populateMissions();
  void showMissions();
  void selectMission();
  void startMission();

  void populateCrew();
  void showCrew();
  void selectRecruit();
  void dismissRecruit();

  void goBack();

  void setFaceAnimation(String const& name);
  void setCurrentSpeech(String const& textWidget, AiSpeech speech);

  void giveBlueprint(String const& blueprintName);

  AiPages m_currentPage;

  UniverseClientPtr m_client;
  CinematicPtr m_cinematic;
  MainInterfacePaneManager* m_paneManager;
  QuestManagerPtr m_questManager;

  EntityId m_sourceEntityId;

  AiDatabaseConstPtr m_aiDatabase;

  Animation m_staticAnimation;
  Animation m_scanlineAnimation;
  pair<String, Animation> m_faceAnimation;

  AudioInstancePtr m_chatterSound;

  StackWidgetPtr m_mainStack;
  StackWidgetPtr m_missionStack;
  StackWidgetPtr m_crewStack;

  ButtonWidgetPtr m_showMissionsButton;
  ButtonWidgetPtr m_showCrewButton;
  ButtonWidgetPtr m_backButton;

  int m_breadcrumbLeftPadding;
  int m_breadcrumbRightPadding;
  ImageStretchWidgetPtr m_homeBreadcrumbBackground;
  ImageStretchWidgetPtr m_pageBreadcrumbBackground;
  ImageStretchWidgetPtr m_itemBreadcrumbBackground;
  LabelWidgetPtr m_homeBreadcrumbWidget;
  LabelWidgetPtr m_pageBreadcrumbWidget;
  LabelWidgetPtr m_itemBreadcrumbWidget;

  LabelWidgetPtr m_currentTextWidget;

  CanvasWidgetPtr m_aiFaceCanvasWidget;
  LabelWidgetPtr m_shipStatusTextWidget;

  ListWidgetPtr m_missionListWidget;
  LabelWidgetPtr m_missionNameLabel;
  ImageWidgetPtr m_missionIcon;

  ListWidgetPtr m_crewListWidget;
  LabelWidgetPtr m_recruitNameLabel;
  ImageWidgetPtr m_recruitIcon;

  String m_species;

  String m_missionBreadcrumbText;
  String m_missionDeployText;
  String m_crewBreadcrumbText;
  String m_defaultRecruitName;
  String m_defaultRecruitDescription;

  StringList m_availableMissions;
  StringList m_completedMissions;
  Maybe<String> m_selectedMission;

  List<CompanionPtr> m_crew;
  CompanionPtr m_selectedRecruit;

  Maybe<AiSpeech> m_currentSpeech;
  float m_textLength;
  float m_textMaxLength;

  ButtonWidgetPtr m_startMissionButton;
  ButtonWidgetPtr m_dismissRecruitButton;
};

}
