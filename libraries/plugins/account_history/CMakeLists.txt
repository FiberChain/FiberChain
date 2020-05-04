file(GLOB HEADERS "include/fiberchain/account_history/*.hpp")

add_library( fiberchain_account_history
             account_history_plugin.cpp
           )

target_link_libraries( fiberchain_account_history fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_account_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_account_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
