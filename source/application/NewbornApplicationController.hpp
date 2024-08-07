#pragma once

#include "NewbornApplication.hpp"
#include "NewbornStatisticsService.hpp"
#include "NewbornP2PNetworkingService.hpp"
#include "NewbornUserGeneratedContentService.hpp"
#include "NewbornDesktopService.hpp"
#include "NewbornImage.hpp"

namespace Newborn {

NEWBORN_CLASS(ApplicationController);

struct AudioFormat {
    unsigned sampleRate;
    unsigned channels;
};

class ApplicationController {
public:
  virtual ~ApplicationController() = default;


  virtual void setTargetUpdateRate(float targetUpdateRate) = 0;

  virtual void setUpdateTrackWindow(float updateTrackWindow) = 0;

  virtual void setMaxFrameSkip(unsigned maxFrameSkip) = 0;

  virtual void setApplicationTitle(String title) = 0;
  virtual void setFullscreenWindow(Vec2U fullScreenResolution) = 0;
  virtual void setNormalWindow(Vec2U windowSize) = 0;
  virtual void setMaximizedWindow() = 0;
  virtual void setBorderlessWindow() = 0;
  virtual void setVSyncEnabled(bool vSync) = 0;
  virtual void setCursorVisible(bool cursorVisible) = 0;
  virtual void setCursorPosition(Vec2I cursorPosition) = 0;
  virtual void setCursorHardware(bool cursorHardware) = 0;
  virtual bool setCursorImage(const String& id, const ImageConstPtr& image, unsigned scale, const Vec2I& offset) = 0;
  virtual void setAcceptingTextInput(bool acceptingTextInput) = 0;



  virtual AudioFormat enableAudio() = 0;
  virtual void disableAudio() = 0;
  
  typedef void (*AudioCallback)(void* userdata, uint8_t* stream, int len);
  
  virtual bool openAudioInputDevice(const char* name, int freq, int channels, void* userdata, AudioCallback callback) = 0;
  virtual bool closeAudioInputDevice() = 0;

  virtual bool hasClipboard() = 0;
  virtual void setClipboard(String text) = 0;
  virtual Maybe<String> getClipboard() = 0;

  virtual float updateRate() const = 0;
  virtual float renderFps() const = 0;

  virtual StatisticsServicePtr statisticsService() const = 0;
  virtual P2PNetworkingServicePtr p2pNetworkingService() const = 0;
  virtual UserGeneratedContentServicePtr userGeneratedContentService() const = 0;
  virtual DesktopServicePtr desktopService() const = 0;

  virtual void quit() = 0;
};

}