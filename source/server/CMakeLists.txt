INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
    ${NEWBORN_PLATFORM_INCLUDES}
    ${NEWBORN_GAME_INCLUDES}
  )

SET (newborn_server_HEADERS
    NewbornServerQueryThread.hpp
    NewbornServerRconClient.hpp
    NewbornServerRconThread.hpp
  )

SET (newborn_server_SOURCES
    NewbornServerQueryThread.cpp
    NewbornServerRconClient.cpp
    NewbornServerRconThread.cpp
    main.cpp
  )

IF (NEWBORN_SYSTEM_WINDOWS)
  SET (newborn_server_RESOURCES
      newborn_server.rc
    )
ENDIF ()

ADD_EXECUTABLE (newborn_server
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  ${newborn_server_HEADERS} ${newborn_server_SOURCES} ${newborn_server_RESOURCES})

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn_server REUSE_FROM newborn_core)
ENDIF()

TARGET_LINK_LIBRARIES (newborn_server ${NEWBORN_EXT_LIBS})