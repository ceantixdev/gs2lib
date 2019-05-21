/*
 * include/CTranslationManager.h
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

#ifndef CTRANSLATIONMANAGER_H
#define CTRANSLATIONMANAGER_H

#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::string> STRMAP;

// -- Class: CTranslationManager -- //
class CTranslationManager
{
	public:
		// -- Functions -> Get -- //
		inline std::map<std::string, STRMAP> * getTranslationList()
		{
			return &mTranslationList;
		}

		// -- Functions -> Translation Management -- //
		const char * translate(const std::string& pLanguage, const std::string& pKey);
		void add(const std::string& pLanguage, const std::string& pKey, const std::string& pTranslation);
		void remove(const std::string& pLanguage, const std::string& pKey);

		// -- Functions -> Language Management -- //
		void reset();
		void reset(const std::string& pLanguage);

	protected:
		std::map<std::string, STRMAP> mTranslationList;
};

#endif
