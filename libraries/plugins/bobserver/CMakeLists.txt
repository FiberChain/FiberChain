file(GLOB HEADERS "include/fiberchain/bobserver/*.hpp")

add_library( fiberchain_bobserver
             bobserver_plugin.cpp
             bobserver_evaluators.cpp
             bobserver_operations.cpp
           )

target_link_libraries( fiberchain_bobserver fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_bobserver
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_bobserver

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
