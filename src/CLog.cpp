/*
 * include/CLog.cpp
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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif
#endif

#ifndef _WIN32
#include <unistd.h>
#endif

#include "CLog.h"

static CString getBasePath();

CLog::CLog()
: enabled(false), file(nullptr)
{
#ifndef __AMIGA__
	m_write = new recursive_mutex();
#endif
	// Get base path.
	homepath = getBasePath();
}

CLog::CLog(const CString& _file, bool _enabled)
: enabled(_enabled), filename(_file), file(0)
{
#ifndef __AMIGA__
	m_write = new recursive_mutex();
#endif
	// Get base path.
	homepath = getBasePath();

	// Open the file now.
	if (enabled)
		file = fopen((homepath + filename).text(), "a");
	if (nullptr == file)
		enabled = false;
}

CLog::~CLog()
{
	{
#ifndef __AMIGA__
		std::lock_guard<recursive_mutex> lock(*m_preventChange);
#endif
		if (file)
		{
			fflush(file);
			fclose(file);
		}
	}
#ifndef __AMIGA__
	delete m_write;
#endif
}

void CLog::out(const CString format, ...)
{
	va_list s_format_v;

#ifndef __AMIGA__
	std::lock_guard<recursive_mutex> lock(*m_preventChange);
#endif
	// Assemble and print the timestamp.
	char timestr[60];
	time_t current_time = time(0);
	strftime(timestr, sizeof(timestr), "%I:%M %p", localtime(&current_time));
	printf("[%s] ", timestr);

	// Log output to file.
	if ( enabled && nullptr != file)
	{
		// Save the timestamp to the file.
		strftime(timestr, sizeof(timestr), "%a %b %d %X %Y", localtime(&current_time));
		fprintf(file, "[%s] ", timestr);

		// Write the message to the file.
		va_start(s_format_v, format);
		vfprintf(file, format.text(), s_format_v);
		va_end(s_format_v);
		fflush(file);
	}

	// Display message.
	va_start(s_format_v, format);
	vprintf(format.text(), s_format_v);
	va_end(s_format_v);
}

void CLog::append(const CString format, ...)
{
	va_list s_format_v;
	va_start(s_format_v, format);

#ifndef __AMIGA__
	std::lock_guard<recursive_mutex> lock(*m_preventChange);
#endif
	// Log output to file.
	if ( enabled && nullptr != file)
	{
		// Write the message to the file.
		vfprintf(file, format.text(), s_format_v);
		fflush(file);
		va_end(s_format_v);
		va_start(s_format_v, format);
	}

	// Display message.
	vprintf(format.text(), s_format_v);

	va_end(s_format_v);
}

void CLog::clear()
{
#ifndef __AMIGA__
	std::lock_guard<recursive_mutex> lock(*m_preventChange);
#endif
	if (file) fclose(file);

	file = fopen((homepath + filename).text(), "w");
	enabled = nullptr != file;
}

void CLog::close()
{
#ifndef __AMIGA__
	std::lock_guard<recursive_mutex> lock(*m_preventChange);
#endif
	if (file) fclose(file);
	file = nullptr;
	enabled = false;
}



void CLog::open()
{
#ifndef __AMIGA__
	std::lock_guard<recursive_mutex> lock(*m_preventChange);
#endif
	if (file) fclose(file);

	file = fopen((homepath + filename).text(), "a");
	enabled = nullptr != file;
}

void CLog::setFilename(const CString& filename)
{
#ifndef __AMIGA__
	std::lock_guard<recursive_mutex> lock(*m_preventChange);
#endif
	if (file) fclose(file);

	this->filename = filename;
	file = fopen((homepath + filename).text(), "a");
	enabled = nullptr != file;
}

CString getBasePath()
{
	CString homepath;

#if defined(_WIN32) || defined(_WIN64)
	// Get the path.
	char path[MAX_PATH];
	GetModuleFileNameA(0, path, MAX_PATH);

	// Find the program exe and remove it from the path.
	// Assign the path to homepath.
	homepath = path;
	int pos = homepath.findl('\\');
	if (pos == -1) homepath.clear();
	else if (pos != (homepath.length() - 1))
		homepath.removeI(++pos, homepath.length());
#else
	// Get the path to the program.
	char path[ 260 ];
	memset((void*)path, 0, 260);
#ifdef __AMIGA__
	snprintf(path, sizeof(path), "PROGDIR:");
#else
	readlink("/proc/self/exe", path, sizeof(path));
#endif

	// Assign the path to homepath.
	char* end = strrchr(path, '/');
	if (end != nullptr)
	{
		end++;
		if (end != nullptr) *end = '\0';
		homepath = path;
	}
#endif

	return homepath;
}
