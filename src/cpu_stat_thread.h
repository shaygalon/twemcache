#ifndef _cpu_stat_thread_h_
#define _cpu_stat_thread_h_

/* Quick cpu stats thread

	Author: Shay Gal-On
	
	Usage: 
	
	Allocate a cpu_info_t and create a cpu_stat_thread() thread with that structure as parameter. 
	Stop the thread with stop_cpu_stats().
	Set detail_cpu_stats_level to 1 to get cpu stats output at every cpu_stats_interval.
	Set interval to N to cpature cpu stats every N seconds.
	
	Example:
	
  cpu_info_t cpustat;
  pthread_create(&(cpustat.tid), 0, cpu_stat_thread, &cpustat);
	.. DO SOMETHING ..
  stop_cpu_stats();
  pthread_join(cpustat.tid,0);
  
*/


typedef struct cpu_info_s {
	volatile long double max,min,avg;
	pthread_t tid;
} cpu_info_t;

/* A thread to monitor cpu stats, returns a cpu_info_s containing info about the cpu load while running when stop_cpu_stats() is called.
   Will output a warning if cpu usage max went over 95% during monitored period.
 */
void *cpu_stat_thread(void *pdata);
/* Stop the cpu stat thread */
void stop_cpu_stats(void);
/* Set the detail level: 0=no output, only update the data object, 1 warn to stdout if avg usage >95%, 2 print usage at every interval */
void cpu_stats_detail(int level);
/* Set the interval (in seconds) to collect stats */
void cpu_stats_interval(int interval);
/* Reset the stats of a running thread */
void reset_cpu_stats(void);

#endif
