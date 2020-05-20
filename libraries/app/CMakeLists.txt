file(GLOB HEADERS "include/fiberchain/app/*.hpp")

add_library( fiberchain_app
             database_api.cpp
             api.cpp
             application.cpp
             impacted.cpp
             plugin.cpp
             ${HEADERS}
           )

target_link_libraries( fiberchain_app fiberchain_chain fiberchain_protocol 
                     fiberchain_tags fiberchain_bobserver
                     fiberchain_token fiberchain_dapp fiberchain_dapp_history 
                     fiberchain_private_message fiberchain_asset_storage
                     fiberchain_mf_plugins fc graphene_net 
                     graphene_utilities 
                     )
target_include_directories( fiberchain_app
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( application.cpp api.cpp database_api.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   fiberchain_app

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/fiberchain/app" )
