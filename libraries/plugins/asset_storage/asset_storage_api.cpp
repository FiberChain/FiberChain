#include <futurepia/asset_storage/asset_storage_api.hpp>
#include <futurepia/app/state.hpp>

#include <functional>

namespace fiberchain { namespace asset_storage {

   namespace detail {
      class asset_api_impl
      {
         public:
            asset_api_impl( fiberchain::app::application& app ):_app( app ) {}

            optional< asset_api_object > get_asset_by_name( string asset_name ) const;
            vector< asset_api_object > get_assets_by_owner( string owner ) const;
            vector< asset_event_api_object > get_asset_events( string asset_name ) const;

            fiberchain::chain::database& database() { return *_app.chain_database(); }

         private:
            fiberchain::app::application& _app;
      };

      optional< asset_api_object > asset_api_impl::get_asset_by_name( string asset_name ) const
      {
         const auto& asset_idx = _app.chain_database()->get_index< asset_object_index >().indices().get< by_name >();
         auto itr = asset_idx.find( asset_name );
         if( itr != asset_idx.end() )
            return asset_api_object( *itr );
         else 
            return {};
      }

      vector< asset_api_object > asset_api_impl::get_assets_by_owner( string owner ) const
      {
         vector < asset_api_object > results;

         const auto& asset_idx = _app.chain_database()->get_index< asset_object_index >().indices().get < by_owner >();
         auto itr = asset_idx.find( owner );
         while( itr != asset_idx.end() && itr->owner == owner )
         {
            results.push_back( *itr );
            itr++;
         }

         return results;
      }

      vector< asset_event_api_object > asset_api_impl::get_asset_events( string asset_name )const
      {
         vector < asset_event_api_object > results;

         const auto& asset_idx = _app.chain_database()->get_index< asset_event_index >().indices().get < by_asset_name >();
         auto itr = asset_idx.find( asset_name );
         while( itr != asset_idx.end() && itr->asset == asset_name )
         {
            results.push_back( *itr );
            itr++;
         }

         return results;
      }

   } //namespace fiberchain::asset_storage::detail

   asset_api::asset_api( const fiberchain::app::api_context& ctx )
   {
      _my = std::make_shared< detail::asset_api_impl >( ctx.app );
   }

   void asset_api::on_api_startup() {}

   optional< asset_api_object > asset_api::get_asset_by_name( string asset_name ) const
   {
      return _my->database().with_read_lock( [ & ]()
      {
         return _my->get_asset_by_name( asset_name );
      });
   }

   vector< asset_api_object > asset_api::get_assets_by_owner( string owner ) const
   {
      return _my->database().with_read_lock( [ & ]()
      {
         return _my->get_assets_by_owner( owner );
      });
   }

   vector< asset_event_api_object > asset_api::get_asset_events( string asset_name ) const
   {
      return _my->database().with_read_lock( [ & ]()
      {
         return _my->get_asset_events( asset_name );
      });
   }

}} //namespace fiberchain::asset_storage
