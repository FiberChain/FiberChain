file(GLOB HEADERS "include/fiberchain/account_statistics/*.hpp")

add_library( fiberchain_account_statistics
             account_statistics_plugin.cpp
             account_statistics_api.cpp
           )

target_link_libraries( fiberchain_account_statistics fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_account_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_account_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)