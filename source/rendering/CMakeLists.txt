INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
    ${NEWBORN_GAME_INCLUDES}
    ${NEWBORN_PLATFORM_INCLUDES}
    ${NEWBORN_APPLICATION_INCLUDES}
    ${NEWBORN_RENDERING_INCLUDES}
  )

SET (newborn_rendering_HEADERS
      NewbornAnchorTypes.hpp
      NewbornAssetTextureGroup.hpp
      NewbornDrawablePainter.hpp
      NewbornEnvironmentPainter.hpp
      NewbornFontTextureGroup.hpp
      NewbornTextPainter.hpp
      NewbornTilePainter.hpp
      NewbornWorldCamera.hpp
      NewbornWorldPainter.hpp
    )

SET (newborn_rendering_SOURCES
      NewbornAnchorTypes.cpp
      NewbornAssetTextureGroup.cpp
      NewbornDrawablePainter.cpp
      NewbornEnvironmentPainter.cpp
      NewbornFontTextureGroup.cpp
      NewbornTextPainter.cpp
      NewbornTilePainter.cpp
      NewbornWorldCamera.cpp
      NewbornWorldPainter.cpp
    )

ADD_LIBRARY (newborn_rendering OBJECT ${newborn_rendering_SOURCES} ${newborn_rendering_HEADERS})

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn_rendering REUSE_FROM newborn_core)
ENDIF()