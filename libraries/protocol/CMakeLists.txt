file(GLOB HEADERS "include/fiberchain/protocol/*.hpp")

if( MSVC )
   set( hardfork_hpp_file "${CMAKE_CURRENT_SOURCE_DIR}/include/fiberchain/protocol/hardfork.hpp" )
   add_custom_target( build_hardfork_hpp
      COMMAND cat-parts "${CMAKE_CURRENT_SOURCE_DIR}/hardfork.d" ${hardfork_hpp_file} )
   add_dependencies( build_hardfork_hpp cat-parts )
else( MSVC )
   set( hardfork_hpp_file "${CMAKE_CURRENT_BINARY_DIR}/include/fiberchain/protocol/hardfork.hpp" )
   add_custom_target( build_hardfork_hpp
      COMMAND "${CMAKE_SOURCE_DIR}/programs/build_helpers/cat_parts.py" "${CMAKE_CURRENT_SOURCE_DIR}/hardfork.d" ${hardfork_hpp_file} )
endif( MSVC )

set_source_files_properties( "${CMAKE_CURRENT_BINARY_DIR}/include/fiberchain/protocol/hardfork.hpp" PROPERTIES GENERATED TRUE )

## SORT .cpp by most likely to change / break compile
add_library( fiberchain_protocol

             types.cpp
             authority.cpp
             operations.cpp
             sign_state.cpp
             operation_util_impl.cpp
             fiberchain_operations.cpp
             transaction.cpp
             block.cpp
             asset.cpp
             version.cpp
             get_config.cpp

             ${HEADERS}
             ${hardfork_hpp_file}
             "${CMAKE_CURRENT_BINARY_DIR}/include/fiberchain/protocol/hardfork.hpp"
           )

add_dependencies( fiberchain_protocol build_hardfork_hpp )
target_link_libraries( fiberchain_protocol fc )
target_include_directories( fiberchain_protocol
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" )

INSTALL( TARGETS
   fiberchain_protocol

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

INSTALL( FILES ${HEADERS} DESTINATION "include/fiberchain/protocol" )
