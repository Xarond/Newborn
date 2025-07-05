#pragma once

#include "NewbornJson.hpp"
#include "NewbornThread.hpp"
#include "NewbornVersion.hpp"

namespace Newborn {

NEWBORN_CLASS(Configuration);

NEWBORN_EXCEPTION(ConfigurationException, NewbornException);

class Configuration {
public:
  Configuration(Json defaultConfiguration, Json currentConfiguration);

  Json defaultConfiguration() const;
  Json currentConfiguration() const;
  String printConfiguration() const;

  Json get(String const& key, Json def = {}) const;
  Json getPath(String const& path, Json def = {}) const;

  Json getDefault(String const& key) const;
  Json getDefaultPath(String const& path) const;

  void set(String const& key, Json const& value);
  void setPath(String const& path, Json const& value);

private:
  mutable Mutex m_mutex;

  Json m_defaultConfig;
  Json m_currentConfig;
};

}
