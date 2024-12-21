#include <time.h>
#include <assert.h>
#include "lprofile.h"

static int call_count[PROF_NUM];
static float execution_time[PROF_NUM];
static struct timespec ts_prof_start[PROF_NUM];
static struct timespec ts_prof_end[PROF_NUM];

static int profile_started[PROF_NUM];
static float get_execution_time(struct timespec* ts_start, struct timespec* ts_end);

LUAI_FUNC void init_profile()
{
  for(int index=0; index<PROF_NUM; index++)
  {
    call_count[index]        = 0;
    execution_time[index]    = 0.0f;
    ts_prof_start[index].tv_sec   = 0;
    ts_prof_start[index].tv_nsec  = 0.0f;
    ts_prof_end[index].tv_sec     = 0;
    ts_prof_end[index].tv_nsec    = 0.0f;

    profile_started[index]   = 0;
  }
}

void start_profile(ProfileIndex index)
{
  assert(profile_started[index] == 0);
  profile_started[index] = 1;
  
  timespec_get(&ts_prof_start[index], TIME_UTC);
}

void end_profile(ProfileIndex index)
{
  timespec_get(&ts_prof_end[index], TIME_UTC);

  assert(profile_started[index] == 1);
  profile_started[index] = 0;

  call_count[index]++;
  execution_time[index] += get_execution_time(&ts_prof_start[index], &ts_prof_end[index]);
}

int get_profile_call_count(ProfileIndex index)
{
  return call_count[index];
}


float get_profile_total_time(ProfileIndex index)
{
  return execution_time[index];
}

float get_profile_average_time(ProfileIndex index)
{
  if(call_count[index] != 0)
  {
    return get_profile_total_time(index) / (float)get_profile_call_count(index);
  }

  return 0.0f;
}

float get_execution_time(struct timespec* ts_start, struct timespec* ts_end)
{
  int sec   = ts_end->tv_sec  - ts_start->tv_sec;
  long nsec = ts_end->tv_nsec - ts_start->tv_nsec;
  if(nsec < 0)
  {
    nsec += 1000000000;
    sec--;
  }

  return (float)sec + ((float)nsec / (float)(1000 * 1000 * 1000));
}
