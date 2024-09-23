INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
  )

SET (newborn_base_HEADERS
    NewbornAnimatedPartSet.hpp
    NewbornAssets.hpp
    NewbornAssetSource.hpp
    NewbornBlocksAlongLine.hpp
    NewbornCellularLightArray.hpp
    NewbornCellularLighting.hpp
    NewbornCellularLiquid.hpp
    NewbornConfiguration.hpp
    NewbornDirectoryAssetSource.hpp
    NewbornMemoryAssetSource.hpp
    NewbornMixer.hpp
    NewbornPackedAssetSource.hpp
    NewbornRootBase.hpp
    NewbornVersionOptionParser.hpp
    NewbornWorldGeometry.hpp
    scripting/NewbornImageLuaBindings.hpp
  )

SET (newborn_base_SOURCES
    NewbornAnimatedPartSet.cpp
    NewbornAssets.cpp
    NewbornCellularLightArray.cpp
    NewbornCellularLighting.cpp
    NewbornConfiguration.cpp
    NewbornDirectoryAssetSource.cpp
    NewbornMemoryAssetSource.cpp
    NewbornMixer.cpp
    NewbornPackedAssetSource.cpp
    NewbornRootBase.cpp
    NewbornVersionOptionParser.cpp
    NewbornWorldGeometry.cpp
    scripting/NewbornImageLuaBindings.cpp
  )

ADD_LIBRARY (newborn_base OBJECT ${newborn_base_SOURCES} ${newborn_base_HEADERS})

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn_base REUSE_FROM newborn_core)
ENDIF()