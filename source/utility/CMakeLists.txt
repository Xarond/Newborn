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

ADD_EXECUTABLE (btree_repacker
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base>
  btree_repacker.cpp)
TARGET_LINK_LIBRARIES (btree_repacker ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (dump_versioned_json
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  dump_versioned_json.cpp)
TARGET_LINK_LIBRARIES (dump_versioned_json ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (game_repl
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  game_repl.cpp)
TARGET_LINK_LIBRARIES (game_repl ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (make_versioned_json
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  make_versioned_json.cpp)
TARGET_LINK_LIBRARIES (make_versioned_json ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (planet_mapgen
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  planet_mapgen.cpp)
TARGET_LINK_LIBRARIES (planet_mapgen ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (render_terrain_selector
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  render_terrain_selector.cpp)
TARGET_LINK_LIBRARIES (render_terrain_selector ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (update_tilesets
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  update_tilesets.cpp tileset_updater.cpp)
TARGET_LINK_LIBRARIES (update_tilesets ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (fix_embedded_tilesets
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  fix_embedded_tilesets.cpp)
TARGET_LINK_LIBRARIES (fix_embedded_tilesets ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (world_benchmark
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  world_benchmark.cpp)
TARGET_LINK_LIBRARIES (world_benchmark ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (generation_benchmark
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  generation_benchmark.cpp)
TARGET_LINK_LIBRARIES (generation_benchmark ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (dungeon_generation_benchmark
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  dungeon_generation_benchmark.cpp)
TARGET_LINK_LIBRARIES (dungeon_generation_benchmark ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (map_grep
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  map_grep.cpp)
TARGET_LINK_LIBRARIES (map_grep ${NEWBORN_EXT_LIBS})

ADD_EXECUTABLE (word_count
  $<TARGET_OBJECTS:newborn_extern> $<TARGET_OBJECTS:newborn_core> $<TARGET_OBJECTS:newborn_base> $<TARGET_OBJECTS:newborn_game>
  word_count.cpp)
TARGET_LINK_LIBRARIES (word_count ${NEWBORN_EXT_LIBS})
