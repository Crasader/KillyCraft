//
//  Random.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__Random__
#define __KillyCraft__Random__

#include <random>

namespace MelonGames
{
    class Random
    {
    public:
        static Random& getInstance();
        
        //0.0 .. 1.0
        float next();
        
    private:
        Random();
        
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<> dis;
    };
}

#endif /* defined(__KillyCraft__Random__) */