#pragma once

#include "NewbornInputEvent.hpp"

namespace Newborn {

NEWBORN_CLASS(ApplicationController);
NEWBORN_CLASS(Renderer);
NEWBORN_CLASS(Application);

NEWBORN_EXCEPTION(ApplicationException, NewbornException);

enum class WindowMode {
    Normal,
    Maximized,
    Fullscreen,
    Borderless
};

class Application {
public:
    virtual ~Application() = default;
    virtual void startup(StringList const& cmdLineArgs);

    virtual void applicationInit(ApplicationControllerPtr appController);

    virtual void renderInit(RendererPtr renderer);

    virtual void windowChanged(WindowMode windowMode, Vec2U screenSize);

    virtual void processInput(InputEvent const& event);

    virtual void update();

    virtual void render();

    virtual void getAudioData(int16_t* sampleData, size_t frameCount);

    virtual void shutdown();

    ApplicationControllerPtr const& appController() const;
    RendererPtr const& renderer() const;

private:
    ApplicationControllerPtr m_appController;
    RendererPtr m_renderer;
};

inline ApplicationControllerPtr const& Application::appController() const {
  return m_appController;
}

inline RendererPtr const& Application::renderer() const {
  return m_renderer;
}

}