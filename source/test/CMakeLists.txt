INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
  )

# Add top-level test directory so  gtest-all.cc can find its own include file
INCLUDE_DIRECTORIES (.)

SET (newborn_core_tests_SOURCES
      gtest/gtest-all.cc

      core_tests_main.cpp

      algorithm_test.cpp
      hash_test.cpp

    )
ADD_EXECUTABLE (core_tests
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core>
  ${newborn_core_tests_SOURCES})
TARGET_LINK_LIBRARIES (core_tests ${NEWBORN_EXT_LIBS})
ADD_TEST (NAME core_tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/core_tests)

SET (newborn_game_tests_SOURCES
      gtest/gtest-all.cc


    )
ADD_EXECUTABLE (game_tests
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core>
  ${newborn_game_tests_SOURCES})
TARGET_LINK_LIBRARIES (game_tests ${NEWBORN_EXT_LIBS})
ADD_TEST (NAME game_tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/game_tests)

SET_TESTS_PROPERTIES(core_tests PROPERTIES
                     LABELS "NoAssets")
