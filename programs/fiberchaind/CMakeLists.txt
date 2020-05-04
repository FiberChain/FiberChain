add_executable( fiberchaind main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling fiberchaind with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( FIBERCHAIN_STATIC_BUILD )
   target_link_libraries( fiberchaind PRIVATE
      "-static-libstdc++ -static-libgcc"
      fiberchain_plugins
      fiberchain_mf_plugins
      fiberchain_app
      fiberchain_bobserver
      fiberchain_account_history
      fiberchain_chain
      fiberchain_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
elseif( FULL_STATIC_BUILD ) # for windows version (mingw) : include libwinpthread-1.dll in fiberchaind
   target_link_libraries( fiberchaind PRIVATE
      "-static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lwinpthread -Wl,-Bdynamic"
      fiberchain_plugins
      fiberchain_mf_plugins
      fiberchain_app
      fiberchain_bobserver
      fiberchain_account_history
      fiberchain_chain
      fiberchain_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
  )   
else( FIBERCHAIN_STATIC_BUILD )
   target_link_libraries( fiberchaind PRIVATE
      fiberchain_plugins
      fiberchain_mf_plugins
      fiberchain_app
      fiberchain_bobserver
      fiberchain_account_history
      fiberchain_chain
      fiberchain_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
endif( FIBERCHAIN_STATIC_BUILD )

install( TARGETS
   fiberchaind

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
