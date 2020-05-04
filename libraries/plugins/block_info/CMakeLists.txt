file(GLOB HEADERS "include/fiberchain/plugins/block_info/*.hpp")

add_library( fiberchain_block_info
             ${HEADERS}
             block_info_plugin.cpp
             block_info_api.cpp
           )

target_link_libraries( fiberchain_block_info fiberchain_app fiberchain_chain fiberchain_protocol fc )
target_include_directories( fiberchain_block_info
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
