/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: SystemOverrides.h
// Author: Valerii Myronov, Mar 2025

#pragma once

#ifndef _H_SystemOverrides
#define _H_SystemOverrides

#include "Common/MessageStream.h"

class SystemOverrides : public GameMessageTranslator
{
public:
	SystemOverrides();
	~SystemOverrides();

	GameMessageDisposition translateGameMessage(const GameMessage *msg);
	Real m_resScaleFactor;
private:
	Bool m_resScaleOn;
	Bool m_tacticalViewOn;

	Real m_tacticalViewZoom;
	Real m_tacticalViewPitch;
};

extern SystemOverrides *TheSystemOverrides;

#endif
