#pragma once

#ifndef RIIERU_HREAD
#define RIIERU_HREAD





#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <ws2tcpip.h>
#include<WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include<iostream>
#include<map>
#include <regex>
#include <ranges>
#include <algorithm>

#include <openssl/ssl.h>
#include <openssl/err.h>


#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")


#include <icu.h>


#pragma comment(lib, "icu.lib")

#include"retrieve.h"
#include"icuproject.h"
#include"fileoperation.h"
#include"instance_class.hpp"
#include"StringEX.h"
#include"Riierufiletail.h"
#include"openssl.h"
#include"socket.h"
#include"network.h"
#include"crawlertool.h"




#endif // !RIIERU_HREAD