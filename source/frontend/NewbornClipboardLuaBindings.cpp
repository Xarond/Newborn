#include "NewbornClipboardLuaBindings.hpp"
#include "NewbornLuaConverters.hpp"
#include "NewbornInput.hpp"
namespace Newborn {

LuaCallbacks LuaBindings::makeClipboardCallbacks(ApplicationControllerPtr appController, bool alwaysAllow) {
  LuaCallbacks callbacks;

  auto available = [alwaysAllow]() { return alwaysAllow || Input::singleton().getTag("clipboard") > 0; };

  callbacks.registerCallback("available", [=]() -> bool {
    return available();
  });

  callbacks.registerCallback("hasText", [=]() -> bool {
    return available() && appController->hasClipboard();
  });

  callbacks.registerCallback("getText", [=]() -> Maybe<String> {
    if (!available())
      return {};
    else
      return appController->getClipboard();
  });

  callbacks.registerCallback("setText", [=](String const& text) -> bool {
    if (available()) {
      appController->setClipboard(text);
      return true;
    }
    return false;
  });

  return callbacks;
};

}