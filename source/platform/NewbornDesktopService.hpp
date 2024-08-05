#pragma once

#include "NewbornConfig.hpp"
#include "NewbornString.hpp"

namespace Newborn {

NEWBORN_CLASS(DesktopService);

class DesktopService {
public:
  ~DesktopService() = default;

  virtual void openUrl(String const& url) = 0;
};

}
