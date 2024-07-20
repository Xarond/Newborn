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

)

SET (newborn_base_SOURCES
    NewbornAssets.cpp
)

ADD_LIBRARY (newborn_base OBJECT ${newborn_base_SOURCES} ${newborn_base_HEADERS})

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn_base REUSE_FROM newborn_core)
ENDIF()