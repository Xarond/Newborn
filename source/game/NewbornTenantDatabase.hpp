#pragma once

#include "NewbornRoot.hpp"
#include "NewbornAssets.hpp"
#include "NewbornTtlCache.hpp"

namespace Newborn {

NEWBORN_STRUCT(Tenant);
NEWBORN_CLASS(TenantDatabase);

NEWBORN_EXCEPTION(TenantException, NewbornException);

struct TenantNpcSpawnable {
  List<String> species;
  String type;
  Maybe<float> level;
  Maybe<Json> overrides;
};

struct TenantMonsterSpawnable {
  String type;
  Maybe<float> level;
  Maybe<Json> overrides;
};

typedef MVariant<TenantNpcSpawnable, TenantMonsterSpawnable> TenantSpawnable;

struct TenantRent {
  Vec2F periodRange;
  String pool;
};

struct Tenant {
  bool criteriaSatisfied(StringMap<unsigned> const& colonyTags) const;

  String name;
  float priority;

  // The colonyTag multiset the house must contain in order to satisfy this
  // tenant.
  StringMap<unsigned> colonyTagCriteria;

  List<TenantSpawnable> tenants;

  Maybe<TenantRent> rent;

  // The Json this tenant was parsed from
  Json config;
};

class TenantDatabase {
public:
  TenantDatabase();

  void cleanup();

  TenantPtr getTenant(String const& name) const;

  // Return the list of all tenants for which colonyTags is a superset of
  // colonyTagCriteria
  List<TenantPtr> getMatchingTenants(StringMap<unsigned> const& colonyTags) const;

private:
  static TenantPtr readTenant(String const& path);

  Map<String, String> m_paths;
  mutable Mutex m_cacheMutex;
  mutable HashTtlCache<String, TenantPtr> m_tenantCache;
};

}
