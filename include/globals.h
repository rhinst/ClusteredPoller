#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "types.h"

// See globals.cpp for documentation on what these are used for.

extern std::vector<QueryHost> hosts;
extern std::vector<ResultCache> cache;
extern std::list<std::string> queries;
extern unsigned query_queue_depth;
extern RTGConf config;
extern unsigned thread_id;
extern std::string rtgconf;
extern std::string targets;
extern int verbosity;
extern int detach;
extern int use_db;
extern int allow_db_zero;
extern unsigned max_queue_length;
extern pthread_mutex_t global_lock;
extern pthread_mutex_t db_list_lock;
extern pthread_mutex_t cerr_lock;
extern pthread_cond_t global_cond;
extern unsigned active_threads;
extern unsigned stat_inserts;
extern unsigned stat_queries;
extern unsigned stat_iterations;

#endif