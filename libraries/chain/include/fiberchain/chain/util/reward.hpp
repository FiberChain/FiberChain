#pragma once

#include <fiberchain/chain/util/asset.hpp>
#include <fiberchain/chain/fiberchain_objects.hpp>

#include <fiberchain/protocol/asset.hpp>
#include <fiberchain/protocol/config.hpp>
#include <fiberchain/protocol/types.hpp>

#include <fc/reflect/reflect.hpp>

#include <fc/uint128.hpp>

namespace fiberchain { namespace chain { namespace util {

using fiberchain::protocol::asset;
using fiberchain::protocol::price;
using fiberchain::protocol::share_type;

using fc::uint128_t;

struct comment_reward_context
{
   asset      max_snac;
   price      current_pia_price;
};

} } } // fiberchain::chain::util

FC_REFLECT( fiberchain::chain::util::comment_reward_context,
   (max_snac)
   (current_pia_price)
   )
