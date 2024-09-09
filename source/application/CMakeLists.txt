INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_PLATFORM_INCLUDES}
    ${NEWBORN_APPLICATION_INCLUDES}
  )

SET (newborn_application_HEADERS
    NewbornApplication.hpp
    NewbornApplicationController.hpp
    NewbornMainApplication.hpp
    NewbornRenderer.hpp
  )

SET (newborn_application_SOURCES
    NewbornApplication.cpp
    NewbornRenderer.cpp
  )

SET (newborn_application_HEADERS ${newborn_application_HEADERS}
    NewbornP2PNetworkingService_pc.hpp
    NewbornPlatformServices_pc.hpp
    NewbornRenderer_opengl.hpp
  )

SET (newborn_application_SOURCES ${newborn_application_SOURCES}
    NewbornMainApplication_sdl.cpp
    NewbornP2PNetworkingService_pc.cpp
    NewbornPlatformServices_pc.cpp
    NewbornRenderer_opengl.cpp
  )



IF (NEWBORN_ENABLE_DISCORD_INTEGRATION)
  SET (newborn_application_SOURCES ${newborn_application_SOURCES}
      discord/core.cpp
      discord/image_manager.cpp
      discord/lobby_manager.cpp
      discord/network_manager.cpp
      discord/overlay_manager.cpp
      discord/relationship_manager.cpp
      discord/storage_manager.cpp
      discord/store_manager.cpp
      discord/types.cpp
      discord/user_manager.cpp
      discord/voice_manager.cpp
      discord/achievement_manager.cpp
      discord/activity_manager.cpp
      discord/application_manager.cpp
    )
ENDIF ()

ADD_LIBRARY (newborn_application OBJECT ${newborn_application_SOURCES} ${newborn_application_HEADERS})

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn_application REUSE_FROM newborn_core)
ENDIF()