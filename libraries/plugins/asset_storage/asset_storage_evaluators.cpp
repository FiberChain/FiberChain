#include <futurepia/asset_storage/asset_storage_operations.hpp>
#include <futurepia/asset_storage/asset_storage_plugin.hpp>
#include <futurepia/chain/database.hpp>
#include <futurepia/chain/account_object.hpp>

namespace futurepia { namespace asset_storage {

   void create_asset_evaluator::do_apply( const create_asset_operation& op )
   {
      try 
      {
         ilog( "create_asset_evaluator::do_apply" );

         database& _db = db();
         const signed_transaction* trx = _plugin->get_current_tx();

         const auto& owner_idx = _db.get_index< account_index >().indicies().get< chain::by_name >();
         auto owner_ptr = owner_idx.find( op.owner );
         FC_ASSERT( owner_ptr != owner_idx.end(), "${owner} accounts does not exist", ( "owner", op.owner ) );

         const auto& name_idx = _db.get_index< asset_object_index >().indices().get< by_name >();
         auto name_itr = name_idx.find( op.asset_name );

         FC_ASSERT( name_itr == name_idx.end(), "${name} asset already exists", ( "name", op.asset_name ) );

         auto now_time = _db.head_block_time();
         _db.create< asset_object > ( [&]( asset_object& asset_obj ) {
               asset_obj.asset_name = op.asset_name;
               asset_obj.owner = op.owner;
               from_string( asset_obj.asset_data, op.asset_data );
               asset_obj.created = now_time;
               asset_obj.created_tx = trx->id();
            }
         );
      }
      FC_CAPTURE_AND_RETHROW( ( op ) )
   }

   void create_asset_event_evaluator::do_apply( const create_asset_event_operation& op )
   {
      try 
      {
         ilog( "create_asset_event_evaluator::do_apply" );

         database& _db = db();
         const signed_transaction* trx = _plugin->get_current_tx();

         const auto& owner_idx = _db.get_index< account_index >().indicies().get< chain::by_name >();
         auto owner_ptr = owner_idx.find( op.author );
         FC_ASSERT( owner_ptr != owner_idx.end(), "${owner} accounts does not exist", ( "owner", op.author ) );

         const auto& name_idx = _db.get_index< asset_object_index >().indices().get< by_name >();
         auto name_itr = name_idx.find( op.asset );

         FC_ASSERT( name_itr != name_idx.end(), "${name} asset does not exist", ( "name", op.asset ) );

         auto now_time = _db.head_block_time();
         _db.create< asset_event > ( [&]( asset_event& event_obj ) {
               event_obj.asset = op.asset;
               from_string( event_obj.title, op.title );
               from_string( event_obj.body, op.body );
               event_obj.created = now_time;
               event_obj.created_tx = trx->id();
            }
         );
      } 
      FC_CAPTURE_AND_RETHROW( ( op ) )
   }

} } // namespace futurepia::asset_storage

