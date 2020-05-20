#pragma once

#include <fiberchain/app/plugin.hpp>
#include <fiberchain/chain/fiberchain_object_types.hpp>

#include <boost/multi_index/composite_key.hpp>

namespace fiberchain { namespace asset_storage {
   using namespace std;
   using namespace fiberchain::chain;
   using namespace boost::multi_index;
   using namespace fiberchain::protocol;

   enum asset_by_key_object_type
   {
      asset_object_type    = (ASSET_STORAGE_SPACE_ID << 8),
      asset_event_type     = (ASSET_STORAGE_SPACE_ID << 8) + 1
   };

   class asset_object : public object< asset_object_type, asset_object >
   {
      public:
         template< typename Constructor, typename Allocator >
         asset_object( Constructor&& c, allocator< Allocator > a )
          : asset_data(a)
         {
            c( *this );
         }

         id_type                 id;
         asset_name_type         asset_name;
         shared_string           asset_data;
         account_name_type       owner;
         time_point_sec          created;
         transaction_id_type     created_tx;
   };

   typedef oid< asset_object > asset_object_id_type;

   class asset_event : public object < asset_event_type, asset_event >
   {
      public:
         template< typename Constructor, typename Allocator >
         asset_event( Constructor&& c, allocator< Allocator > a )
          : title(a), body(a)
         {
            c( *this );
         }

         id_type              id;
         asset_name_type      asset;
         shared_string        title;
         shared_string        body;
         time_point_sec       created;
         transaction_id_type  created_tx;
   };

   typedef oid< asset_event > asset_event_id_type;

   struct by_id;
   struct by_name;
   struct by_owner;
   struct by_asset_name;

   typedef multi_index_container <
      asset_object,
      indexed_by <
         ordered_unique < tag < by_id >,
            member < asset_object, asset_object_id_type, &asset_object::id >
         >,
         ordered_unique < tag < by_name >,
            member < asset_object, asset_name_type, &asset_object::asset_name >
         >,
         ordered_non_unique < tag < by_owner >,
            member < asset_object, account_name_type, &asset_object::owner >
         >
      >,
      chainbase::allocator < asset_object >
   > asset_object_index;

   typedef multi_index_container <
      asset_event,
      indexed_by <
         ordered_unique < tag< by_id >
            , member< asset_event, asset_event_id_type, &asset_event::id > 
         >,
         ordered_non_unique < tag< by_asset_name >
            , member< asset_event, asset_name_type, &asset_event::asset > 
         >
      > ,
      chainbase::allocator< asset_event >
   > asset_event_index;

} } // namespace fiberchain::asset_storage

FC_REFLECT( fiberchain::asset_storage::asset_object,
   ( id )
   ( asset_name )
   ( asset_data )
   ( owner )
   ( created )
   ( created_tx )
)

FC_REFLECT(fiberchain::asset_storage::asset_event,
   ( id )
   ( asset )
   ( title )
   ( body )
   ( created )
   ( created_tx )
)

CHAINBASE_SET_INDEX_TYPE( fiberchain::asset_storage::asset_object, fiberchain::asset_storage::asset_object_index )
CHAINBASE_SET_INDEX_TYPE( fiberchain::asset_storage::asset_event, fiberchain::asset_storage::asset_event_index )
