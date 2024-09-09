INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
  )

SET (newborn_base_HEADERS
    NewbornAssets.hpp
    NewbornAssetSource.hpp
    NewbornDirectoryAssetSource.hpp
    NewbornMemoryAssetSource.hpp
    NewbornPackedAssetSource.hpp
    NewbornRootBase.hpp
    NewbornAnimatedPartSet.hpp
    NewbornVersion.hpp
    NewbornConfiguration.hpp
    NewbornVersionOptionParser.hpp
    NewbornWorldGeometry.hpp
    NewbornMixer.hpp
    NewbornCellularLiquid.hpp
    NewbornBlocksAlongLine.hpp
    NewbornCellularLighting.hpp
    NewbornCellularLightArray.hpp
    scripting/NewbornImageLuaBindings.hpp


)

SET (newborn_base_SOURCES
    NewbornAssets.cpp
    NewbornDirectoryAssetSource.cpp
    NewbornAnimatedPartSet.cpp
    NewbornMemoryAssetSource.cpp
    NewbornPackedAssetSource.cpp
    NewbornVersionOptionParser.cpp
    NewbornRootBase.cpp
    NewbornWorldGeometry.cpp
    NewbornMixer.cpp
    NewbornCellularLighting.cpp
    NewbornCellularLightArray.cpp
    NewbornConfiguration.cpp
    scripting/NewbornImageLuaBindings.cpp
)

CONFIGURE_FILE (NewbornVersion.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/NewbornVersion.cpp)
ADD_LIBRARY (newborn_base OBJECT ${newborn_base_SOURCES} ${newborn_base_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/NewbornVersion.cpp)

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn_base REUSE_FROM newborn_core)
ENDIF()