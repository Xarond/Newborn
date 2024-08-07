#pragma once

#include "NewbornJson.hpp"

namespace Newborn {

NEWBORN_CLASS(StatisticsService);

class StatisticsService {
public:
    virtual ~StatisticsService() = default;

    virtual bool initialized() const = 0;
    virtual Maybe<String> error() const = 0;

    virtual bool setStat(String const& name, String const& type, Json const& value);
    virtual Json getStat(String const& name, String const& type, Json def = {}) const = 0;

    virtual bool reportEvent(String const& name, Json const& fields) = 0;

    virtual bool unlockAchievement(String const& name) = 0;
    virtual StringSet achievementsUnlocked() const = 0;

    virtual void refresh() = 0;
    virtual void flush() = 0;
    virtual bool reset() = 0;

};

}