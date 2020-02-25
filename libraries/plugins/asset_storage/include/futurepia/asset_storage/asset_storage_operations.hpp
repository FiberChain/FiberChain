#pragma once

#include <futurepia/protocol/base.hpp>
#include <futurepia/app/plugin.hpp>
#include <futurepia/asset_storage/asset_storage_objects.hpp>

namespace futurepia { namespace asset_storage {
   using namespace std;
   using futurepia::protocol::base_operation;
   using namespace futurepia::chain;
   using namespace futurepia::protocol;

   class asset_storage_plugin;

   struct create_asset_operation : base_operation
   {
      account_name_type                owner;
      asset_name_type                  asset_name;

      void validate()const;
      void get_required_active_authorities( flat_set< account_name_type >& a )const { a.insert( owner );}
   };

   struct create_asset_event_operation : base_operation
   {
      asset_object_id_type    asset_id;
      account_name_type       author;
      string                  title;
      string                  body;

      void validate()const;
      void get_required_posting_authorities( flat_set< account_name_type >& a )const { a.insert( author );}
   };

   typedef fc::static_variant< 
      create_asset_operation
      , create_asset_event_operation
   > asset_storage_operation;

   DEFINE_PLUGIN_EVALUATOR( asset_storage_plugin, asset_storage_operation, create_asset )
   DEFINE_PLUGIN_EVALUATOR( asset_storage_plugin, asset_storage_operation, create_asset_event )

} } // namespace futurepia::asset_storage

FC_REFLECT( futurepia::asset_storage::create_asset_operation,
   ( owner )
   ( asset_name )
   )

FC_REFLECT( futurepia::asset_storage::create_asset_event_operation,
   ( asset_id )
   ( author ) 
   ( title )
   ( body )
   )

DECLARE_OPERATION_TYPE( futurepia::asset_storage::asset_storage_operation )

FC_REFLECT_TYPENAME( futurepia::asset_storage::asset_storage_operation )