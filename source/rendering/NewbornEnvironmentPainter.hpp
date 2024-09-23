#pragma once

#include "NewbornParallax.hpp"
#include "NewbornWorldRenderData.hpp"
#include "NewbornAssetTextureGroup.hpp"
#include "NewbornRenderer.hpp"
#include "NewbornWorldCamera.hpp"
#include "NewbornPerlin.hpp"
#include "NewbornRandomPoint.hpp"

namespace Newborn {

NEWBORN_CLASS(EnvironmentPainter);

class EnvironmentPainter {
public:
  EnvironmentPainter(RendererPtr renderer);

  void update(float dt);

  void renderStars(float pixelRatio, Vec2F const& screenSize, SkyRenderData const& sky);
  void renderDebrisFields(float pixelRatio, Vec2F const& screenSize, SkyRenderData const& sky);
  void renderBackOrbiters(float pixelRatio, Vec2F const& screenSize, SkyRenderData const& sky);
  void renderPlanetHorizon(float pixelRatio, Vec2F const& screenSize, SkyRenderData const& sky);
  void renderFrontOrbiters(float pixelRatio, Vec2F const& screenSize, SkyRenderData const& sky);
  void renderSky(Vec2F const& screenSize, SkyRenderData const& sky);

  void renderParallaxLayers(Vec2F parallaxWorldPosition, WorldCamera const& camera, ParallaxLayers const& layers, SkyRenderData const& sky);

  void cleanup(int64_t textureTimeout);

private:
  static float const SunriseTime;
  static float const SunsetTime;
  static float const SunFadeRate;
  static float const MaxFade;
  static float const RayPerlinFrequency;
  static float const RayPerlinAmplitude;
  static int const RayCount;
  static float const RayMinWidth;
  static float const RayWidthVariance;
  static float const RayAngleVariance;
  static float const SunRadius;
  static float const RayColorDependenceLevel;
  static float const RayColorDependenceScale;
  static float const RayUnscaledAlphaVariance;
  static float const RayMinUnscaledAlpha;
  static Vec3B const RayColor;

  void drawRays(float pixelRatio, SkyRenderData const& sky, Vec2F start, float length, double time, float alpha);
  void drawRay(float pixelRatio,
      SkyRenderData const& sky,
      Vec2F start,
      float width,
      float length,
      float angle,
      double time,
      Vec3B color,
      float alpha);
  void drawOrbiter(float pixelRatio, Vec2F const& screenSize, SkyRenderData const& sky, SkyOrbiter const& orbiter);

  uint64_t starsHash(SkyRenderData const& sky, Vec2F const& viewSize) const;
  void setupStars(SkyRenderData const& sky);

  RendererPtr m_renderer;
  AssetTextureGroupPtr m_textureGroup;

  double m_timer;
  PerlinF m_rayPerlin;

  uint64_t m_starsHash{};
  List<TexturePtr> m_starTextures;
  shared_ptr<Random2dPointGenerator<pair<size_t, float>>> m_starGenerator;
  List<shared_ptr<Random2dPointGenerator<pair<String, float>, double>>> m_debrisGenerators;
};

}
