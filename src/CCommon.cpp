/*
 * include/CCommon.cpp
 *
 * Copyright 2019 OpenGraal
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

#include "CCommon.h"
#include "IEnums.h"

const CString CCommon::triggerAction(char targetX, char targetY, CString action, CString weapon, CString args)
{
	return CString() >> char(PLO_TRIGGERACTION) >> short(0) >> int(0) >> char(targetX) >> char(targetY) << action.gtokenize() << "," << weapon.gtokenize() << "," << args;
}