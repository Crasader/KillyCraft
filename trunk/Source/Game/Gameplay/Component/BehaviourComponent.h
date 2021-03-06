//
//  BehaviourComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__BehaviourComponent__
#define __KillyCraft__BehaviourComponent__

#include "Component.h"
#include "Gameplay/Behaviour/Behaviour.h"
#include <vector>

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactory
        {
            Component* createBehaviourComponent(const Json::Value& json);
        }
        
        class BehaviourComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(BehaviourComponent, Component);
            
            friend Component* ComponentsFactory::createBehaviourComponent(const Json::Value& json);
            
            virtual void update(float dt) override;
            
            template <typename T> T* get() const;
            template <typename T> T* getOrCreate();
            void addBehaviour(Behaviour* b);
            
        private:
            std::vector<Behaviour*> behaviours;
        };
        
        
        template <typename T>
        T* BehaviourComponent::get() const
        {
            for (auto behaviour : behaviours)
            {
                if (behaviour->isA<T>())
                {
                    return (T*)behaviour;
                }
            }
            return nullptr;
        }
        
        template <typename T>
        T* BehaviourComponent::getOrCreate()
        {
            for (auto behaviour : behaviours)
            {
                if (behaviour->isA<T>())
                {
                    return (T*)behaviour;
                }
            }
            
            auto result = new T();
            addBehaviour(result);
            
            return result;
        }
    }
}

#endif /* defined(__KillyCraft__BehaviourComponent__) */
