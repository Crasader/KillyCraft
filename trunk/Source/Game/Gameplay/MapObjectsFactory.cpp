//
//  MapObjectsFactory.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapObjectsFactory.h"
#include "MelonGames/Crypto.h"
#include "MapObject.h"
#include "Component/ComponentsFactory.h"

#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "json/json.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        MapObjectsFactory::MapObjectsFactory()
        {
        }
        
        void MapObjectsFactory::addTemplatesFromFile(const std::string& filename)
        {
            Json::Value json;
            std::string contents = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
            Json::Reader reader;
            reader.parse(contents, json);
            
            const Json::Value& objectsJson = json["obj"];
            
            for (const auto& objectJson : objectsJson)
            {
                std::string name = objectJson["name"].asString();
                unsigned int nameHash = Crypto::stringHash(name);
                ObjectTemplate t;
                t.name = name;
                t.json = objectJson;
                templates[nameHash] = t;
            }
        }
        
        MapObject* MapObjectsFactory::createObject(const std::string& name) const
        {
            unsigned int hash = Crypto::stringHash(name);
            auto it = templates.find(hash);
            if (it != templates.end())
            {
                return createObject(it->second);
            }
            
            return nullptr;
        }
        
        MapObject* MapObjectsFactory::createObject(const ObjectTemplate& t) const
        {
            MapObject* result = new MapObject();
            
            for (const auto& componentJson : t.json["components"])
            {
                Component* component = ComponentsFactory::createComponent(componentJson);
                
                if (component)
                {
                    result->addComponent(component);
                }
            }
            
            return result;
        }
    }
}