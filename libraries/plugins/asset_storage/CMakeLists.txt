file( GLOB HEADERS
      "include/fiberchain/asset_storage/*.hpp" )

add_library( fiberchain_asset_storage
             ${HEADERS}
             asset_storage_api.cpp
             asset_storage_plugin.cpp
             asset_storage_evaluators.cpp
             asset_storage_operations.cpp
           )

target_link_libraries( fiberchain_asset_storage fiberchain_app fiberchain_chain fc fiberchain_protocol )
target_include_directories( fiberchain_asset_storage
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   fiberchain_asset_storage
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
