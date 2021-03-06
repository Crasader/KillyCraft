//
//  ViewParts.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 28/01/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ViewParts__
#define __KillyCraft__ViewParts__

#include "MelonGames/DeclaredTypes.h"
#include <string>
#include "math/Vec2.h"

namespace Json
{
    class Value;
}

namespace cocos2d
{
    class Node;
    class Sprite;
    struct Color3B;
    class Label;
    class ParticleSystemQuad;
}

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        class ViewPart;
        class WeaponComponent;
        
        namespace ViewPartsFactory
        {
            ViewPart* createViewPart(const Json::Value& json);
        }
        
        class ViewPart
        {
        public:
            DECLARE_BASE_TYPE(ViewPart);
            
            ViewPart();
            virtual ~ViewPart();
            
            virtual cocos2d::Node* getNode() = 0;
            
            void setPositionOffset(const cocos2d::Vec2& offset);
            const cocos2d::Vec2& getPositionOffset() const;
            
            virtual void onAttachedToObject(MapObject* object);
            virtual void onDetachedFromObject(MapObject* object);
            
        protected:
            cocos2d::Vec2 positionOffset;
        };
        
        
        class ViewPartSprite : public ViewPart
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ViewPartSprite, ViewPart);
            
            ViewPartSprite(const std::string& spriteFrameName);
            virtual ~ViewPartSprite();
            
            virtual cocos2d::Node* getNode() override;
            
            void setTintColor(const cocos2d::Color3B& color);
            
        private:
            cocos2d::Sprite* sprite;
        };
        
        class ViewPartParticleSystem : public ViewPart
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ViewPartParticleSystem, ViewPart);
            
            ViewPartParticleSystem(const std::string& fileName);
            ~ViewPartParticleSystem();
            
            virtual cocos2d::Node* getNode() override;
            
        private:
            cocos2d::ParticleSystemQuad* particleSystem;
        };
        
        class ViewPartWeapon : public ViewPart
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(ViewPartWeapon, ViewPart);
            
            ViewPartWeapon();
            virtual ~ViewPartWeapon();
            
            virtual cocos2d::Node* getNode() override;
            
            virtual void onAttachedToObject(MapObject* object) override;
            virtual void onDetachedFromObject(MapObject* object) override;
            
            void onWeaponComponentChanged(WeaponComponent* weaponComponent);
            
        private:
            cocos2d::Node* node;
        };
    }
}

#endif /* defined(__KillyCraft__ViewParts__) */
