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

cmake_minimum_required(VERSION 2.8.5)

project(gs2lib CXX)

set(CMAKE_DEBUG_POSTFIX _d)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${BIN_DIR})

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
	string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/lib )
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/lib )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/${BIN_DIR} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

link_directories(${PROJECT_SOURCE_DIR}/lib)

# Adhere to GNU filesystem layout conventions
include(GNUInstallDirs)

# Lowercase project name for binaries and packaging
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

# Additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if(APPLE)
	# Set variables for generating the Info.plist file
	set(MACOSX_BUNDLE_BUNDLE_VERSION "${VER_FULL}")
	set(MACOSX_BUNDLE_EXECUTABLE ${PROJECT_NAME})
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.GraalReborn.GS2Lib")
	set(MACOSX_BUNDLE_NSMAIN_NIB_FILE "Application")
	set(MACOSX_BUNDLE_ICON_FILE "carton")
	set(MACOSX_BUNDLE_NAME ${PROJECT_NAME})
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VER_FULL}")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=gnu++17")
	cmake_policy(SET CMP0042 NEW)
elseif(WIN32)
	# Visual C++ Compiler options
	if(MSVC)
		# Suppress secure string function warnings
		add_definitions(-D_CRT_SECURE_NO_WARNINGS)

		include(CheckCXXCompilerFlag)
		CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
		if (_cpp_latest_flag_supported)
			add_compile_options("/std:c++latest")
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
		endif()

		# Enable parallel compilation
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

		# Enable static linkage of the Microsoft Visual C/C++ Runtime
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
		set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MTd")
		set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} /MT")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
		set(
			CMAKE_CXX_FLAGS_RELWITHDEBINFO
			"${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MTd"
		)
		set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
		cmake_policy(SET CMP0043 NEW)
	endif()

	if( MINGW )
		add_definitions(-D__STDC_FORMAT_MACROS)
		add_definitions(-D_BSD_SOURCE=1)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
	endif()

	# Prevent Windows.h from clashing with the Standard Template Library so we
	# can use std::min/std::max (see https://support.microsoft.com/kb/143208)
	add_definitions(-DNOMINMAX)

elseif(AROS)
elseif(AMIGA)

	add_definitions(-D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=1)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
else()
	if(NOT NOSTATIC)
	#	SET(CMAKE_EXE_LINKER_FLAGS "-static")
	endif()

	add_definitions(-D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=1)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

endif()

option(NOSTATIC "Don't compile as a static runtime." OFF)
if(NOSTATIC)
	message("Don't compile as a static runtime.")
	set(BUILD_SHARED_LIBS TRUE CACHE BOOL "-" FORCE)
else()
	message("Compile as static runtime.")
	add_definitions(-DSTATICLIB)
	set(BUILD_SHARED_LIBS FALSE CACHE BOOL "-" FORCE)
endif()

# Prefer static linkage
if(NOT NOSTATIC)
	set(SUFFIXES_ORIG ${CMAKE_FIND_LIBRARY_SUFFIXES})
	set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

find_package(ZLIB)
if(NOT ZLIB_FOUND)
	message("Zlib not found in system. Compiling it ourselves.")
	add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/zlib EXCLUDE_FROM_ALL)
	if(NOSTATIC)
		set_target_properties(zlibstatic minigzip example PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
	else()
		set_target_properties(zlib minigzip example PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
	endif()
endif()

find_package(BZip2)
if(NOT BZip2_FOUND)
	message("Bzip2 not found in system. Compiling it ourselves.")
	add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/bzip2)
endif()

# Restore library suffixes
if(NOT NOSTATIC)
	set(CMAKE_FIND_LIBRARY_SUFFIXES ${SUFFIXES_ORIG})
endif()

set(
	SOURCES
	src/CCommon.cpp
	src/CLog.cpp
	src/CSettings.cpp
	src/CString.cpp
	src/CTranslationManager.cpp
	src/IUtil.cpp
	src/md5.cpp
)

set(
	HEADERS
	include/CCommon.h

	include/CLog.h
	include/CSettings.h
	include/CString.h
	include/CTimeout.h
	include/CTranslationManager.h
	include/IDebug.h
	include/IEnums.h
	include/IUtil.h
	include/md5.h
)

if(NOT NONET)
	list(APPEND
			SOURCES
			src/CEncryption.cpp
			src/CFileQueue.cpp
			src/CSocket.cpp
	)

	list(APPEND
			HEADERS
			include/CEncryption.h
			include/CFileQueue.h
			include/CSocket.h
			)
endif()

include_directories(
	${PROJECT_SOURCE_DIR}/include
)

set(GS2LIB_INCLUDE_DIRECTORY
		"${PROJECT_SOURCE_DIR}/include"
		"${PROJECT_BINARY_DIR}/include"
		PARENT_SCOPE)

if(NOT ZLIB_FOUND)
	include_directories(${PROJECT_BINARY_DIR}/dependencies/zlib ${PROJECT_SOURCE_DIR}/dependencies/zlib)
else()
	include_directories(${ZLIB_INCLUDE_DIRS})
endif()

if(NOT BZip2_FOUND)
	include_directories(${PROJECT_SOURCE_DIR}/dependencies/bzip2/src)
endif()

# Set target names for the libraries
set(TARGET_NAME ${PROJECT_NAME})

add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})

option(NOWOLFSSL "Don't compile WolfSSL." OFF)
if(NOWOLFSSL)
	message("Don't compile WolfSSL.")
else()
	message("Compile as static runtime.")
	set(WOLFSSL_ARC4 yes)
	set(WOLFSSL_RSA yes)
	set(WOLFSSL_DES3 yes)

	set(WOLFSSL_CRYPT_TESTS no)
	set(WOLFSSL_EXAMPLES no)
	target_compile_definitions(${PROJECT_NAME} PUBLIC WOLFSSL_ENABLED)
	add_subdirectory("dependencies/wolfssl")
	add_dependencies(${PROJECT_NAME} wolfssl)
	target_link_libraries(${PROJECT_NAME} wolfssl)
endif()

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

# Packaging
if(APPLE)
	set(CPACK_GENERATOR DragNDrop)
	set(CPACK_DMG_VOLUME_NAME "${PROJECT_NAME} ${VER_FULL}")
	set(
			CPACK_DMG_DS_STORE_SETUP_SCRIPT
			${PROJECT_SOURCE_DIR}/resources/packaging/osx/DMGSetup.scpt
	)
	set(
			CPACK_DMG_BACKGROUND_IMAGE
			${PROJECT_SOURCE_DIR}/resources/packaging/osx/DMGBackground.tif
	)
elseif(WIN32)
	set(CPACK_GENERATOR "ZIP")
elseif(AMIGA)
	set(CPACK_GENERATOR LHA)
else()
	set(CPACK_GENERATOR TGZ)
endif()

set(CPACK_PACKAGE_NAME ${PROJECT_NAME_LOWER})
set(CPACK_PACKAGE_VENDOR "OpenGraal Team")
set(CPACK_PACKAGE_CONTACT "graal.in")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${VER_CPACK}")
set(CPACK_PACKAGE_VERSION_MAJOR ${VER_X})
set(CPACK_PACKAGE_VERSION_MINOR ${VER_Y})
set(CPACK_PACKAGE_VERSION_PATCH ${VER_Z}${VER_EXTRA})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GS2Lib")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${PROJECT_SOURCE_DIR}/README.md)
set(CPACK_RESOURCE_FILE_README ${PROJECT_SOURCE_DIR}/README.md)
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE.md)
set(CPACK_SOURCE_GENERATOR TGZ)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${VER_CPACK}-src")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/.bzr/;~$;${CPACK_SOURCE_IGNORE_FILES}")

if(NOT CPack_CMake_INCLUDED)
	include(CPack)
endif()

install(TARGETS ${TARGET_NAME} DESTINATION "lib/")

file(GLOB GS2LIB_INCLUDES
	"include/*.h"
)

install(TARGETS ${TARGET_NAME} DESTINATION "lib/")

install(FILES ${TARGET_NAME} DESTINATION "include/")


set(GS2LIB_LOADED ON PARENT_SCOPE)
