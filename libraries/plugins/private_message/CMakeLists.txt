file(GLOB HEADERS "include/fiberchain/private_message/*.hpp")

add_library( fiberchain_private_message
             private_message_plugin.cpp
           )

target_link_libraries( fiberchain_private_message fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_private_message
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_private_message

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
