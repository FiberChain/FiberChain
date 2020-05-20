file(GLOB HEADERS "include/fiberchain/tags/*.hpp")

add_library( fiberchain_tags
             tags_plugin.cpp )

target_link_libraries( fiberchain_tags fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_tags
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_tags

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
