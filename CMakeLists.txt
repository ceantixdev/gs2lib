#
#  CMakeLists.txt
#
#  Copyright 2019 死体
#
#  This file is part of GS2Emu.
#
#  GS2Emu is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  GS2Emu is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with GS2Emu.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.4.4)

project(gs2lib CXX)

set(VERSION "1.0")

set(
	SOURCES
	src/CCommon.cpp
	src/CEncryption.cpp
	src/CFileQueue.cpp
	src/CLog.cpp
	src/CSettings.cpp
	src/CSocket.cpp
	src/CString.cpp
	src/CTranslationManager.cpp
	src/IUtil.cpp
	src/md5.cpp
)

set(
	HEADERS
	include/CCommon.h
	include/CEncryption.h
	include/CFileQueue.h
	include/CLog.h
	include/CPlugin.h
	include/CSettings.h
	include/CSocket.h
	include/CString.h
	include/CTimeout.h
	include/CTranslationManager.h
	include/IDebug.h
	include/IEnums.h
	include/IUtil.h
	include/md5.h
)

include_directories(
	${PROJECT_SOURCE_DIR}/include
)

if(NOT NOUPNP AND NOT MINIUPNPC_FOUND)
	include_directories(${PROJECT_SOURCE_DIR}/../miniupnp ${PROJECT_SOURCE_DIR}/../miniupnp/miniupnpc)
endif()

if(NOT ZLIB_FOUND)
	include_directories(${PROJECT_BINARY_DIR}/../zlib ${PROJECT_SOURCE_DIR}/../zlib)
endif()

if(NOT BZip2_FOUND)
	include_directories(${PROJECT_SOURCE_DIR}/../bzip2)
endif()

# Set target names for the libraries
set(TARGET_NAME ${PROJECT_NAME})

add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})

if(NOT ZLIB_FOUND AND NOT NOSTATIC)
	add_dependencies(${TARGET_NAME} zlibstatic)
	target_link_libraries(${TARGET_NAME} zlibstatic)
elseif(NOT ZLIB_FOUND AND NOSTATIC)
	add_dependencies(${TARGET_NAME} zlib)
	target_link_libraries(${TARGET_NAME} zlib)
else()
	target_link_libraries(${TARGET_NAME} ${ZLIB_LIBRARIES})
endif()

if(NOT BZip2_FOUND)
	add_dependencies(${TARGET_NAME} bzip2)
	target_link_libraries(${TARGET_NAME} bzip2)
else()
	target_link_libraries(${TARGET_NAME} ${BZIP2_LIBRARIES})
endif()

target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})

if(WIN32)
	target_link_libraries(${TARGET_NAME} ws2_32 wsock32 iphlpapi)
endif()

if(NOT NOUPNP)
	if(NOT MINIUPNPC_FOUND)
		if(NOSTATIC)
			add_dependencies(${TARGET_NAME} libminiupnpc-shared)
			target_link_libraries(${TARGET_NAME} libminiupnpc-shared)
		else()
			add_dependencies(${TARGET_NAME} libminiupnpc-static)
			target_link_libraries(${TARGET_NAME} libminiupnpc-static)
		endif()
	else()
		target_link_libraries(${TARGET_NAME} ${MINIUPNP_LIBRARIES})
	endif()
endif()
