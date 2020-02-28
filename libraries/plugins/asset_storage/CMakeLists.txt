file( GLOB HEADERS
      "include/futurepia/asset_storage/*.hpp" )

add_library( futurepia_asset_storage
             ${HEADERS}
             asset_storage_api.cpp
             asset_storage_plugin.cpp
             asset_storage_evaluators.cpp
             asset_storage_operations.cpp
           )

target_link_libraries( futurepia_asset_storage futurepia_app futurepia_chain fc futurepia_protocol )
target_include_directories( futurepia_asset_storage
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   futurepia_asset_storage
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
