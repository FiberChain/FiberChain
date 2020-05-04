file(GLOB HEADERS "include/fiberchain/dapp_history/*.hpp")

add_library( fiberchain_dapp_history
               ${HEADERS}
               dapp_history_api.cpp
               dapp_history_plugin.cpp
               dapp_impacted.cpp
           )

target_link_libraries( fiberchain_dapp_history 
                        fiberchain_chain fiberchain_protocol fiberchain_app 
                        fiberchain_dapp fiberchain_token )
target_include_directories( fiberchain_dapp_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_dapp_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
