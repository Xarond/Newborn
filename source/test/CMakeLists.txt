INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
    ${NEWBORN_PLATFORM_INCLUDES}
    ${NEWBORN_GAME_INCLUDES}
  )

# Add top-level test directory so  gtest-all.cc can find its own include file
INCLUDE_DIRECTORIES (.)

SET (newborn_core_tests_SOURCES
      gtest/gtest-all.cc

      core_tests_main.cpp

      algorithm_test.cpp
      block_allocator_test.cpp
      blocks_along_line_test.cpp
      btree_database_test.cpp
      btree_test.cpp
      byte_array_test.cpp
      clock_test.cpp
      color_test.cpp
      container_test.cpp
      encode_test.cpp
      file_test.cpp
      hash_test.cpp
      host_address_test.cpp
      ref_ptr_test.cpp
      json_test.cpp
      flat_hash_test.cpp
      formatted_json_test.cpp
      line_test.cpp
      lua_test.cpp
      lua_json_test.cpp
      math_test.cpp
      multi_table_test.cpp
      net_states_test.cpp
      ordered_map_test.cpp
      ordered_set_test.cpp
      periodic_test.cpp
      poly_test.cpp
      random_test.cpp
      rect_test.cpp
      serialization_test.cpp
      static_vector_test.cpp
      small_vector_test.cpp
      sha_test.cpp
      shell_parse.cpp
      string_test.cpp
      strong_typedef_test.cpp
      thread_test.cpp
      worker_pool_test.cpp
      variant_test.cpp
      vlq_test.cpp
    )
ADD_EXECUTABLE (core_tests
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core>
  ${newborn_core_tests_SOURCES})
TARGET_LINK_LIBRARIES (core_tests ${NEWBORN_EXT_LIBS})
ADD_TEST (NAME core_tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/core_tests)

SET (newborn_game_tests_SOURCES
      gtest/gtest-all.cc

      game_tests_main.cpp

      NewbornTestUniverse.cpp
      assets_test.cpp
      function_test.cpp
      item_test.cpp
      root_test.cpp
      server_test.cpp
      spawn_test.cpp
      stat_test.cpp
      tile_array_test.cpp
      world_geometry_test.cpp
      universe_connection_test.cpp
    )
ADD_EXECUTABLE (game_tests
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  ${newborn_game_tests_SOURCES})
TARGET_LINK_LIBRARIES (game_tests ${NEWBORN_EXT_LIBS})
ADD_TEST (NAME game_tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/game_tests)

SET_TESTS_PROPERTIES(core_tests PROPERTIES
                     LABELS "NoAssets")
