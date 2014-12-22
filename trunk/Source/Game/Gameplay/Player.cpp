//
//  Player.cpp
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 24/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "Player.h"
#include "Gameplay/Gamepad.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		Player::Player()
		{
            gamepad = new Gamepad();
		}
		
		Player::~Player()
		{
			delete gamepad;
		}
		
		Gamepad* Player::getGamepad() const
		{
			return gamepad;
		}
	}
}