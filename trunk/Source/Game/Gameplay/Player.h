//
//  Player.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 24/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__Player__
#define __KillyCraft__Player__

#include "Signal/Signal.h"

namespace MelonGames
{
	namespace KillyCraft
	{
		class Gamepad;
        class MapObject;
		
		class Player
		{
		public:
			Player();
			virtual ~Player();
			
			Gamepad* getGamepad() const;
            
            int getLives() const;
            Gallant::Signal1<Player*>& getLivesChangedSignal();
            
            int getScore() const;
            Gallant::Signal1<Player*>& getScoreChangedSignal();
            
            void addLives(int n);
            void removeLives(int n);
            
            void addScore(int nPoints);
            
            void setPlayerObject(MapObject* object);
            MapObject* getPlayerObject() const;
			
		private:
			Gamepad* gamepad;
            int lives;
            int score;
            Gallant::Signal1<Player*> livesChangedSignal;
            Gallant::Signal1<Player*> scoreChangedSignal;
            
            MapObject* playerObject;
		};
	}
}

#endif /* defined(__KillyCraft__Player__) */
