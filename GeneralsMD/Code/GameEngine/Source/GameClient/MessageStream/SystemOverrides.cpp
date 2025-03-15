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
// Allows to change global application data on keypresses
// Author: Valerii Myronov, Mar 2025

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/KeyDefs.h"
#include "GameClient/InGameUI.h"
#include "GameClient/SystemOverrides.h"

#include "Common/UnicodeString.h"
#include "Common/GlobalData.h"

SystemOverrides *TheSystemOverrides = NULL;

//-----------------------------------------------------------------------------
SystemOverrides::SystemOverrides() :
	m_resScaleFactor(1.0),
	m_tacticalViewPitch(-PI / 5),
	m_tacticalViewZoom(2.5)
{
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
			const Bool isPressed = !(BitIsSet( state, KEY_STATE_UP ));

			switch (key)
			{
				case KEY_F1:
					if (isPressed) {
						m_resScaleOn = !m_resScaleOn;
						if (m_resScaleOn) {
							const int xRes = TheGlobalData->m_xResolution;
							const int yRes = TheGlobalData->m_yResolution;
							m_resScaleFactor = static_cast<float>(min(xRes / 800.0, yRes / 600.0));
							TheInGameUI->message(UnicodeString(L"Resolution based icon scale enabled: %.2f"), m_resScaleFactor);
						} else {
							m_resScaleFactor = 1.0;
							TheInGameUI->message(UnicodeString(L"Resolution based icon scale disabled"));
						}
					}
					return DESTROY_MESSAGE;
				case KEY_F2:
					if (isPressed) {
						if (m_tacticalViewOn)
						{
							TheTacticalView->setDefaultView(0, 0, 1.0);
							TheTacticalView->setHeightAboveGround(TheGlobalData->m_maxCameraHeight);
							TheTacticalView->setPitch(0);
							TheInGameUI->message(UnicodeString(L"Switched to default wiew"));
						}
						else
						{
							static const Real heightMulti = 3;
							TheTacticalView->setDefaultView(-PI / 5, 0, heightMulti);
							TheTacticalView->setHeightAboveGround(TheGlobalData->m_maxCameraHeight * heightMulti);
							TheTacticalView->setPitch(-PI / 5);
							TheInGameUI->message(UnicodeString(L"Switched to tactical wiew"));
						}
						m_tacticalViewOn = !m_tacticalViewOn;
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
