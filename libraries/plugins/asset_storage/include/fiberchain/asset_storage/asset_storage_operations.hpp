#pragma once

#include <fiberchain/protocol/base.hpp>
#include <fiberchain/app/plugin.hpp>
#include <fiberchain/asset_storage/asset_storage_objects.hpp>

namespace fiberchain { namespace asset_storage {
   using namespace std;
   using fiberchain::protocol::base_operation;
   using namespace fiberchain::chain;
   using namespace fiberchain::protocol;

   class asset_storage_plugin;

   struct create_asset_operation : base_operation
   {
      account_name_type                owner;
      asset_name_type                  asset_name;
      string                           asset_data;

      void validate()const;
      void get_required_active_authorities( flat_set< account_name_type >& a )const { a.insert( owner );}
   };

   struct create_asset_event_operation : base_operation
   {
      asset_name_type         asset;
      account_name_type       author;
      string                  title;
      string                  body;

      void validate()const;
      void get_required_active_authorities( flat_set< account_name_type >& a )const { a.insert( author );}
   };

   typedef fc::static_variant< 
      create_asset_operation
      , create_asset_event_operation
   > asset_storage_operation;

   DEFINE_PLUGIN_EVALUATOR( asset_storage_plugin, asset_storage_operation, create_asset )
   DEFINE_PLUGIN_EVALUATOR( asset_storage_plugin, asset_storage_operation, create_asset_event )

} } // namespace fiberchain::asset_storage

FC_REFLECT( fiberchain::asset_storage::create_asset_operation,
   ( owner )
   ( asset_name )
   ( asset_data )
   )

FC_REFLECT( fiberchain::asset_storage::create_asset_event_operation,
   ( asset )
   ( author ) 
   ( title )
   ( body )
   )

DECLARE_OPERATION_TYPE( fiberchain::asset_storage::asset_storage_operation )

FC_REFLECT_TYPENAME( fiberchain::asset_storage::asset_storage_operation )
