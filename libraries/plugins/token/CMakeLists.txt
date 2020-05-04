file(GLOB HEADERS "include/fiberchain/token/*.hpp" "include/fiberchain/token/util/*.hpp")

add_library( fiberchain_token
             token_api.cpp
             token_evaluators.cpp
             token_operations.cpp
             token_plugin.cpp
           )

target_link_libraries( fiberchain_token fiberchain_chain fiberchain_protocol fiberchain_app fiberchain_dapp )
target_include_directories( fiberchain_token
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_token

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
