//
//  StarsView.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__StarsView__
#define __KillyCraft__StarsView__

#include <vector>

namespace cocos2d
{
    class Node;
    class Sprite;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class StarsView
        {
        public:
            StarsView();
            virtual ~StarsView();
            
            
            void update(float dt);
            void addLayerWithTexture(cocos2d::Node* operatingNode, int zOrder, const std::string& textureName, float speedX, float speedY);
            
        private:
            struct Layer
            {
                cocos2d::Sprite* sprite = nullptr;
                float speedX = 0.0f;
                float speedY = 0.0f;
            };
            std::vector<Layer> layers;
        };
    }
}

#endif /* defined(__KillyCraft__StarsView__) */