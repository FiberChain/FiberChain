#include <futurepia/asset_storage/asset_storage_operations.hpp>
#include <futurepia/asset_storage/asset_storage_plugin.hpp>
#include <futurepia/chain/database.hpp>
#include <futurepia/chain/account_object.hpp>

#ifndef IS_LOW_MEM
#include <diff_match_patch.h>
#include <boost/locale/encoding_utf.hpp>

using boost::locale::conv::utf_to_utf;

#endif

namespace futurepia { namespace asset_storage {

   std::wstring utf8_to_wstring(const std::string& str)
   {
      return utf_to_utf<wchar_t>(str.c_str(), str.c_str() + str.size());
   }

   std::string wstring_to_utf8(const std::wstring& str)
   {
      return utf_to_utf<char>(str.c_str(), str.c_str() + str.size());
   }

   void create_asset_evaluator::do_apply( const create_asset_operation& op )
   {
      try 
      {
         ilog( "create_asset_evaluator::do_apply" );

         database& _db = db();

         const auto& owner_idx = _db.get_index< account_index >().indicies().get< chain::by_name >();
         auto owner_ptr = owner_idx.find( op.owner );
         FC_ASSERT( owner_ptr != owner_idx.end(), "${owner} accounts does not exist", ( "owner", op.owner ) );

         const auto& name_idx = _db.get_index< asset_index >().indices().get< by_name >();
         auto name_itr = name_idx.find( op.asset_name );

         FC_ASSERT( name_itr == name_idx.end(), "${name} asset already exists", ( "name", op.asset_name ) );

         auto now_time = _db.head_block_time();
         auto asset = _db.create< asset_object > ( [&]( asset_object& asset_obj ) {
               asset_obj.asset_name = op.asset_name;
               asset_obj.asset_title = op.asset_title;
               asset_obj.owner = op.owner;
               asset_obj.created = now_time;
               asset_obj.created_tx = now_time;
            }
         );

         if( _db.has_hardfork( FUTUREPIA_HARDFORK_0_2 ) ) {  
            // owner add to member
            _db.create< dapp_user_object >( [&]( dapp_user_object& object ) {
               object.dapp_id = dapp.id;
               object.dapp_name = op.dapp_name;
               object.account_id = owner_ptr->id;
               object.account_name = op.owner;
               object.join_date_time = now_time;
            });
         }

      } 
      FC_CAPTURE_AND_RETHROW( ( op ) )
   }

   void create_asset_event_evaluator::do_apply( const create_dapp_operation& op )
   {
      try 
      {
         ilog( "create_dapp_evaluator::do_apply" );

         database& _db = db();

         const auto& owner_idx = _db.get_index< account_index >().indicies().get< chain::by_name >();
         auto owner_ptr = owner_idx.find( op.owner );
         FC_ASSERT( owner_ptr != owner_idx.end(), "${owner} accounts is not exist", ( "owner", op.owner ) );

         const auto& name_idx = _db.get_index< dapp_index >().indices().get< by_name >();
         auto name_itr = name_idx.find( op.dapp_name );

         FC_ASSERT( name_itr == name_idx.end(), "${name} dapp is exist", ( "name", op.dapp_name ) );

         auto now_time = _db.head_block_time();
         auto dapp = _db.create< asset_object > ( [&]( asset_object& dapp_obj ) {
               dapp_obj.dapp_name = op.dapp_name;
               dapp_obj.owner = op.owner;
               dapp_obj.dapp_key = *op.dapp_key;
               dapp_obj.dapp_state = dapp_state_type::APPROVAL;
               dapp_obj.created = now_time;
               dapp_obj.last_updated = now_time;
            }
         );

         if( _db.has_hardfork( FUTUREPIA_HARDFORK_0_2 ) ) {  
            // owner add to member
            _db.create< dapp_user_object >( [&]( dapp_user_object& object ) {
               object.dapp_id = dapp.id;
               object.dapp_name = op.dapp_name;
               object.account_id = owner_ptr->id;
               object.account_name = op.owner;
               object.join_date_time = now_time;
            });
         }

      } 
      FC_CAPTURE_AND_RETHROW( ( op ) )
   }

} } // namespace futurepia::dapp

