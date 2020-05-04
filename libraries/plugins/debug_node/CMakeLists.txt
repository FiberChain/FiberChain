file(GLOB HEADERS "include/fiberchain/plugins/debug_node/*.hpp")

add_library( fiberchain_debug_node
             ${HEADERS}
             debug_node_plugin.cpp
             debug_node_api.cpp
           )

target_link_libraries( fiberchain_debug_node fiberchain_app fiberchain_chain fiberchain_protocol fc )
target_include_directories( fiberchain_debug_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS fiberchain_debug_node
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
       )
INSTALL( FILES ${HEADERS} DESTINATION "include/fiberchain/plugins/debug_node" )
