#pragma once

#include "NewbornPane.hpp"
#include "NewbornPlayerStorage.hpp"

namespace Newborn {

NEWBORN_CLASS(PlayerStorage);

class CharSelectionPane : public Pane {
public:
  typedef function<void()> CreateCharCallback;
  typedef function<void(PlayerPtr const&)> SelectCharacterCallback;
  typedef function<void(Uuid)> DeleteCharacterCallback;

  CharSelectionPane(PlayerStoragePtr playerStorage, CreateCharCallback createCallback,
      SelectCharacterCallback selectCallback, DeleteCharacterCallback deleteCallback);

  bool sendEvent(InputEvent const& event) override;
  void show() override;
  void updateCharacterPlates();

private:
  void shiftCharacters(int movement);
  void selectCharacter(unsigned buttonIndex);

  PlayerStoragePtr m_playerStorage;
  unsigned m_downScroll;

  CreateCharCallback m_createCallback;
  SelectCharacterCallback m_selectCallback;
  DeleteCharacterCallback m_deleteCallback;
};
typedef shared_ptr<CharSelectionPane> CharSelectionPanePtr;
}
