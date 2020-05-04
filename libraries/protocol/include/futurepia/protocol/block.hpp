#pragma once
#include <futurepia/protocol/block_header.hpp>
#include <futurepia/protocol/transaction.hpp>

namespace fiberchain { namespace protocol {

   struct signed_block : public signed_block_header
   {
      checksum_type calculate_merkle_root()const;
      vector<signed_transaction> transactions;
   };

} } // fiberchain::protocol

FC_REFLECT_DERIVED( fiberchain::protocol::signed_block, (fiberchain::protocol::signed_block_header), (transactions) )
