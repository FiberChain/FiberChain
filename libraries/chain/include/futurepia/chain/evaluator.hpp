#pragma once
#include <futurepia/protocol/exceptions.hpp>
#include <futurepia/protocol/operations.hpp>

namespace futurepia { namespace chain {

class database;

template< typename OperationType=futurepia::protocol::operation >
class evaluator
{
   public:
      virtual void apply(const OperationType& op, const signed_transaction& trx) = 0;
      virtual int get_type()const = 0;
};

template< typename EvaluatorType, typename OperationType=futurepia::protocol::operation >
class evaluator_impl : public evaluator<OperationType>
{
   public:
      typedef OperationType operation_sv_type;
      // typedef typename EvaluatorType::operation_type op_type;

      evaluator_impl( database& d )
         : _db(d) {}

      virtual void apply(const OperationType& o, const signed_transaction& trx) final override
      {
         const auto& op = o.template get< typename EvaluatorType::operation_type >();
         do_apply(op, trx);
      }

      virtual void do_apply(const OperationType& op, const signed_transaction& trx)
      {
         auto* eval = static_cast< EvaluatorType* >(this);
         eval->do_apply(op);
      }

      virtual int get_type()const override { return OperationType::template tag< typename EvaluatorType::operation_type >::value; }

      database& db() { return _db; }

   protected:
      database& _db;
};

} }

#define DEFINE_EVALUATOR( X ) \
class X ## _evaluator : public futurepia::chain::evaluator_impl< X ## _evaluator > \
{                                                                           \
   public:                                                                  \
      typedef X ## _operation operation_type;                               \
                                                                            \
      X ## _evaluator( database& db )                                       \
         : futurepia::chain::evaluator_impl< X ## _evaluator >( db )          \
      {}                                                                    \
                                                                            \
      void do_apply( const X ## _operation& o );                            \
};
