INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
    ${NEWBORN_GAME_INCLUDES}
    ${NEWBORN_PLATFORM_INCLUDES}
    ${NEWBORN_APPLICATION_INCLUDES}
    ${NEWBORN_RENDERING_INCLUDES}
    ${NEWBORN_WINDOWING_INCLUDES}
    ${NEWBORN_FRONTEND_INCLUDES}
  )

SET (newborn_client_HEADERS
      NewbornClientApplication.hpp
    )

SET (newborn_client_SOURCES
      NewbornClientApplication.cpp
    )

IF (NEWBORN_SYSTEM_WINDOWS)
  SET (newborn_client_RESOURCES
      newborn.rc
    )
ENDIF ()

ADD_EXECUTABLE (newborn WIN32
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  $<TARGET_OBJECTS:newborn_application> $<TARGET_OBJECTS:newborn_rendering> $<TARGET_OBJECTS:newborn_windowing> $<TARGET_OBJECTS:newborn_frontend>
  ${newborn_client_HEADERS} ${newborn_client_SOURCES} ${newborn_client_RESOURCES})

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn REUSE_FROM newborn_core)
ENDIF()

IF(UNIX)
  set_target_properties (newborn PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN'")
ENDIF()

TARGET_LINK_LIBRARIES (newborn ${NEWBORN_EXT_LIBS} ${NEWBORN_EXT_GUI_LIBS})