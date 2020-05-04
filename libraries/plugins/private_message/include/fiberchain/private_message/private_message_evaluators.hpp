#pragma once

#include <fiberchain/chain/evaluator.hpp>

#include <fiberchain/private_message/private_message_operations.hpp>
#include <fiberchain/private_message/private_message_plugin.hpp>

namespace fiberchain { namespace private_message {

DEFINE_PLUGIN_EVALUATOR( private_message_plugin, fiberchain::private_message::private_message_plugin_operation, private_message )

} }
