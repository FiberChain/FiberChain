#pragma once

#include <fiberchain/account_statistics/account_statistics_plugin.hpp>

#include <fc/api.hpp>

namespace fiberchain{ namespace app {
   struct api_context;
} }

namespace fiberchain { namespace account_statistics {

namespace detail
{
   class account_statistics_api_impl;
}

class account_statistics_api
{
   public:
      account_statistics_api( const fiberchain::app::api_context& ctx );

      void on_api_startup();

   private:
      std::shared_ptr< detail::account_statistics_api_impl > _my;
};

} } // fiberchain::account_statistics

FC_API( fiberchain::account_statistics::account_statistics_api, )