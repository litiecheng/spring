/*
	Copyright (c) 2008 Robin Vobruba <hoijui.quaero@gmail.com>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CppTestAI.h"


#include "ExternalAI/Interface/AISEvents.h"
#include "ExternalAI/Interface/AISCommands.h"

// generated by the C++ Wrapper scripts
#include "OOAICallback.h"
#include "Unit.h"
#include "UnitDef.h"
#include "Game.h"

#include <string>

cpptestai::CCppTestAI::CCppTestAI(springai::OOAICallback* callback):
		callback(callback),
		skirmishAIId(callback != NULL ? callback->GetSkirmishAIId() : -1)
		{}

cpptestai::CCppTestAI::~CCppTestAI() {}

static inline std::string IntToString(int i, const std::string& format = "%i")
{
	char buf[64];
	SNPRINTF(buf, sizeof(buf), format.c_str(), i);
	return std::string(buf);
}
int cpptestai::CCppTestAI::HandleEvent(int topic, const void* data) {

	switch (topic) {
		case EVENT_UNIT_CREATED: {
			//struct SUnitCreatedEvent* evt = (struct SUnitCreatedEvent*) data;
			//int unitId = evt->unit;

			// TODO: wrapp events and commands too

			const std::vector<springai::Unit*> friendlyUnits = callback->GetFriendlyUnits();
			std::string msgText = std::string("Hello Engine (from CppTestA), num my units is ") + IntToString(friendlyUnits.size());
			if (friendlyUnits.size() > 0) {
				springai::Unit* unit = friendlyUnits[0];
				springai::UnitDef* unitDef = unit->GetDef();
				std::string unitDefName = unitDef->GetName();
				msgText = msgText + ", first friendly units def name is: " + unitDefName;
			}
			callback->GetGame()->SendTextMessage(msgText.c_str(), 0);

			break;
		}
		default: {
			break;
		}
	}

	// signal: everything went OK
	return 0;
}
