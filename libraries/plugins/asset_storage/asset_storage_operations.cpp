#include <futurepia/asset_storage/asset_storage_operations.hpp>

#include <futurepia/protocol/operation_util_impl.hpp>
#include <futurepia/protocol/authority.hpp>

namespace futurepia { namespace asset_storage {
   
   void create_asset_operation::validate()const
   {
      try {
         FC_ASSERT( is_valid_account_name( owner ), "Account name ${n} is invalid", ("n", owner) );
         FC_ASSERT( asset_name.size() > 0 );
         FC_ASSERT( asset_data.size() > 0 );
      } FC_CAPTURE_AND_RETHROW( ( *this ) )
   }

   void create_asset_event_operation::validate()const
   {
      try {
         FC_ASSERT( is_valid_account_name( author ), "Account name ${n} is invalid", ("n", author) );
         FC_ASSERT( asset.size() > 0 );
         FC_ASSERT(title.size() < 256, "Title larger than size limit");
         FC_ASSERT(fc::is_utf8(title), "Title not formatted in UTF8");
         FC_ASSERT(body.size() > 0, "Body is empty");
         FC_ASSERT(fc::is_utf8(body), "Body not formatted in UTF8");
      } FC_CAPTURE_AND_RETHROW( ( *this ) )
   }

} } //namespace futurepia::asset_storage

DEFINE_OPERATION_TYPE( futurepia::asset_storage::asset_storage_operation )
