INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
  )

FIND_PACKAGE (Qt5Core)
FIND_PACKAGE (Qt5Widgets)

SET (CMAKE_INCLUDE_CURRENT_DIR ON)
SET (CMAKE_AUTOMOC ON)

SET (newborn_mod_uploader_HEADERS
    NewbornStringConversion.hpp
    NewbornModUploader.hpp
    NewbornSPlainTextEdit.hpp
  )

SET (newborn_mod_uploader_SOURCES
    NewbornModUploader.cpp
    NewbornSPlainTextEdit.cpp
    main.cpp
  )

ADD_EXECUTABLE (mod_uploader WIN32
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base>
  ${NEWBORN_mod_uploader_HEADERS} ${NEWBORN_mod_uploader_SOURCES})
TARGET_LINK_LIBRARIES (mod_uploader ${NEWBORN_EXT_LIBS} ${STEAM_API_LIBRARY})

SET (CMAKE_AUTOMOC OFF)
SET (CMAKE_INCLUDE_CURRENT_DIR OFF)
