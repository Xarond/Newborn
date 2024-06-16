# External code included with newborn source, which core depends on
set(NEWBORN_EXTERN_INCLUDES ${PROJECT_SOURCE_DIR}/extern)
add_subdirectory(extern)

# Core support code, not specific to newborn.
set(NEWBORN_CORE_INCLUDES
    ${PROJECT_SOURCE_DIR}/core
)
add_subdirectory(core)