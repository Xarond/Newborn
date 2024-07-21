INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
  )


INCLUDE_DIRECTORIES (.)

SET (newborn_core_tests_SOURCES
      gtest/gtest-all.cc

      core_tests_main.cpp

      byte_array_test.cpp
      algorithm_test.cpp
      hash_test.cpp
      math_test.cpp
      flat_hash_test.cpp
      encode_test.cpp
      file_test.cpp
      host_address_test.cpp
      sha_test.cpp
      small_vector_test.cpp
      shell_parse.cpp
      net_states_test.cpp
      ordered_map_test.cpp
      ordered_set_test.cpp
      btree_database_test.cpp
      btree_test.cpp
      multi_table_test.cpp
    )
ADD_EXECUTABLE (core_tests
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core>
  ${newborn_core_tests_SOURCES})
TARGET_LINK_LIBRARIES (core_tests ${NEWBORN_EXT_LIBS})
ADD_TEST (NAME core_tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/core_tests)

SET (newborn_game_tests_SOURCES
      gtest/gtest-all.cc

      game_tests_main.cpp

      assets_test.cpp
    )
ADD_EXECUTABLE (game_tests
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core>
  ${newborn_game_tests_SOURCES})
TARGET_LINK_LIBRARIES (game_tests ${NEWBORN_EXT_LIBS})
ADD_TEST (NAME game_tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/game_tests)

SET_TESTS_PROPERTIES(core_tests PROPERTIES
                     LABELS "NoAssets")
