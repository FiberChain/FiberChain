file(GLOB HEADERS "include/fiberchain/delayed_node/*.hpp")

add_library( fiberchain_delayed_node
             delayed_node_plugin.cpp
           )

target_link_libraries( fiberchain_delayed_node fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_delayed_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( delayed_node_plugin.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   fiberchain_delayed_node

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
