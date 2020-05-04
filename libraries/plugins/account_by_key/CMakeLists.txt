file(GLOB HEADERS "include/fiberchain/account_by_key/*.hpp")

add_library( fiberchain_account_by_key
             account_by_key_plugin.cpp
             account_by_key_api.cpp
           )

target_link_libraries( fiberchain_account_by_key fiberchain_chain fiberchain_protocol fiberchain_app )
target_include_directories( fiberchain_account_by_key
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_account_by_key

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
