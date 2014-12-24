//
//  EnemyStateComponent.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 23/12/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "EnemyStateComponent.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        EnemyStateComponent::EnemyStateComponent()
        : livesCost(0)
        , lives(0)
        , score(0)
        {
        }
        
        unsigned int EnemyStateComponent::getLivesCost() const
        {
            return livesCost;
        }
        
        unsigned int EnemyStateComponent::getLives() const
        {
            return lives;
        }
        
        unsigned int EnemyStateComponent::getScore() const
        {
            return score;
        }
        
        void EnemyStateComponent::removeLives(unsigned int nLives)
        {
            if (nLives >= lives)
            {
                lives = 0;
            }
            else
            {
                lives = (lives - nLives);
            }
        }
    }
}