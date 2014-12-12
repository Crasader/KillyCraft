//
//  SpawnObjectsManager.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__SpawnObjectsManager__
#define __KillyCraft__SpawnObjectsManager__

#include "json/value.h"
#include <string>
#include <vector>

namespace cocos2d
{
    class Vec2;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class Map;
        class MapObject;
        
        class SpawnObjectsManager
        {
        public:
            SpawnObjectsManager();
            
            void loadEnemySquadsFromFile(const std::string& filename);
            
            void setMap(Map* map);
            
            void update(float dt);
            
        private:
            
            class SpawnManager
            {
            public:
                SpawnManager(float minTime, float varTime) : minTime(minTime), varTime(varTime), map(nullptr), timeout(0.0f) {};
                
                virtual void update(float dt);
                virtual void spawnNextItem() = 0;
                
                void setMap(Map* map) { this->map = map; }
                
            private:
                SpawnManager();
                
            protected:
                const float minTime;
                const float varTime;
                Map* map;
                float timeout;
            };
            
            class SpawnSquadsManager : public SpawnManager
            {
            public:
                SpawnSquadsManager(float minTime, float varTime) : SpawnManager(minTime, varTime) {};
                struct SquadTemplate
                {
                    std::string name;
                    Json::Value json;
                };
                
                void loadEnemySquadsFromFile(const std::string& filename);
                void spawnNextItem() override;
                void createSquad(const SquadTemplate& squadTemplate, const cocos2d::Vec2& offset, std::vector<MapObject*>& enemies);
                const SquadTemplate* getSquadTemplateWithName(const std::string& name) const;
                
            private:
                std::vector<SquadTemplate> squadTemplates;
            };
            SpawnSquadsManager spawnSquadsManager;
            
            class SpawnPowerUpsManager : public SpawnManager
            {
            public:
                SpawnPowerUpsManager(float minTime, float varTime) : SpawnManager(minTime, varTime) {};
                void spawnNextItem() override;
                
            };
            SpawnPowerUpsManager spawnPowerUpsManager;
            
            std::vector<SpawnManager*> allManagers;
        };
    }
}

#endif /* defined(__KillyCraft__SpawnObjectsManager__) */
