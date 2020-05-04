file(GLOB HEADERS "include/fiberchain/plugins/raw_block/*.hpp")

add_library( fiberchain_raw_block
             ${HEADERS}
             raw_block_plugin.cpp
             raw_block_api.cpp
           )

target_link_libraries( fiberchain_raw_block fiberchain_app fiberchain_chain fiberchain_protocol fc )
target_include_directories( fiberchain_raw_block
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
