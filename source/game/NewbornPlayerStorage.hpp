#pragma once

#include "NewbornOrderedMap.hpp"
#include "NewbornUuid.hpp"
#include "NewbornPlayerFactory.hpp"
#include "NewbornThread.hpp"
#include "NewbornWorldStorage.hpp"
#include "NewbornStatistics.hpp"

namespace Newborn {

class PlayerStorage {
public:
  PlayerStorage(String const& storageDir);
  ~PlayerStorage();

  size_t playerCount() const;
  // Returns nothing if index is out of bounds.
  Maybe<Uuid> playerUuidAt(size_t index);
  // Returns nothing if name doesn't match a player.
  Maybe<Uuid> playerUuidByName(String const& name, Maybe<Uuid> except = {});
  // Returns nothing if name doesn't match a player.
  List<Uuid> playerUuidListByName(String const& name, Maybe<Uuid> except = {});

  // Also returns the diskStore Json if needed.
  Json savePlayer(PlayerPtr const& player);

  Maybe<Json> maybeGetPlayerData(Uuid const& uuid);
  Json getPlayerData(Uuid const& uuid);
  PlayerPtr loadPlayer(Uuid const& uuid);
  void deletePlayer(Uuid const& uuid);

  WorldChunks loadShipData(Uuid const& uuid);
  void applyShipUpdates(Uuid const& uuid, WorldChunks const& updates);

  // Move the given player to the top of the player ordering.
  void moveToFront(Uuid const& uuid);

  // Copy all the player relevant files for this uuid into .bak1 .bak2 etc
  // files for however many backups are configured
  void backupCycle(Uuid const& uuid);

  // Get / Set PlayerStorage global metadata
  void setMetadata(String key, Json value);
  Json getMetadata(String const& key);

private:
  String const& uuidFileName(Uuid const& uuid);
  void writeMetadata();

  mutable RecursiveMutex m_mutex;
  String m_storageDirectory;
  String m_backupDirectory;
  OrderedHashMap<Uuid, Json> m_savedPlayersCache;
  BiMap<Uuid, String> m_playerFileNames;
  JsonObject m_metadata;
};

}
