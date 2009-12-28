#include "types.h"
#include "query.h"
#include "util.h"
#include "version.h"
#include "globals.h"
#include "snmp.h"

using namespace std;

void help();

// Setup and initialization.

// Display usage.
void help() {
	cerr << "clpoll version " << CLPOLL_VERSION << endl;
	cerr << " -c <file>   Specify configuration file [" << rtgconf << "]" << endl;
	cerr << " -D          Don't detach, run in foreground" << endl;
	cerr << " -d          Disable database inserts" << endl;
	cerr << " -t <file>   Specify target file [" << targets << "]" << endl;
	cerr << " -v          Increase verbosity" << endl;
	cerr << " -z          Database zero delta inserts" << endl;
	cerr <<  " Copyright (c) 2009-2010 Jakob Borg" << endl;
}

// Parse command line, load caonfiguration and start threads.
int main (int argc, char * const argv[])
{
	if (argc < 2) {
		help();
		exit(0);
	}
	for (int i = 1; i < argc; i++) {
		string arg = string(argv[i]);
		if (arg == "-v")
			verbosity++;
		else if (arg == "-D")
			detach = 0;
		else if (arg == "-d")
			use_db = 0;
		else if (arg == "-z")
			allow_db_zero = 1;
		else if (arg == "-h") {
			help();
			exit(0);
		}
		else if (arg == "-c") {
			i++;
			rtgconf = string(argv[i]);
		}
		else if (arg == "-t") {
			i++;
			targets = string(argv[i]);
		}
	}

	if (detach)
		daemonize();

	global_snmp_init();

	// Read rtg.conf
	config = read_rtg_conf(rtgconf);
	// Read targets.cfg
	hosts = read_rtg_targets(targets, config);

	if (hosts.size() == 0) {
		cerr << "No hosts, so nothing to do." << endl;
		exit(-1);
	}

	// Allocate result cache for the number of hosts in targets.cfg
	cache = vector<ResultCache>(hosts.size());
	// Allocate the number of threads specified in rtg.conf
	pthread_t threads[config.threads];

	if (verbosity >= 1) {
		cerr << "Polling every " << config.interval << " seconds." << endl;
		cerr << "Starting poll with " << config.threads << " threads." << endl;
	}

	// Start the threads
	for (unsigned i = 0; i < config.threads; i++) {
		pthread_create(&threads[i], NULL, start_thread, NULL);
	}

	// Wait for them (forever, currently)
	for (unsigned i = 0; i < config.threads; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}

