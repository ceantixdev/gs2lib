/*
 * include/CSettings.cpp
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
#include "CSettings.h"

/*
	Constructor - Deconstructor
*/
CSettings::CSettings()
{
	m_preventChange = new std::recursive_mutex();
}

CSettings::CSettings(const CString& pStr, const CString& pSeparator)
{
	m_preventChange = new std::recursive_mutex();

	strSep = pSeparator;
	opened = loadFile(pStr);
}

CSettings::~CSettings()
{
	clear();
	delete m_preventChange;
}

/*
	File-Loading Functions
*/
bool CSettings::isOpened() const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);
	return opened;
}

void CSettings::setSeparator(const CString& pSeparator)
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);
	strSep = pSeparator;
}

bool CSettings::saveFile()
{
	CString options = CString();
	options.clear();
	std::vector<CString> oldOptions = CString::loadToken(filename, "\n", true);

	for (auto & newOption : oldOptions)
	{
		if (newOption.find("#") != -1)
		{
			options << newOption << "\n";
			continue;
		}

		if (newOption.isEmpty() || newOption.find(strSep) == -1)
		{
			options << "\n";
			continue;
		}

		CString name = newOption.subString(0, newOption.find("="));
		name.trimI();

		CKey *option = this->getKey(name);
		newOption = CString() << name << " = " << option->value;

		option->saved = true;

		// Add this line back into options.
		options << newOption << "\n";
	}

	for (auto & key : keys)
	{
		if (!key->saved)
			options << key->name << " = " << key->value << "\n";

		key->saved = false;
	}

	options.replaceAllI("\n", "\r\n");
	return options.save(filename);
}

bool CSettings::loadFile(const CString& pStr)
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	filename = pStr;

	// definitions
	CString fileData;

	// Clear Keys
	clear();

	// Load File
	if (!fileData.load(pStr))
	{
		opened = false;
		return false;
	}

	// Parse Data
	fileData.removeAllI("\r");
	strList = fileData.tokenize("\n");
	for (auto & i : strList)
	{
		// Strip out comments.
		int comment_pos = i.find("#");
		if (comment_pos != -1)
			i.removeI(comment_pos);

		// Skip invalid or blank lines.
		if (i.isEmpty() || i.find(strSep) == -1)
			continue;

		// Tokenize Line && Trim && Lowercase Key Name
		std::vector<CString> line = i.tokenize(strSep);
		line[0].toLowerI();
		if (line.size() == 1) continue;

		// Fix problem involving settings with an = in the value.
		if (line.size() > 2)
		{
			for (unsigned int j = 2; j < line.size(); ++j)
				line[1] << "=" << line[j];
		}

		// Trim
		for (auto & j : line)
			j.trimI();

		// Create Key
		CKey *key;
		if ((key = getKey(line[0])) == nullptr)
			keys.push_back(new CKey(line[0], line[1]));
		else
			key->value << "," << line[1];
	}

	opened = true;
	return true;
}

void CSettings::clear()
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	// Clear Keys
	for (auto & key : keys)
		delete key;
	keys.clear();
}

bool CSettings::exists(const CString& pKey) const
{
	// Lowercase Name
	CString strName = pKey.toLower();

	// Iterate key List
	for (auto key : keys)
	{
		if (key->name == strName)
			return true;
	}

	return false;
}

CKey* CSettings::addKey(const CString& pKey, const CString& pValue)
{
	CKey* k = getKey(pKey);
	if (k)
	{
		k->value = pValue;
		return k;
	}

	k = new CKey(pKey, pValue);
	keys.push_back(k);
	return k;
}

/*
	Get Settings
*/
CKey * CSettings::getKey(const CString& pStr)
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	// Lowercase Name
	CString strName = pStr.toLower();

	// Iterate key List
	for (auto & key : keys)
	{
		if (key->name == strName)
			return key;
	}

	// None :(
	return 0;
}

const CKey* CSettings::getKey(const CString& pStr) const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	// Lowercase Name
	CString strName = pStr.toLower();

	// Iterate key List
	for (auto key : keys)
	{
		if (key->name == strName)
			return key;
	}

	// None :(
	return 0;
}

bool CSettings::getBool(const CString& pStr, bool pDefault) const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	const CKey *key = getKey(pStr);
	return (key == nullptr ? pDefault : (key->value == "true" || key->value == "1"));
}

float CSettings::getFloat(const CString& pStr, float pDefault) const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	const CKey *key = getKey(pStr);
	return (key == nullptr ? pDefault : (float)strtofloat(key->value));
}

int CSettings::getInt(const CString& pStr, int pDefault) const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	const CKey *key = getKey(pStr);
	return (key == nullptr ? pDefault : strtoint(key->value));
}

const CString CSettings::getStr(const CString& pStr, const CString& pDefault) const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	const CKey *key = getKey(pStr);
	return (key == nullptr ? pDefault : key->value);
}

const CString CSettings::operator[](int pIndex) const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);
	return strList[pIndex].trim();
}

std::vector<CString> CSettings::getFile() const
{
	std::lock_guard<std::recursive_mutex> lock(*m_preventChange);

	std::vector<CString> newStrList;
	std::copy(strList.begin(), strList.end(), newStrList.begin());
	return newStrList;
}
