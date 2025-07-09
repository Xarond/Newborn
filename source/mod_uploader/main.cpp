#include <QApplication>
#include <QMessageBox>

#include "steam/steam_api.h"

#include "NewbornModUploader.hpp"
#include "NewbornStringConversion.hpp"

using namespace Newborn;

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  if (!SteamAPI_Init()) {
    QMessageBox::critical(nullptr, "Error", "Could not initialize Steam API");
    return 1;
  }

  ModUploader modUploader;
  modUploader.show();

  try {
    return app.exec();
  } catch (std::exception const& e) {
    QMessageBox::critical(nullptr, "Error", toQString(strf("Exception caught: {}\n", outputException(e, true))));
    coutf("Exception caught: {}\n", outputException(e, true));
    return 1;
  }
}
