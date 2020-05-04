#include <futurepia/bobserver/bobserver_operations.hpp>

#include <futurepia/protocol/operation_util_impl.hpp>

namespace fiberchain { namespace bobserver {

void enable_content_editing_operation::validate()const
{
   chain::validate_account_name( account );
}

} } // fiberchain::bobserver

DEFINE_OPERATION_TYPE( fiberchain::bobserver::bobserver_plugin_operation )
