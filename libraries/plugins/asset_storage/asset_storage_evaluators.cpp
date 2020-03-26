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

   void create_asset_evaluator::do_apply( const create_asset_operation& op, const signed_transaction& trx )
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
               asset_obj.created_tx = trx.id();
            }
         );
      }
      FC_CAPTURE_AND_RETHROW( ( op ) )
   }

   void create_asset_event_evaluator::do_apply( const create_asset_event_operation& op, const signed_transaction& trx )
   {
      try 
      {
         ilog( "create_asset_event_evaluator::do_apply" );

         database& _db = db();

         const auto& owner_idx = _db.get_index< account_index >().indicies().get< chain::by_name >();
         auto owner_ptr = owner_idx.find( op.author );
         FC_ASSERT( owner_ptr != owner_idx.end(), "${owner} accounts does not exist", ( "owner", op.author ) );

         const auto& name_idx = _db.get_index< asset_index >().indices().get< by_name >();
         auto name_itr = name_idx.find( op.asset );

         FC_ASSERT( name_itr != name_idx.end(), "${name} asset does not exist", ( "name", op.asset ) );

         auto now_time = _db.head_block_time();
         auto event = _db.create< asseet_event_object > ( [&]( asseet_event_object& event_obj ) {
               event_obj.asset = op.asset;
               event_obj.title = op.title;
               event_obj.body = op.body;
               event_obj.created = now_time;
               event_obj.created_tx = trx.id();
            }
         );
      } 
      FC_CAPTURE_AND_RETHROW( ( op ) )
   }

} } // namespace futurepia::dapp

