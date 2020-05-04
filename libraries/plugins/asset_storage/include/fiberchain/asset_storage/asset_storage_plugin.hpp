#pragma once

#include <fiberchain/app/plugin.hpp>
#include <fiberchain/asset_storage/asset_storage_operations.hpp>

#define ASSET_PLUGIN_NAME "asset_storage"

namespace fiberchain { namespace asset_storage {
   using fiberchain::app::application;

   namespace detail { class asset_storage_plugin_impl; }

   class asset_storage_plugin : public fiberchain::app::plugin
   {
      public:
         asset_storage_plugin( application* app );

         std::string plugin_name()const override { return ASSET_PLUGIN_NAME; }
         virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;
         virtual void plugin_startup() override;
         const signed_transaction* get_current_tx() const;

         friend class detail::asset_storage_plugin_impl;
         
      private:
         std::unique_ptr<detail::asset_storage_plugin_impl> _my;
   };

} } //namespace fiberchain::asset_storage

