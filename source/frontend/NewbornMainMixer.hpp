#pragma once

#include "NewbornMixer.hpp"
#include "NewbornGameTypes.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(WorldPainter);
NEWBORN_CLASS(MainMixer);

class MainMixer {
public:
  MainMixer(unsigned sampleRate, unsigned channels);

  void setUniverseClient(UniverseClientPtr universeClient);
  void setWorldPainter(WorldPainterPtr worldPainter);

  void update(float dt, bool muteSfx = false, bool muteMusic = false);

  MixerPtr mixer() const;

  void setSpeed(float speed);
  void setVolume(float volume, float rampTime = 0.0f);
  void read(int16_t* sampleData, size_t frameCount, Mixer::ExtraMixFunction = {});

private:
  UniverseClientPtr m_universeClient;
  WorldPainterPtr m_worldPainter;
  MixerPtr m_mixer;
  Set<MixerGroup> m_mutedGroups;
  Map<MixerGroup, float> m_groupVolumes;
};

}
