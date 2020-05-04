file(GLOB HEADERS "include/fiberchain/blockchain_statistics/*.hpp")

add_library( fiberchain_blockchain_statistics
             blockchain_statistics_plugin.cpp
             blockchain_statistics_api.cpp
           )

target_link_libraries( fiberchain_blockchain_statistics fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_blockchain_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_blockchain_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)