#pragma once

#ifdef MINIGIN_EXPORT
// dll library uses this
#define MINIGIN_ENTRY __declspec(dllexport)
#else
#ifdef MINIGIN_IMPORT
// dll user uses this
#define MINIGIN_ENTRY __declspec(dllimport)
#else
// static linked uses this
#define MINIGIN_ENTRY
#endif
#endif