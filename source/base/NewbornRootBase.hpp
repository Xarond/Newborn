#pragma once

#include "NewbornAssets.hpp"

namespace Newborn {

NEWBORN_CLASS(Configuration);

NEWBORN_EXCEPTION(RootException, NewbornException);

class RootBase {
public:
  static RootBase* singletonPtr();
  static RootBase& singleton();

  virtual AssetsConstPtr assets() = 0;
  virtual ConfigurationPtr configuration() = 0;
protected:
  RootBase();

  static atomic<RootBase*> s_singleton;
};

}