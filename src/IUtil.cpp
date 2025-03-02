/*
 * include/IUtil.cpp
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

#include "IDebug.h"
#include "IEnums.h"
#include "IUtil.h"

static const char* colors[] =
{
	"white",
	"yellow",
	"orange",
	"pink",
	"red",
	"darkred",
	"lightgreen",
	"green",
	"darkgreen",
	"lightblue",
	"blue",
	"darkblue",
	"brown",
	"cynober",
	"purple",
	"darkpurple",
	"lightgray",
	"gray",
	"black",
	"transparent",
	0
};

static const char* const clientVersions[] =
{
	"",				// CLVER_UNKNOWN,
	"",				// CLVER_NPCSERVER,
	"SERV009",		// CLVER_1_25,
	"SERV011",		// CLVER_1_27,
	"SERV013",		// CLVER_1_28,
	"SERV016",		// CLVER_1_31,
	"SERV018",		// CLVER_1_32,
	"",		// CLVER_1_322,
	"",		// CLVER_1_323,
	"",		// CLVER_1_324,
	"GNW20020",		// CLVER_1_33,
	"",		// CLVER_1_331,
	"GNW22030",		// CLVER_1_34,
	"",		// CLVER_1_341,
	"GNW13040",		// CLVER_1_35,
	"GNW10050",		// CLVER_1_36,
	"GNW21050",		// CLVER_1_37,
	"",		// CLVER_1_371,
	"GNW22060",		// CLVER_1_38,
	"",		// CLVER_1_381,
	"GNW07080",		// CLVER_1_39,
	"",		// CLVER_1_391,
	"",		// CLVER_1_392,
	"",		// CLVER_1_4,
	"",		// CLVER_1_41,
	"GNW13110",		// CLVER_1_411,
	"GNW31101",		// CLVER_2_1,
	"GNW01012",		// CLVER_2_12,
	"GNW23012",		// CLVER_2_13,
	"GNW30042",		// CLVER_2_14,
	"GNW19052",		// CLVER_2_15,
	"GNW20052",		// CLVER_2_151,
	"GNW12102",		// CLVER_2_16,
	"GNW22122",		// CLVER_2_17,
	"GNW21033",		// CLVER_2_18,
	"GNW15053",		// CLVER_2_19,
	"GNW28063",		// CLVER_2_2,
	"GNW01113",		// CLVER_2_21,
	"GNW03014",		// CLVER_2_22,
	"GNW14015",		// CLVER_2_3,
	"GNW28015",		// CLVER_2_31,

	"G3D16053",		// CLVER_3,
	"G3D27063",		// CLVER_3_01,
	"G3D03014",		// CLVER_3_041,

	"G3D28095",		// CLVER_4_0211,
	"G3D09125",		// CLVER_4_034,
	"G3D17026",		// CLVER_4_042,
	"G3D26076",		// CLVER_4_110,
	"G3D20126",		// CLVER_4_208,

	"G3D22067",		// CLVER_5_07,
	"G3D14097",		// CLVER_5_12,
	"G3D26090",		// CLVER_5_31x,

	"G3D3007A",		// CLVER_6_015,
	"G3D2505C",     // CLVER_6_034,
	"G3D0311C",		// CLVER_6_037,
	"G3D0511C",		// CLVER_6_037_LINUX,

	"G3D04048",		// CLVER_IPHONE_1_1
	"G3D18010",		// CLVER_IPHONE_1_5
	"G3D29090",		// CLVER_IPHONE_1_11
	"G3D2504D",		// CLVER_IPHONE_BELOTE_1_5

	"",				// NSVER_UNKNOWN,
	"GRNS0000",		// NSVER_GENERIC,
	"LNX00001",		// NSVER_LNXMAD,
	0
};

static const char* const ncVersions[] =
{
	"",				// NCVER_UNKNOWN,
	"NCL11012",		// NCVER_1_1,
	"NCL21075",		// NCVER_2_1,
	0
};

static const char* const rcVersions[] =
{
	"",				// RCVER_UNKNOWN,
	"GSERV023",		// RCVER_1_010,
	"GSERV024",		// RCVER_1_1,
	"GSERV025",		// RCVER_2,
	0
};

static const char* const clientVersionString[] =
{
	"",			// CLVER_UNKNOWN,
	"",			// CLVER_NPCSERVER,
	"1.25",		// CLVER_1_25,
	"1.27",		// CLVER_1_27,
	"1.28",		// CLVER_1_28,
	"1.31",		// CLVER_1_31,
	"1.32",		// CLVER_1_32,
	"",		// CLVER_1_322,
	"",		// CLVER_1_323,
	"",		// CLVER_1_324,
	"1.33",		// CLVER_1_33,
	"",		// CLVER_1_331,
	"1.34",		// CLVER_1_34,
	"",		// CLVER_1_341,
	"1.35",		// CLVER_1_35,
	"1.36",		// CLVER_1_36,
	"1.37",		// CLVER_1_37,
	"",		// CLVER_1_371,
	"1.38",		// CLVER_1_38,
	"",		// CLVER_1_381,
	"1.39",		// CLVER_1_39,
	"",		// CLVER_1_391,
	"",		// CLVER_1_392,
	"",		// CLVER_1_4,
	"",		// CLVER_1_41,
	"1.41r1",	// CLVER_1_411,
	"2.1",		// CLVER_2_1,
	"2.12",		// CLVER_2_12,
	"2.13",		// CLVER_2_13,
	"2.14",		// CLVER_2_14,
	"2.15",		// CLVER_2_15,
	"2.151",	// CLVER_2_151,
	"2.16",		// CLVER_2_16,
	"2.17",		// CLVER_2_17,
	"2.18",		// CLVER_2_18,
	"2.19",		// CLVER_2_19,
	"2.2",		// CLVER_2_2,
	"2.21",		// CLVER_2_21,
	"2.22",		// CLVER_2_22,
	"2.3",		// CLVER_2_3,
	"2.31",		// CLVER_2_31,

	"3.0",		// CLVER_3,
	"3.01",		// CLVER_3_01,
	"3.041",	// CLVER_3_041,

	"4.0211",	// CLVER_4_0211,
	"4.034",	// CLVER_4_034,
	"4.042",	// CLVER_4_042,
	"4.110",	// CLVER_4_110,
	"4.208",	// CLVER_4_208,

	"5.07",		// CLVER_5_07,
	"5.12",		// CLVER_5_12,
	"5.31x",	// CLVER_5_31x,

	"6.015",		// CLVER_6_015,
	"6.034/6.035",		// CLVER_6_034,
	"6.037",		// CLVER_6_037,
	"6.037 (Linux)",		// CLVER_6_037_LINUX,

	"iPhone 1.1",	// CLVER_IPHONE_1_1
	"iPhone 1.5",	// CLVER_IPHONE_1_5
	"iPhone 1.11",	// CLVER_IPHONE_1_11
	"iPhone Belote 1.5", //CLVER_IPHONE_BELOTE_1_5

	"[NPC-Server]",				// NSVER_UNKNOWN,
	"[NPC-Server] Generic",		// NSVER_GENERIC,
	"[NPC-Server] lnxmad",		// NSVER_LNXMAD,
	0
};

static const char* const ncVersionString[] =
{
	"",			// NCVER_UNKNOWN,
	"1.1",		// NCVER_1_1,
	"2.1",		// NCVER_2_1,
	0
};

static const char* const rcVersionString[] =
{
	"",			// RCVER_UNKNOWN,
	"1.010",	// RCVER_1_010,
	"1.1",		// RCVER_1_1,
	"2.0",		// RCVER_2,
	0
};

int getVersionID(const CString& version)
{
	int i = 0;
	while (clientVersions[i] != 0)
	{
		if (version == CString(clientVersions[i]))
			return i;
		++i;
	}
	return CLVER_UNKNOWN;
}

const char* getVersionString(const CString& version, const int type)
{
	int i = 0;
	while (clientVersions[i] != 0)
	{
		if ((type & PLTYPE_ANYCLIENT) != 0)
		{
			if (version == CString(clientVersions[i]))
				return clientVersionString[i];
		}
		else if ((type & PLTYPE_ANYRC) != 0)
		{
			if (version == CString(rcVersions[i]))
				return rcVersionString[i];
		}
		else if ((type & PLTYPE_ANYNC) != 0)
		{
			if (version == CString(ncVersions[i]))
				return ncVersionString[i];
		}
		else if ((type & PLTYPE_NPCSERVER) != 0)
		{
			if (version == CString(clientVersions[i]))
				return clientVersionString[i];
		}
		++i;
	}
	return 0;
}

int getNCVersionID(const CString& version)
{
	int i = 0;
	while (ncVersions[i] != 0)
	{
		if (version == CString(ncVersions[i]))
			return i;
		++i;
	}
	return NCVER_UNKNOWN;
}

int getRCVersionID(const CString& version)
{
	int i = 0;
	while (rcVersions[i] != 0)
	{
		if (version == CString(rcVersions[i]))
			return i;
		++i;
	}
	return RCVER_UNKNOWN;
}

signed char getColor(const CString& color)
{
	int i = 0;
	while (colors[i] != 0)
	{
		if (color.comparei(CString(colors[i])))
			return i;
		++i;
	}
	return -1;
}

CString removeComments(const CString& code, const CString& newLine)
{
	CString ret(code);
	int pos = -1;

	// Remove // comments.
	while ((pos = ret.find("//", pos + 1)) != -1)
	{
		//check for urls (http://)
		if (pos > 0 && ret[pos - 1] == ':')
			continue;

		// check for //#CLIENTSIDE
		if (ret.subString(pos, 13) == "//#CLIENTSIDE")
			continue;

		int len = ret.find(newLine, pos) - pos;
		if (len < 0) len = -1;
		ret.removeI(pos, len);
	}

	// Remove /* ... */ comments.
	while ((pos = ret.find("/*", pos + 1)) != -1)
	{
		int len = ret.find("*/", pos) - pos;
		if (len < 0) len = -1;
		ret.removeI(pos, len + 2);
	}

	return ret;
}

CString removeExtension(const CString& file)
{
	int ePos = file.findl('.');
	if (ePos == -1) return file;

	return file.subString(0, ePos);
}


int webSocketFixOutgoingPacket( CString& packetData ) {
	auto *message = new unsigned char[65535 * sizeof( char )];
	int i;
	int data_start_index;

	message[0] = 130;

	if( packetData.length() <= 125 ) {
		message[1] = ( unsigned char )packetData.length();
		data_start_index = 2;
	} else if( packetData.length() > 125 && packetData.length() <= 65535 ) {
		message[1] = 126;
		message[2] = ( unsigned char )( ( (int64_t)packetData.length() >> 8 ) & 255 );
		message[3] = ( unsigned char )( ( (int64_t)packetData.length() ) & 255 );
		data_start_index = 4;
	} else {
		message[1] = 127;
		message[2] = ( unsigned char )( ( (int64_t)packetData.length() >> 56 ) & 255 );
		message[3] = ( unsigned char )( ( (int64_t)packetData.length() >> 48 ) & 255 );
		message[4] = ( unsigned char )( ( (int64_t)packetData.length() >> 40 ) & 255 );
		message[5] = ( unsigned char )( ( (int64_t)packetData.length() >> 32 ) & 255 );
		message[6] = ( unsigned char )( ( (int64_t)packetData.length() >> 24 ) & 255 );
		message[7] = ( unsigned char )( ( (int64_t)packetData.length() >> 16 ) & 255 );
		message[8] = ( unsigned char )( ( (int64_t)packetData.length() >> 8 ) & 255 );
		message[9] = ( unsigned char )( ( (int64_t)packetData.length() ) & 255 );
		data_start_index = 10;
	}

	for( i = 0; i < packetData.length(); i++ ) {
		message[ data_start_index + i ] = ( unsigned char )packetData.text()[i];
	}

	int newPacketLength = packetData.length() + data_start_index;

	packetData.clear();
	packetData.write(message, newPacketLength);

	delete [] message;

	return i;
}

/**
 * @brief Frame FIN.
 */
	#define WS_FIN      128

/**
 * @brief Frame FIN shift
 */
	#define WS_FIN_SHIFT  7

/**
 * @brief Continuation frame.
 */
	#define WS_FR_OP_CONT 0

/**
 * @brief Text frame.
 */
	#define WS_FR_OP_TXT  1

/**
 * @brief Binary frame.
 */
	#define WS_FR_OP_BIN  2

/**
 * @brief Close frame.
 */
	#define WS_FR_OP_CLSE 8

/**
 * @brief Ping frame.
 */
	#define WS_FR_OP_PING 0x9

/**
 * @brief Pong frame.
 */
	#define WS_FR_OP_PONG 0xA

/**
 * @brief Unsupported frame.
 */
	#define WS_FR_OP_UNSUPPORTED 0xF

int webSocketFixIncomingPacket( CString& packetData ) {
	unsigned int i, j;
	unsigned char mask[4];
	unsigned int packet_length = 0;
	unsigned int length_code = 0;
	int index_first_mask = 0;
	int index_first_data_byte = 0;

	auto bytes = packetData.text();
	volatile auto code = bytes[0];
	volatile auto is_fin = (code & 0xFF) >> WS_FIN_SHIFT;
	volatile auto opcode = (code & 0x0F);

	if( opcode != WS_FR_OP_BIN ) {
		//dst = NULL;
		if( code == 136 ) {
			/* WebSocket client disconnected */
			return -2;
		}
		/* Unknown error */
		printf("packetData: %d\n", opcode);
		return -1;
	}


	length_code = bytes[1] & 127;

	if( length_code <= 125 ) {
		index_first_mask = 2;

		mask[0] = bytes[2];
		mask[1] = bytes[3];
		mask[2] = bytes[4];
		mask[3] = bytes[5];
	} else if( length_code == 126 ) {
		index_first_mask = 4;

		mask[0] = bytes[4];
		mask[1] = bytes[5];
		mask[2] = bytes[6];
		mask[3] = bytes[7];
	} else if( length_code == 127 ) {
		index_first_mask = 10;

		mask[0] = bytes[10];
		mask[1] = bytes[11];
		mask[2] = bytes[12];
		mask[3] = bytes[13];
	}

	index_first_data_byte = index_first_mask + 4;

	packet_length = packetData.length() - index_first_data_byte;

	auto * dst = new unsigned char[packet_length];

	for( i = index_first_data_byte, j = 0; i < packetData.length() && j < packet_length; i++, j++ ) {
		dst[ j ] = ( unsigned char )bytes[ i ] ^ mask[ j % 4];
	}

	packetData.clear();
	packetData.write(dst, packet_length);

	delete [] dst;

	return packet_length;
}
