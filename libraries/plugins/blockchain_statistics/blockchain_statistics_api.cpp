#include <futurepia/blockchain_statistics/blockchain_statistics_api.hpp>

namespace fiberchain { namespace blockchain_statistics {

namespace detail
{
   class blockchain_statistics_api_impl
   {
      public:
         blockchain_statistics_api_impl( fiberchain::app::application& app )
            :_app( app ) {}

         statistics get_stats_for_time( fc::time_point_sec open, uint32_t interval )const;
         statistics get_stats_for_interval( fc::time_point_sec start, fc::time_point_sec end )const;
         statistics get_lifetime_stats()const;

         fiberchain::app::application& _app;
   };

   statistics blockchain_statistics_api_impl::get_stats_for_time( fc::time_point_sec open, uint32_t interval )const
   {
      statistics result;
      const auto& bucket_idx = _app.chain_database()->get_index< bucket_index >().indices().get< by_bucket >();
      auto itr = bucket_idx.lower_bound( boost::make_tuple( interval, open ) );

      if( itr != bucket_idx.end() )
         result += *itr;

      return result;
   }

   statistics blockchain_statistics_api_impl::get_stats_for_interval( fc::time_point_sec start, fc::time_point_sec end )const
   {
      statistics result;
      const auto& bucket_itr = _app.chain_database()->get_index< bucket_index >().indices().get< by_bucket >();
      const auto& sizes = _app.get_plugin< blockchain_statistics_plugin >( BLOCKCHAIN_STATISTICS_PLUGIN_NAME )->get_tracked_buckets();
      auto size_itr = sizes.rbegin();
      auto time = start;

      // This is a greedy algorithm, same as the ubiquitous "making change" problem.
      // So long as the bucket sizes share a common denominator, the greedy solution
      // has the same efficiency as the dynamic solution.
      while( size_itr != sizes.rend() && time < end )
      {
         auto itr = bucket_itr.find( boost::make_tuple( *size_itr, time ) );

         while( itr != bucket_itr.end() && itr->seconds == *size_itr && time + itr->seconds <= end )
         {
            time += *size_itr;
            result += *itr;
            itr++;
         }

         size_itr++;
      }

      return result;
   }

   statistics blockchain_statistics_api_impl::get_lifetime_stats()const
   {
      statistics result;
      result += _app.chain_database()->get( bucket_id_type() );

      return result;
   }
} // detail

blockchain_statistics_api::blockchain_statistics_api( const fiberchain::app::api_context& ctx )
{
   my = std::make_shared< detail::blockchain_statistics_api_impl >( ctx.app );
}

void blockchain_statistics_api::on_api_startup() {}

statistics blockchain_statistics_api::get_stats_for_time( fc::time_point_sec open, uint32_t interval )const
{
   return my->_app.chain_database()->with_read_lock( [&]()
   {
      return my->get_stats_for_time( open, interval );
   });
}

statistics blockchain_statistics_api::get_stats_for_interval( fc::time_point_sec start, fc::time_point_sec end )const
{
   return my->_app.chain_database()->with_read_lock( [&]()
   {
      return my->get_stats_for_interval( start, end );
   });
}

statistics blockchain_statistics_api::get_lifetime_stats()const
{
   return my->_app.chain_database()->with_read_lock( [&]()
   {
      return my->get_lifetime_stats();
   });
}

statistics& statistics::operator +=( const bucket_object& b )
{
   this->blocks                                 += b.blocks;
   this->bandwidth                              += b.bandwidth;
   this->operations                             += b.operations;
   this->transactions                           += b.transactions;
   this->transfers                              += b.transfers;
   this->pia_transferred                        += b.pia_transferred;
   this->snac_transferred                       += b.snac_transferred;
   this->accounts_created                       += b.accounts_created;
   this->total_comments                         += b.root_comments + b.replies;
   this->total_comment_edits                    += b.root_comment_edits + b.reply_edits;
   this->total_comments_deleted                 += b.root_comments_deleted + b.replies_deleted;
   this->root_comments                          += b.root_comments;
   this->root_comment_edits                     += b.root_comment_edits;
   this->root_comments_deleted                  += b.root_comments_deleted;
   this->replies                                += b.replies;
   this->reply_edits                            += b.reply_edits;
   this->replies_deleted                        += b.replies_deleted;
   this->total_votes                            += b.new_root_votes + b.new_reply_votes;
   this->new_votes                              += b.new_root_votes + b.new_reply_votes;
   this->total_root_votes                       += b.new_root_votes;
   this->new_root_votes                         += b.new_root_votes;
   this->total_reply_votes                      += b.new_reply_votes ;
   this->new_reply_votes                        += b.new_reply_votes;
   this->like_count                             += b.like_count;
   this->dislike_count                          += b.dislike_count;
   this->recommend_count                        += b.recommend_count;
   this->betting_count                          += b.betting_count;
   this->snac_conversion_requests_created       += b.snac_conversion_requests_created;
   this->snac_to_be_converted                   += b.snac_to_be_converted;
   this->snac_conversion_requests_filled        += b.snac_conversion_requests_filled;
   this->pia_converted                          += b.pia_converted;

   return ( *this );
}

} } // fiberchain::blockchain_statistics
