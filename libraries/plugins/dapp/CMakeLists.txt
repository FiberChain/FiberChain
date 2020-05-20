file( GLOB HEADERS
      "include/fiberchain/dapp/*.hpp" )

add_library( fiberchain_dapp
             ${HEADERS}
             dapp_api.cpp
             dapp_plugin.cpp
             dapp_evaluators.cpp
             dapp_operations.cpp
           )

target_link_libraries( fiberchain_dapp fiberchain_app fiberchain_chain fc fiberchain_protocol )
target_include_directories( fiberchain_dapp
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_dapp
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
