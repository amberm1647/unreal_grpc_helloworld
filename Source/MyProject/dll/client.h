#pragma once

#include <string>

#ifdef CLIENT_EXPORTS
#define CLIENT_API __declspec(dllexport)
#else
#define CLIENT_API __declspec(dllimport)
#endif


std::string CLIENT_API get_reply(const char* target_addr);
