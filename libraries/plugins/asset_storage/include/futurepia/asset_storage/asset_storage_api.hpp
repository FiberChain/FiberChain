#pragma once
#include <futurepia/app/application.hpp>
#include <futurepia/asset_storage/asset_storage_objects.hpp>

#include <futurepia/chain/account_object.hpp>

#include <fc/api.hpp>
namespace futurepia { namespace asset_storage {

   struct asset_api_object
   {
      asset_api_object() {}
      asset_api_object( const asset_object& o ) 
         : asset_name( o.asset_name ),
            asset_title( to_string(o.asset_title) ),
            owner( o.owner ),
            created( o.created ),
            created_tx( o.created_tx )
            {}

      asset_name_type         asset_name;
      string                  asset_title;
      account_name_type       owner;
      time_point_sec          created;
      transaction_id_type     created_tx;
   };

   struct asset_event_api_object
   {
      asset_event_api_object() {}
      asset_event_api_object( const asset_event& o ) 
         : asset( o.asset ),
            title( to_string(o.title) ),
            body( to_string(o.body) ),
            created( o.created ),
            created_tx( o.created_tx )
            {}

      asset_name_type      asset;
      string               title;
      string               body;
      time_point_sec       created;
      transaction_id_type  created_tx;
   };

   namespace detail 
   { 
      class asset_api_impl; 
   }

   class asset_api 
   {
      public:
         asset_api( const app::api_context& ctx );
         void on_api_startup();

         /**
          * get list of assets
          * @param asset_name search keyword
          * @param limit max count to read from db. limit is 100 or less.
          * @return assets information
          * */
         optional< asset_api_object > get_asset_by_name( string asset_name ) const;

         /**
          * get list of assets owned by an owner
          * @param owner owner name
          * @return assets information
          * */
         vector< asset_api_object > get_assets_by_owner( string owner ) const;

         /**
          * get list of asset events
          * @param asset_name asset name
          * @param limit max count to read from db. limit is 100 or less.
          * @return list of events for asset
          * */
         vector< asset_event_api_object > get_asset_events( string asset_name ) const;

      private:
         std::shared_ptr< detail::asset_api_impl > _my;
   };

} } // namespace futurepia::asset_storage

FC_REFLECT( futurepia::asset_storage::asset_api_object, 
   ( asset_name )
   ( owner )
   ( created )
   ( created_tx )
)

FC_REFLECT( futurepia::asset_storage::asset_event_api_object, 
   ( asset )
   ( title ) 
   ( body )
   ( created )
   ( created_tx )
)

FC_API( futurepia::asset_storage::asset_api,
   ( get_asset_by_name )
   ( get_assets_by_owner )
   ( get_asset_events )
)
