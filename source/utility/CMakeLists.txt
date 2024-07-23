INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
    ${NEWBORN_PLATFORM_INCLUDES}
    ${NEWBORN_GAME_INCLUDES}
  )

ADD_EXECUTABLE (asset_packer
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base>
  asset_packer.cpp)
TARGET_LINK_LIBRARIES (asset_packer ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (asset_unpacker
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base>
  asset_unpacker.cpp)
TARGET_LINK_LIBRARIES (asset_unpacker ${NEWBORN_EXT_LIBS})