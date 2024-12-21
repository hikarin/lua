/*
** Profiler
*/

#ifndef lprofiler_h
#define lprofiler_h

#include "lua.h"

typedef enum
{
  PROF_FULLGC,
  PROF_BARRIER,

  PROF_NUM
  
}ProfileIndex;

LUAI_FUNC void init_profile(void);
LUAI_FUNC void start_profile(ProfileIndex index);
LUAI_FUNC void end_profile(ProfileIndex index);
LUAI_FUNC int get_profile_call_count(ProfileIndex index);
LUAI_FUNC float get_profile_average_time(ProfileIndex index);
LUAI_FUNC float get_profile_total_time(ProfileIndex index);

#endif
