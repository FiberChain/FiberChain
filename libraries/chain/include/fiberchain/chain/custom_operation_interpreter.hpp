
#pragma once

#include <memory>
#include <boost/container/flat_set.hpp>
#include <fiberchain/chain/database.hpp>

namespace graphene { namespace schema {
   struct abstract_schema;
} }

namespace fiberchain { namespace protocol {
   struct custom_json_operation;
   struct custom_json_hf2_operation;
   struct custom_binary_operation;
} }

namespace fiberchain { namespace chain {

class custom_operation_interpreter
{
   public:
      virtual void apply( const protocol::custom_json_operation& op ) = 0;
      virtual void apply( const protocol::custom_json_hf2_operation& op ) = 0;
      virtual void apply( const protocol::custom_binary_operation & op ) = 0;
      virtual std::shared_ptr< graphene::schema::abstract_schema > get_operation_schema() = 0;
};

} } // fiberchain::chain
