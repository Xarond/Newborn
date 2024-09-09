#include "NewbornCellularLightArray.hpp"
#include "NewbornInterpolation.hpp"

namespace Newborn {

template <>
void CellularLightArray<ScalarLightTraits>::calculatePointLighting(size_t xmin, size_t ymin, size_t xmax, size_t ymax) {
  float pointPerBlockObstacleAttenuation = 1.0f / m_pointMaxObstacle;
  float pointPerBlockAirAttenuation = 1.0f / m_pointMaxAir;

  for (PointLight light : m_pointLights) {
    if (light.position[0] < 0 || light.position[0] > m_width - 1 || light.position[1] < 0 || light.position[1] > m_height - 1)
      continue;

    float maxIntensity = ScalarLightTraits::maxIntensity(light.value);
    Vec2F beamDirection = Vec2F(1, 0).rotate(light.beamAngle);
    float perBlockObstacleAttenuation = light.asSpread ? 1.0f / m_spreadMaxObstacle : pointPerBlockObstacleAttenuation;
    float perBlockAirAttenuation = light.asSpread ? 1.0f / m_spreadMaxAir : pointPerBlockAirAttenuation;

    float maxRange = maxIntensity * (light.asSpread ? m_spreadMaxAir : m_pointMaxAir);
    // The min / max considering the radius of the light
    size_t lxmin = std::floor(std::max<float>(xmin, light.position[0] - maxRange));
    size_t lymin = std::floor(std::max<float>(ymin, light.position[1] - maxRange));
    size_t lxmax = std::ceil(std::min<float>(xmax, light.position[0] + maxRange));
    size_t lymax = std::ceil(std::min<float>(ymax, light.position[1] + maxRange));

    for (size_t x = lxmin; x < lxmax; ++x) {
      for (size_t y = lymin; y < lymax; ++y) {
        LightValue lvalue = getLight(x, y);
        // + 0.5f to correct block position to center
        Vec2F blockPos = Vec2F(x + 0.5f, y + 0.5f);

        Vec2F relativeLightPosition = blockPos - light.position;
        float distance = relativeLightPosition.magnitude();
        if (distance == 0.0f) {
          setLight(x, y, light.value + lvalue);
          continue;
        }

        float attenuation = distance * perBlockAirAttenuation;
        if (attenuation >= 1.0f)
          continue;

        Vec2F direction = relativeLightPosition / distance;
        if (light.beam > 0.0001f) {
          attenuation += (1.0f - light.beamAmbience) * clamp(light.beam * (1.0f - direction * beamDirection), 0.0f, 1.0f);
          if (attenuation >= 1.0f)
            continue;
        }

        float remainingAttenuation = maxIntensity - attenuation;
        if (remainingAttenuation <= 0.0f)
          continue;

        // Need to circularize manhattan attenuation here
        float circularizedPerBlockObstacleAttenuation = perBlockObstacleAttenuation / max(fabs(direction[0]), fabs(direction[1]));
        float blockAttenuation = lineAttenuation(blockPos, light.position, circularizedPerBlockObstacleAttenuation, remainingAttenuation);

        attenuation += blockAttenuation;
        // Apply single obstacle boost (determine single obstacle by one
        // block unit of attenuation).
        if (!light.asSpread)
         attenuation += min(blockAttenuation, circularizedPerBlockObstacleAttenuation) * m_pointObstacleBoost;

        if (attenuation < 1.0f) {
          if (m_pointAdditive) {
            auto newLight = ScalarLightTraits::subtract(light.value, attenuation);
            if (ScalarLightTraits::maxIntensity(newLight) > 0.0001f)
              setLight(x, y, lvalue + (light.asSpread ? newLight * 0.15f : newLight));
          } else {
            setLight(x, y, ScalarLightTraits::max(ScalarLightTraits::subtract(light.value, attenuation), lvalue));
          }
        }
      }
    }
  }
}

template <>
void CellularLightArray<ColoredLightTraits>::calculatePointLighting(size_t xmin, size_t ymin, size_t xmax, size_t ymax) {
  float pointPerBlockObstacleAttenuation = 1.0f / m_pointMaxObstacle;
  float pointPerBlockAirAttenuation = 1.0f / m_pointMaxAir;

  for (PointLight light : m_pointLights) {
    if (light.position[0] < 0 || light.position[0] > m_width - 1 || light.position[1] < 0 || light.position[1] > m_height - 1)
      continue;

    float maxIntensity = ColoredLightTraits::maxIntensity(light.value);
    Vec2F beamDirection = Vec2F(1, 0).rotate(light.beamAngle);
    float perBlockObstacleAttenuation = light.asSpread ? 1.0f / m_spreadMaxObstacle : pointPerBlockObstacleAttenuation;
    float perBlockAirAttenuation = light.asSpread ? 1.0f / m_spreadMaxAir : pointPerBlockAirAttenuation;

    float maxRange = maxIntensity * (light.asSpread ? m_spreadMaxAir : m_pointMaxAir);
    // The min / max considering the radius of the light
    size_t lxmin = std::floor(std::max<float>(xmin, light.position[0] - maxRange));
    size_t lymin = std::floor(std::max<float>(ymin, light.position[1] - maxRange));
    size_t lxmax = std::ceil(std::min<float>(xmax, light.position[0] + maxRange));
    size_t lymax = std::ceil(std::min<float>(ymax, light.position[1] + maxRange));

    for (size_t x = lxmin; x < lxmax; ++x) {
      for (size_t y = lymin; y < lymax; ++y) {
        LightValue lvalue = getLight(x, y);
        // + 0.5f to correct block position to center
        Vec2F blockPos = Vec2F(x + 0.5f, y + 0.5f);

        Vec2F relativeLightPosition = blockPos - light.position;
        float distance = relativeLightPosition.magnitude();
        if (distance == 0.0f) {
          setLight(x, y, light.value + lvalue);
          continue;
        }

        float attenuation = distance * perBlockAirAttenuation;
        if (attenuation >= 1.0f)
          continue;

        Vec2F direction = relativeLightPosition / distance;
        if (light.beam > 0.0f) {
          attenuation += (1.0f - light.beamAmbience) * clamp(light.beam * (1.0f - direction * beamDirection), 0.0f, 1.0f);
          if (attenuation >= 1.0f)
            continue;
        }

        float remainingAttenuation = maxIntensity - attenuation;
        if (remainingAttenuation <= 0.0f)
          continue;

        // Need to circularize manhattan attenuation here
        float circularizedPerBlockObstacleAttenuation = perBlockObstacleAttenuation / max(fabs(direction[0]), fabs(direction[1]));
        float blockAttenuation = lineAttenuation(blockPos, light.position, circularizedPerBlockObstacleAttenuation, remainingAttenuation);

        attenuation += blockAttenuation;
        // Apply single obstacle boost (determine single obstacle by one
        // block unit of attenuation).
        if (!light.asSpread)
          attenuation += min(blockAttenuation, circularizedPerBlockObstacleAttenuation) * m_pointObstacleBoost;

        if (attenuation < 1.0f) {
          if (m_pointAdditive) {
            auto newLight = ColoredLightTraits::subtract(light.value, attenuation);
            if (ColoredLightTraits::maxIntensity(newLight) > 0.0001f)
              setLight(x, y, lvalue + (light.asSpread ? newLight * 0.15f : newLight));
          } else {
            setLight(x, y, ColoredLightTraits::max(ColoredLightTraits::subtract(light.value, attenuation), lvalue));
          }
        }
      }
    }
  }
}

}