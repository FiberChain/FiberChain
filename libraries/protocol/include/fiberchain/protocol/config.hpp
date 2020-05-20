#pragma once

#include <fiberchain/protocol/hardfork.hpp>

#define FIBERCHAIN_VERSION                                         ( version(0, 2, 575) )

#define FIBERCHAIN_BLOCKCHAIN_VERSION                              ( version(0, 2, 0) )
#define FIBERCHAIN_BLOCKCHAIN_HARDFORK_VERSION                     ( hardfork_version( FIBERCHAIN_BLOCKCHAIN_VERSION ) )

#define FIBERCHAIN_BLOCKCHAIN_PRECISION_DIGITS                     8
#define FIBERCHAIN_BLOCKCHAIN_SNAC_PRECISION_DIGITS                3

#define FIBERCHAIN_INIT_PRIVATE_KEY                                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("fiberchain"))))
#define FIBERCHAIN_INIT_PUBLIC_KEY_STR                             (std::string( fiberchain::protocol::public_key_type(FIBERCHAIN_INIT_PRIVATE_KEY.get_public_key()) ))
#define FIBERCHAIN_CHAIN_ID                                        (fc::sha256::hash("fiberchain_testnet"))
#define PIA_SYMBOL                                                (uint64_t(FIBERCHAIN_BLOCKCHAIN_PRECISION_DIGITS) | (uint64_t('T') << 8) | (uint64_t('I') << 16) | (uint64_t('A') << 24) )///< PIA with 8 digits of precision
#define SNAC_SYMBOL                                               (uint64_t(FIBERCHAIN_BLOCKCHAIN_SNAC_PRECISION_DIGITS) | (uint64_t('T') << 8) | (uint64_t('N') << 16) | (uint64_t('A') << 24) | (uint64_t('C') << 32) ) ///< SNAC with 8 digits of precision
#define FIBERCHAIN_ADDRESS_PREFIX                                  "TPA"
#define FIBERCHAIN_GENESIS_TIME                                    (fc::time_point_sec(1550475176))
#define FIBERCHAIN_MINING_TIME                                     (fc::time_point_sec(1550475177))
#define FIBERCHAIN_OWNER_AUTH_RECOVERY_PERIOD                      fc::seconds(60)
#define FIBERCHAIN_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD      fc::seconds(12)
#define FIBERCHAIN_OWNER_UPDATE_LIMIT                              fc::seconds(0)
#define FIBERCHAIN_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM     1

#define FIBERCHAIN_BLOCK_INTERVAL                                  3
#define FIBERCHAIN_BLOCKS_PER_YEAR                                 (365*24*60*60/FIBERCHAIN_BLOCK_INTERVAL)
#define FIBERCHAIN_BLOCKS_PER_DAY                                  (24*60*60/FIBERCHAIN_BLOCK_INTERVAL)
#define FIBERCHAIN_START_MINER_VOTING_BLOCK                        (FIBERCHAIN_BLOCKS_PER_DAY * 30)

#define FIBERCHAIN_INIT_MINER_NAME                                 "oneofall"
#define FIBERCHAIN_NUM_INIT_MINERS                                 1
#define FIBERCHAIN_INIT_TIME                                       (fc::time_point_sec());

#define FIBERCHAIN_MAX_BOBSERVERS                                  31
#define FIBERCHAIN_NUM_BOBSERVERS                                  21    // FIBERCHAIN_MAX_VOTED_BOBSERVERS_HF0 + FIBERCHAIN_MAX_MINER_BOBSERVERS_HF0

#define FIBERCHAIN_MAX_VOTED_BOBSERVERS_HF0                        17
#define FIBERCHAIN_MAX_MINER_BOBSERVERS_HF0                        4
#define FIBERCHAIN_MAX_RUNNER_BOBSERVERS_HF0                       10
#define FIBERCHAIN_APPOINTMENT_BPRODUSER_CYCLE                     fc::days(30)

#define FIBERCHAIN_HARDFORK_REQUIRED_BOBSERVERS                    1
#define FIBERCHAIN_HARDFORK_REQUIRED_BOBSERVERS_HF2                1

#define FIBERCHAIN_MAX_TIME_UNTIL_EXPIRATION                       (60*60) // seconds,  aka: 1 hour
#define FIBERCHAIN_MAX_MEMO_SIZE                                   2048
#define FIBERCHAIN_MAX_QUERY_SIZE                                  1024 * 1024 // sqlite's max query size = 1MB
#define FIBERCHAIN_SAVINGS_WITHDRAW_REQUEST_LIMIT                  65535
#define FIBERCHAIN_DEPOSIT_COUNT_LIMIT                             65535
#define FIBERCHAIN_MIN_VOTE_INTERVAL_SEC                           3

#define FIBERCHAIN_MIN_ROOT_COMMENT_INTERVAL                       (fc::seconds(3)) // 3 seconds // (fc::seconds(60*5)) // 5 minutes
#define FIBERCHAIN_MIN_REPLY_INTERVAL                              (fc::seconds(3)) // 3 seconds // (fc::seconds(20)) // 20 seconds

#define FIBERCHAIN_MAX_ACCOUNT_BOBSERVER_VOTES                     30

#define FIBERCHAIN_100_PERCENT                                     10000
#define FIBERCHAIN_1_PERCENT                                       (FIBERCHAIN_100_PERCENT/100)
#define FIBERCHAIN_1_TENTH_PERCENT                                 (FIBERCHAIN_100_PERCENT/1000)

#define FIBERCHAIN_MAX_COMMENT_DEPTH                               0xffff // 64k
#define FIBERCHAIN_SOFT_MAX_COMMENT_DEPTH                          0xff // 255

#define FIBERCHAIN_MAX_RESERVE_RATIO                               (20000)

#define FIBERCHAIN_CREATE_ACCOUNT_WITH_FIBERCHAIN_MODIFIER          30
#define FIBERCHAIN_CREATE_ACCOUNT_DELEGATION_RATIO                 5

#define FIBERCHAIN_MIN_ACCOUNT_NAME_LENGTH                         3
#define FIBERCHAIN_MAX_ACCOUNT_NAME_LENGTH                         16

#define FIBERCHAIN_MIN_PERMLINK_LENGTH                             0
#define FIBERCHAIN_MAX_PERMLINK_LENGTH                             256
#define FIBERCHAIN_MAX_BOBSERVER_URL_LENGTH                        2048

#define FIBERCHAIN_INIT_SUPPLY                                     int64_t(1110000000000000000ll)

#define FIBERCHAIN_MAX_SUPPLY                                      int64_t(2220000000000000000ll)
#define FIBERCHAIN_TOKEN_MAX                                       int64_t(90000000000ll)

#define FIBERCHAIN_MAX_SHARE_SUPPLY                                int64_t(1000000000000000ll)  
#define FIBERCHAIN_MAX_SIG_CHECK_DEPTH                             2

#define FIBERCHAIN_MAX_TRANSACTION_SIZE                            (1024*64*200)
#define FIBERCHAIN_MIN_BLOCK_SIZE_LIMIT                            (FIBERCHAIN_MAX_TRANSACTION_SIZE)
#define FIBERCHAIN_MAX_BLOCK_SIZE                                  uint32_t( FIBERCHAIN_MAX_TRANSACTION_SIZE ) * uint32_t( FIBERCHAIN_BLOCK_INTERVAL * 2000 )
#define FIBERCHAIN_MIN_BLOCK_SIZE                                  115

#define FIBERCHAIN_BLOCKS_PER_HOUR                                 (5*60/FIBERCHAIN_BLOCK_INTERVAL) // 5 min
#define FIBERCHAIN_FEED_INTERVAL_BLOCKS                            (FIBERCHAIN_BLOCKS_PER_HOUR)
#define FIBERCHAIN_MAX_FEED_AGE_SECONDS                            (10*60) // 10 min
#define FIBERCHAIN_MIN_FEEDS                                       3 //(FIBERCHAIN_NUM_BOBSERVERS/3) /// protects the network from conversions before price has been established

#define FIBERCHAIN_MIN_UNDO_HISTORY                                10
#define FIBERCHAIN_MAX_UNDO_HISTORY                                10000

#define FIBERCHAIN_IRREVERSIBLE_THRESHOLD                          (75 * FIBERCHAIN_1_PERCENT)

#define FIBERCHAIN_TRANSFER_SAVINGS_MIN_MONTH                      1
#define FIBERCHAIN_TRANSFER_SAVINGS_MAX_MONTH                      24
#define FIBERCHAIN_TRANSFER_SAVINGS_CYCLE                          (fc::seconds(60))

#define FIBERCHAIN_EXCHANGE_MIN_BALANCE                            asset( 10000000, SNAC_SYMBOL )  // 10000.000 SNAC
#define FIBERCHAIN_EXCHANGE_FEE                                    asset( 1000000, SNAC_SYMBOL )  // 1000.000 SNAC
#define FIBERCHAIN_EXCHANGE_FEE_OWNER                              "snac"
#define FIBERCHAIN_EXCHANGE_REQUEST_EXPIRATION_PERIOD              fc::days(1)
#define FIBERCHAIN_GMT9                                            fc::hours(9)
#define FIBERCHAIN_3HOURS_STR                                      "T030000"

#define FIBERCHAIN_DAPP_TRANSACTION_FEE                            asset( 1000, SNAC_SYMBOL )  // 1 SNAC

#define FIBERCHAIN_MINER_ACCOUNT                                   "miners"
#define FIBERCHAIN_NULL_ACCOUNT                                    "null"
#define FIBERCHAIN_TEMP_ACCOUNT                                    "temp"
#define FIBERCHAIN_ROOT_POST_PARENT                                (account_name_type())

#define FIBERCHAIN_DEPOSIT_FUND_NAME                               ("deposit")
#define FIBERCHAIN_MAX_STAKING_MONTH                               12
#define FIBERCHAIN_MAX_USER_TYPE                                   2

// for staking interest rate
#define FIBERCHAIN_STAKING_INTEREST_PRECISION_DIGITS               3 
#define FIBERCHAIN_STAKING_INTEREST_PRECISION                      std::pow(10, FIBERCHAIN_STAKING_INTEREST_PRECISION_DIGITS )
