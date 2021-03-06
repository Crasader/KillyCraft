//
//  MapObjectsFactory.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapObjectsFactory__
#define __KillyCraft__MapObjectsFactory__

#include <string>
#include <map>
#include "json/value.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        
        struct ObjectTemplate
        {
            std::string name;
            Json::Value json;
            
            bool abstract = false;
            
            Json::Value* getComponentJson(const std::string& componentType);
        };
        
        class MapObjectsFactory
        {
        public:
            MapObjectsFactory();
            
            void addTemplatesFromFile(const std::string& filename);
            
            MapObject* createObject(const std::string& name) const;
            
            std::vector<std::string> getObjectsNamesForFile(const std::string& filename) const;
            
        private:
            MapObject* createObject(const ObjectTemplate& t) const;
            void mergeTemplate(const ObjectTemplate& superTemplate, ObjectTemplate& baseTemplate) const;
            
        private:
            std::map<std::string, std::map<unsigned int, ObjectTemplate>> templatesByFile;
        };
    }
}

#endif /* defined(__KillyCraft__MapObjectsFactory__) */
