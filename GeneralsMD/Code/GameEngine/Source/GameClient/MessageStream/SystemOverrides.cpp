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

// SystemOverrides.cpp
// Allows to changing global application data on keypresses
// Author: Valerii Myronov, Mar 2025

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/KeyDefs.h"
#include "GameClient/SystemOverrides.h"

#include "Common/GlobalData.h"

SystemOverrides *TheSystemOverrides = NULL;

//-----------------------------------------------------------------------------
SystemOverrides::SystemOverrides() :
	m_resScaleFactor(1.0)
{
	DEBUG_ASSERTCRASH(!TheSystemOverridesTranslator, ("Already have a SystemOverridesTranslator - why do you need two?"));
	TheSystemOverrides = this;
}

//-----------------------------------------------------------------------------
SystemOverrides::~SystemOverrides()
{
	if (TheSystemOverrides == this)
		TheSystemOverrides = NULL;
}

//-----------------------------------------------------------------------------
/**
 * The System Overrides Translator is responsible for reacting for toggling some
 * experimental features based on keypresses
 */
GameMessageDisposition SystemOverrides::translateGameMessage(const GameMessage *msg)
{
	const GameMessage::Type t = msg->getType();
	switch (t) {
		//-----------------------------------------------------------------------------
		case GameMessage::MSG_RAW_KEY_DOWN:
		case GameMessage::MSG_RAW_KEY_UP:
		{
			const UnsignedByte key = msg->getArgument( 0 )->integer;
			const UnsignedByte state = msg->getArgument( 1 )->integer;
			const Bool isPressed = !(BitTest( state, KEY_STATE_UP ));

			switch (key)
			{
				case KEY_F12:
					if (isPressed) {
						m_resScaleEnabled = !m_resScaleEnabled;
						if (m_resScaleEnabled) {
							const int xRes = TheGlobalData->m_xResolution;
							const int yRes = TheGlobalData->m_yResolution;
							m_resScaleFactor = static_cast<float>(min(xRes / 1024.0, yRes / 768.0));
						} else {
							m_resScaleFactor = 1.0;
						}
					}
					return DESTROY_MESSAGE;
				default:
					break;
			}
		}
		default:
			break;
	}
	return KEEP_MESSAGE;
} // end SystemOverridesTranslator
