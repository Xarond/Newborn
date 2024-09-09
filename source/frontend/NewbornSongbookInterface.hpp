#pragma once

#include "NewbornSongbook.hpp"
#include "NewbornPane.hpp"
#include "NewbornListener.hpp"

namespace Newborn {

NEWBORN_CLASS(Player);

NEWBORN_CLASS(SongbookInterface);

class SongbookInterface : public Pane {
public:
  SongbookInterface(PlayerPtr player);

  void update(float dt) override;

private:
  PlayerPtr m_player;
  StringList m_files;
  String m_lastSearch;
  CallbackListenerPtr m_reloadListener;
  bool play();
  void refresh(bool reloadFiles = false);
};

}
