file(GLOB HEADERS "include/fiberchain/chain/*.hpp" "include/fiberchain/chain/util/*.hpp")

## SORT .cpp by most likely to change / break compile
add_library( fiberchain_chain

             # As database takes the longest to compile, start it first
             database.cpp
             fork_database.cpp
             bobserver_schedule.cpp

             fiberchain_evaluator.cpp

             fiberchain_objects.cpp
             shared_authority.cpp
             block_log.cpp

             util/reward.cpp

             ${HEADERS}
           )

target_link_libraries( fiberchain_chain fiberchain_protocol fc chainbase graphene_schema ${PATCH_MERGE_LIB} )
target_include_directories( fiberchain_chain
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" )

if(MSVC)
  set_source_files_properties( database.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   fiberchain_chain

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/fiberchain/chain" )
