#pragma once

#include <stdint.h>
#define BURIED_EXPORT __declspec(dllexport)
extern "C" {
// one buried one instance and one work directory
typedef struct Buried Buried;
struct BuriedConfig {
  const char *host; // report server host(url)
  // const char *port;    // server port
  const char *topic;   // server topic url:port/topic
  const char *user_id; // user id, eg: the user whoes app happened error
  // const char *app_version;
  const char *version;
  // const char *app_name;
  const char *custom_data; // custom data, json format
};

// User Interfaces
BURIED_EXPORT Buried *Buried_Create(const char *work_dir);
BURIED_EXPORT void Buried_Destroy(Buried *buried);
BURIED_EXPORT int32_t Buried_Start(Buried *buried, BuriedConfig *config);
BURIED_EXPORT int32_t Buried_Report(Buried *buried, const char *report_data,
                                    uint32_t priority);
}
