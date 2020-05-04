#include <futurepia/asset_storage/asset_storage_plugin.hpp>
#include <futurepia/asset_storage/asset_storage_api.hpp>

#include <futurepia/protocol/hardfork.hpp>

#include <futurepia/chain/generic_custom_operation_interpreter.hpp>
#include <futurepia/chain/index.hpp>

#include <memory>

namespace fiberchain { namespace asset_storage {
   namespace detail {
      class asset_storage_plugin_impl
      {
         public:
            asset_storage_plugin_impl( asset_storage_plugin& _plugin ) : _self( _plugin ) {}

            void plugin_initialize();

            fiberchain::chain::database& database()
            {
               return _self.database();
            }

            void on_apply_hardfork( const uint32_t hardfork );
            void on_apply_block( const signed_block& b );
            void on_pre_apply_transaction( const signed_transaction& tx );

            const signed_transaction* get_current_tx() const;
         private:
            asset_storage_plugin&  _self;
            std::shared_ptr< generic_custom_operation_interpreter< fiberchain::asset_storage::asset_storage_operation > > _custom_op_interpreter;
            const signed_transaction* _currentTx;
      };

      void asset_storage_plugin_impl::plugin_initialize() 
      {
         _custom_op_interpreter = std::make_shared< generic_custom_operation_interpreter< fiberchain::asset_storage::asset_storage_operation > >( database() );
         _custom_op_interpreter->register_evaluator< create_asset_evaluator >( &_self );
         _custom_op_interpreter->register_evaluator< create_asset_event_evaluator >( &_self );

         database().set_custom_operation_interpreter( _self.plugin_name(), _custom_op_interpreter );
      }

      void asset_storage_plugin_impl::on_apply_hardfork( const uint32_t hardfork ) {
         //Check hardfork params and update database
      }

      void asset_storage_plugin_impl::on_apply_block( const signed_block& b ) {
         // Perform ongoing and periodic operations
      }

      void asset_storage_plugin_impl::on_pre_apply_transaction( const signed_transaction& tx ) {
         _currentTx = &tx;
      }

      const signed_transaction* asset_storage_plugin_impl::get_current_tx() const {
         return _currentTx;
      }
   } //namespace detail

   asset_storage_plugin::asset_storage_plugin( application* app ) 
   : plugin( app ), _my( new detail::asset_storage_plugin_impl( *this ) ) {}

   void asset_storage_plugin::plugin_initialize( const boost::program_options::variables_map& options )
   {
      try 
      {
         ilog( "Intializing asset storage plugin" );

         _my->plugin_initialize();

         chain::database& db = database();
         add_plugin_index < asset_object_index > ( db );
         add_plugin_index < asset_event_index > ( db );

         db.on_apply_hardfork.connect( [&]( const uint32_t hardfork ){ 
            _my->on_apply_hardfork( hardfork ); 
         });

         db.applied_block.connect( [&]( const signed_block& b ){ 
            _my->on_apply_block( b ); 
         });

         db.on_pre_apply_transaction.connect( [&]( const signed_transaction& tx ){ 
            _my->on_pre_apply_transaction( tx ); 
         });

      } FC_CAPTURE_AND_RETHROW()
   }

   void asset_storage_plugin::plugin_startup()
   {
      app().register_api_factory< asset_api >( "asset_storage_api" );
   }

   const signed_transaction* asset_storage_plugin::get_current_tx() const
   {
      return _my->get_current_tx();
   }

} } //namespace fiberchain::asset_storage

FUTUREPIA_DEFINE_PLUGIN( asset_storage, fiberchain::asset_storage::asset_storage_plugin )
