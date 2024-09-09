#include "NewbornPopupInterface.hpp"
#include "NewbornGuiReader.hpp"
#include "NewbornRoot.hpp"
#include "NewbornLabelWidget.hpp"
#include "NewbornRandom.hpp"
#include "NewbornAssets.hpp"

namespace Newborn {

PopupInterface::PopupInterface() {
  auto assets = Root::singleton().assets();

  GuiReader reader;

  reader.registerCallback("close", [=](Widget*) { dismiss(); });
  reader.registerCallback("ok", [=](Widget*) { dismiss(); });

  reader.construct(assets->json("/interface/windowconfig/popup.config:paneLayout"), this);
}

void PopupInterface::displayMessage(String const& message, String const& title, String const& subtitle, Maybe<String> const& onShowSound) {
  setTitleString(title, subtitle);
  fetchChild<LabelWidget>("message")->setText(message);
  show();
  auto sound = onShowSound.value(Random::randValueFrom(Root::singleton().assets()->json("/interface/windowconfig/popup.config:onShowSound").toArray(), "").toString());
  if (!sound.empty())
    context()->playAudio(sound);
}

}
