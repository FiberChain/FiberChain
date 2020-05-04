file(GLOB HEADERS "include/fiberchain/plugins/auth_util/*.hpp")

add_library( fiberchain_auth_util
             ${HEADERS}
             auth_util_plugin.cpp
             auth_util_api.cpp
           )

target_link_libraries( fiberchain_auth_util fiberchain_app fiberchain_chain fiberchain_protocol fc )
target_include_directories( fiberchain_auth_util
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
