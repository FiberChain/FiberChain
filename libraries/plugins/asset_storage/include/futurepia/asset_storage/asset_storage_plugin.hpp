#pragma once

#include <futurepia/app/plugin.hpp>
#include <futurepia/dapp/dapp_operations.hpp>

#define ASSET_PLUGIN_NAME "asset_storage"

namespace futurepia { namespace asset_storage {
   using futurepia::app::application;

   namespace detail { class asset_storage_plugin_impl; }

   class asset_storage_plugin : public futurepia::app::plugin
   {
      public:
         asset_storage_plugin( application* app );

         std::string plugin_name()const override { return ASSET_PLUGIN_NAME; }
         virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;
         virtual void plugin_startup() override;

         friend class detail::asset_storage_plugin_impl;
         
      private:
         std::unique_ptr<detail::asset_storage_plugin_impl> _my;
   };

} } //namespace futurepia::dapp

