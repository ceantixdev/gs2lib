/*
 * include/IUtil.h
 *
 * Copyright 2007-2019 OpenGraal
 *
 * This file is part of GS2Emu.
 *
 * GS2Emu is free software : you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GS2Emu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GS2Emu. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IUTIL_H
#define IUTIL_H

#include <map>
#include <vector>
#include <iterator>
#include "CString.h"

#define inrange(a, b, c) ((a) >= (b) && (a) <= (c))

/*
	Map-Functions
*/
template <class T, class U>
bool mapRemove(std::map<T, U>& a, T b)
{
	typename std::map<T, U>::iterator i;
	for (i = a.begin(); i != a.end();)
	{
		if (i->first == b)
		{
			a.erase(i++);
			return true;
		}
		else ++i;
	}
	return false;
}

template <class T, class U>
bool mapRemove(std::map<T, U>& a, U b)
{
	typename std::map<T, U>::iterator i;
	for (i = a.begin(); i != a.end();)
	{
		if (i->second == b)
		{
			a.erase(i++);
			return true;
		}
		else ++i;
	}
	return false;
}

/*
	Vector-Functions
*/
template <class T>
int vecSearch(std::vector<T>& a, T b)
{
	for (unsigned int i = 0; i < a.size(); ++i)
	{
		if (a[i] == b)
			return i;
	}
	return -1;
}

template <class T>
bool vecRemove(std::vector<T>& a, T b)
{
	bool found = false;
	typename std::vector<T>::iterator i;
	for (i = a.begin(); i != a.end();)
	{
		if (*i == b)
		{
			i = a.erase(i);
			found = true;
		}
		else ++i;
	}
	if (found) return true;
	return false;
}

template <class T>
int vecReplace(std::vector<T>& a, void *b, void *c)
{
	for (unsigned int i = 0; i < a.size(); i++)
	{
		if (a[i] == b)
		{
			a[i] = (T)c;
			return i;
		}
	}

	return -1;
}

/*
	Definitions
*/
enum // Return-Errors
{
	ERR_SUCCESS = 0,
	ERR_SETTINGS = -1,
	ERR_SOCKETS = -2,
	ERR_MYSQL = -3,
	ERR_LISTEN = -4,
};

enum
{
	COLOR_WHITE			= 0,
	COLOR_YELLOW		= 1,
	COLOR_ORANGE		= 2,
	COLOR_PINK			= 3,
	COLOR_RED			= 4,
	COLOR_DARKRED		= 5,
	COLOR_LIGHTGREEN	= 6,
	COLOR_GREEN			= 7,
	COLOR_DARKGREEN		= 8,
	COLOR_LIGHTBLUE		= 9,
	COLOR_BLUE			= 10,
	COLOR_DARKBLUE		= 11,
	COLOR_BROWN			= 12,
	COLOR_CYNOBER		= 13,
	COLOR_PURPLE		= 14,
	COLOR_DARKPURPLE	= 15,
	COLOR_LIGHTGRAY		= 16,
	COLOR_GRAY			= 17,
	COLOR_BLACK			= 18,
	COLOR_TRANSPARENT	= 19,
};

enum
{
	CLVER_UNKNOWN,
	CLVER_NPCSERVER,
	CLVER_1_25,
	CLVER_1_27,
	CLVER_1_28,
	CLVER_1_31,
	CLVER_1_32,
	CLVER_1_322,
	CLVER_1_323,
	CLVER_1_324,
	CLVER_1_33,
	CLVER_1_331,
	CLVER_1_34,
	CLVER_1_341,
	CLVER_1_35,
	CLVER_1_36,
	CLVER_1_37,
	CLVER_1_371,
	CLVER_1_38,
	CLVER_1_381,
	CLVER_1_39,
	CLVER_1_391,
	CLVER_1_392,
	CLVER_1_4,
	CLVER_1_41,
	CLVER_1_411,
	CLVER_2_1,
	CLVER_2_12,
	CLVER_2_13,
	CLVER_2_14,
	CLVER_2_15,
	CLVER_2_151,
	CLVER_2_16,
	CLVER_2_17,
	CLVER_2_18,
	CLVER_2_19,
	CLVER_2_2,
	CLVER_2_21,
	CLVER_2_22,
	CLVER_2_3,
	CLVER_2_31,

	CLVER_3,
	CLVER_3_01,
	CLVER_3_041,

	CLVER_4_0211,
	CLVER_4_034,
	CLVER_4_042,
	CLVER_4_110,
	CLVER_4_208,

	CLVER_5_07,
	CLVER_5_12,
	CLVER_5_31x,

	CLVER_6_015,
	CLVER_6_034,
	CLVER_6_037,
	CLVER_6_037_LINUX,

	CLVER_IPHONE_1_1,
	CLVER_IPHONE_1_5,
	CLVER_IPHONE_1_11,
	CLVER_IPHONE_BELOTE_1_5
};

enum
{
	NCVER_UNKNOWN,
	NCVER_1_1,
	NCVER_2_1,
};

enum
{
	RCVER_UNKNOWN,
	RCVER_1_010,
	RCVER_1_1,
	RCVER_2,
};

int getVersionID(const CString& version);
const char* getVersionString(const CString& version, const int type);
int getNCVersionID(const CString& version);
int getRCVersionID(const CString& version);
signed char getColor(const CString& color);
CString removeComments(const CString& code, const CString& newLine = "\n");
CString removeExtension(const CString& file);
int webSocketFixOutgoingPacket( CString& packetData );
int webSocketFixIncomingPacket( CString& packetData );

#endif
