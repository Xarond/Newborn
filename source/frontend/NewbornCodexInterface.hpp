#pragma once

#include "NewbornPane.hpp"
#include "NewbornPlayerCodexes.hpp"

namespace Newborn {

NEWBORN_CLASS(Player);
NEWBORN_CLASS(JsonRpcInterface);
NEWBORN_CLASS(StackWidget);
NEWBORN_CLASS(ListWidget);
NEWBORN_CLASS(LabelWidget);
NEWBORN_CLASS(ButtonWidget);
NEWBORN_CLASS(ButtonGroupWidget);
NEWBORN_CLASS(Codex);

NEWBORN_CLASS(CodexInterface);
class CodexInterface : public Pane {
public:
  CodexInterface(PlayerPtr player);

  virtual void show() override;
  virtual void tick(float dt) override;

  void showTitles();
  void showSelectedContents();
  void showContents(String const& codexId);
  void showContents(CodexConstPtr codex);

  void forwardPage();
  void backwardPage();

  bool showNewCodex();

private:
  void updateSpecies();
  void setupPageText();
  void updateCodexList();

  StackWidgetPtr m_stack;

  ListWidgetPtr m_bookList;

  CodexConstPtr m_currentCodex;
  size_t m_currentPage;

  ButtonGroupWidgetPtr m_speciesTabs;
  LabelWidgetPtr m_selectLabel;
  LabelWidgetPtr m_titleLabel;
  LabelWidgetPtr m_pageContent;
  LabelWidgetPtr m_pageLabelWidget;
  LabelWidgetPtr m_pageNumberWidget;
  ButtonWidgetPtr m_prevPageButton;
  ButtonWidgetPtr m_nextPageButton;
  ButtonWidgetPtr m_backButton;

  String m_selectText;
  String m_currentSpecies;

  PlayerPtr m_player;
  List<PlayerCodexes::CodexEntry> m_codexList;
};

}
