INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
  )

SET (newborn_core_HEADERS
    NewbornByteArray.hpp
    NewbornConfig.hpp
    NewbornBytes.hpp
    NewbornException.hpp
    NewbornStaticVector.hpp
    NewbornAlgorithm.hpp
    NewbornSmallVector.hpp
)
ADD_LIBRARY (newborn_core OBJECT ${newborn_core_SOURCES} ${newborn_core_HEADERS})