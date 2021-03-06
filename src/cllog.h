/*
 *  ClusteredPoller
 *
 *  Created by Jakob Borg.
 *  Copyright 2011 Nym Networks. See LICENSE for terms.
 */

#ifndef _UTIL_H
#define _UTIL_H

/** @file cllog.h Clpoll logging implementation. */

/**
 * The maximum length of a log line.
 * Lines will be truncated to this length.
 */
#define MAX_LINE_LENGTH 128

/**
 * Log a message with the specified level.
 * Accepts format string and arguments á la printf.
 * Will log to syslog and console, depending on verbosity level.
 * @param level Log level; 0 being critical, 1 information, 2 and higher are increasing levels of debug.
 * @param format A printf-style format string.
 */
__attribute__ ((format(printf, 2, 3)))
void cllog(int level, const char *format, ...);

#endif
