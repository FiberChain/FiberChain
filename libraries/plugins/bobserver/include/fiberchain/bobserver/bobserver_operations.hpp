#pragma once

#include <fiberchain/protocol/base.hpp>
#include <fiberchain/protocol/operation_util.hpp>

#include <fiberchain/app/plugin.hpp>

namespace fiberchain { namespace bobserver {

using namespace std;
using fiberchain::protocol::base_operation;
using fiberchain::chain::database;

class bobserver_plugin;

struct enable_content_editing_operation : base_operation
{
   protocol::account_name_type   account;
   fc::time_point_sec            relock_time;

   void validate()const;

   void get_required_active_authorities( flat_set< protocol::account_name_type>& a )const { a.insert( account ); }
};

typedef fc::static_variant<
         enable_content_editing_operation
      > bobserver_plugin_operation;

DEFINE_PLUGIN_EVALUATOR( bobserver_plugin, bobserver_plugin_operation, enable_content_editing );

} } // fiberchain::bobserver

FC_REFLECT( fiberchain::bobserver::enable_content_editing_operation, (account)(relock_time) )

FC_REFLECT_TYPENAME( fiberchain::bobserver::bobserver_plugin_operation )

DECLARE_OPERATION_TYPE( fiberchain::bobserver::bobserver_plugin_operation )
