//
//  MapView.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapView__
#define __KillyCraft__MapView__

#include "2d/CCNode.h"
#include "Game/GameConfig.h"
#include "Gameplay/View/MapGridView.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class StarsView;
        class GameHUDView;
        
        class MapView
        {
        public:
            MapView(const Map* map, cocos2d::Node* mainNode);
            virtual ~MapView();
            
            cocos2d::Node* getNode() const;
            StarsView* getStarsView() const;
            
            void update(float dt);
            
        private:
            const Map* map;
            cocos2d::Node* mainView;
            StarsView* starsView;
            GameHUDView* hudView;
            
#ifdef DRAW_MAP_GRID
            MapGridView* gridView;
#endif
        };
    }
}

#endif /* defined(__KillyCraft__MapView__) */
