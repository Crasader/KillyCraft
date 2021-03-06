//
//  MapTransitionController.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 17/02/15.
//  Copyright (c) 2015 MelonGames. All rights reserved.
//

#include "MapTransitionController.h"
#include "Map.h"
#include "MapTime.h"
#include "MapObject.h"
#include "MapObjectInspector.h"
#include "MapObjectsFactory.h"
#include "Component/BehaviourComponent.h"
#include "Component/MovementStateComponents.h"
#include "Component/PositionComponent.h"
#include "Component/ViewComponent.h"
#include "Behaviour/MovementBehaviours.h"
#include "View/MapView.h"
#include "View/StarsView.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        const static float kWaitingIn = 3.0f;
        const static float kParallaxMaxMultiplier = 5.0f;
        const static float kWaitingInY = 400.0f;
        
        MapTransitionController::MapTransitionController(Map* map)
        : map(map)
        , mapPlayer(nullptr)
        , mapTransitionPlayer(nullptr)
        , state(State::eNone)
        , stateTime(0.0f)
        {
            
        }
        
        void MapTransitionController::startTransition()
        {
            CCASSERT(state == State::eNone, "Calling MapTransitionController::startTransition() with a state different than eNone");
            state = State::eStart;
        }
        
        bool MapTransitionController::isTransitioning() const
        {
            return (state != State::eNone);
        }
        
        void MapTransitionController::update(float dt)
        {
            State oldState = state;
            float stateElapsedTime = (map->getTime()->getTotalTime() - stateTime);
            switch (state)
            {
                case State::eNone:
                default:
                    break;
                case State::eStart:
                {
                    mapPlayer = map->getObjectPassingFilter(MapObjectInspector::isPlayer);
                    CCASSERT(mapPlayer != nullptr, "There must be a player object at this point");
                    if (mapPlayer)
                    {
                        mapTransitionPlayer = map->getFactory()->createObject("PlayerTransition");
                        CCASSERT(mapTransitionPlayer != nullptr, "A PlayerTransition template must exist");
                        if (mapTransitionPlayer)
                        {
                            const float speedY = 500.0f;
                            float targetX = (map->getView()->getNode()->getContentSize().width * 0.5f);
                            
                            const cocos2d::Vec2& currPosition = mapPlayer->get<PositionComponent>()->getPosition();
                            map->addObject(mapTransitionPlayer);
                            mapTransitionPlayer->get<PositionComponent>()->setPosition(currPosition);
                            mapPlayer->get<ViewComponent>()->setVisible(false);
                            
                            float distToCenter = (targetX - currPosition.x);
                            float movingTime = std::abs((kWaitingInY - currPosition.y) / speedY);
                            float speedX = (distToCenter / movingTime);
                            
                            auto movementComponent = mapTransitionPlayer->getOrCreate<MoveLinearStateComponent>();
                            movementComponent->setMovementPerSecond(cocos2d::Vec2(speedX, speedY));
                            
                            mapPlayer->get<PositionComponent>()->setPosition(cocos2d::Vec2(targetX, currPosition.y));
                            state = State::eMovingIn;
                        }
                        else
                        {
                            state = State::eFinished;
                        }
                    }
                    else
                    {
                        state = State::eFinished;
                    }
                    break;
                }
                case State::eMovingIn:
                {
                    const float kStartHeight = mapPlayer->get<PositionComponent>()->getPosition().y;
                    
                    auto posComponent = mapTransitionPlayer->get<PositionComponent>();
                    float currentHeight = posComponent->getPosition().y;
                    
                    float parallaxSpeedMultiplier = (1.0f + ((currentHeight-kStartHeight) / (kWaitingInY - kStartHeight)) * kParallaxMaxMultiplier);
                    
                    if (currentHeight >= kWaitingInY)
                    {
                        auto movementComponent = mapTransitionPlayer->get<MoveLinearStateComponent>();
                        movementComponent->setMovementPerSecond(cocos2d::Vec2(0.0f, 0.0f));
                        parallaxSpeedMultiplier = kParallaxMaxMultiplier;
                        state = State::eWaitingIn;
                    }
                    
                    map->getView()->getStarsView()->setSpeedMultiplier(parallaxSpeedMultiplier);
                    
                    break;
                }
                case State::eWaitingIn:
                {
                    if (stateElapsedTime > kWaitingIn)
                    {
                        auto movementComponent = mapTransitionPlayer->get<MoveLinearStateComponent>();
                        movementComponent->setMovementPerSecond(cocos2d::Vec2(0.0f, -500.0f));
                        state = State::eMovingOut;
                    }
                    break;
                }
                case State::eMovingOut:
                {
                    const float kStartHeight = mapPlayer->get<PositionComponent>()->getPosition().y;
                    
                    auto posComponent = mapTransitionPlayer->get<PositionComponent>();
                    float currentHeight = posComponent->getPosition().y;
                    
                    float parallaxSpeedMultiplier = (1.0f + ((currentHeight-kStartHeight) / (kWaitingInY - kStartHeight)) * kParallaxMaxMultiplier);
                    
                    if (posComponent->getPosition().y <= mapPlayer->get<PositionComponent>()->getPosition().y)
                    {
                        auto movementComponent = mapTransitionPlayer->get<MoveLinearStateComponent>();
                        movementComponent->setMovementPerSecond(cocos2d::Vec2(0.0f, 0.0f));
                        parallaxSpeedMultiplier = 1.0f;
                        state = State::eWaitingOut;
                    }
                    
                    map->getView()->getStarsView()->setSpeedMultiplier(parallaxSpeedMultiplier);
                    
                    break;
                }
                case State::eWaitingOut:
                {
                    state = State::eFinished;
                    break;
                }
                case State::eFinished:
                {
                    mapPlayer->get<ViewComponent>()->setVisible(true);
                    mapPlayer->get<PositionComponent>()->setPosition(mapTransitionPlayer->get<PositionComponent>()->getPosition());
                    mapTransitionPlayer->get<ViewComponent>()->setVisible(false);
                    map->removeObjectWhenPossible(mapTransitionPlayer);
                    mapTransitionPlayer = nullptr;
                    state = State::eNone;
                    transitionFinishedSignal.Emit(this);
                    break;
                }
            }
            
            if (state != oldState)
            {
                stateTime = map->getTime()->getTotalTime();
            }
        }
        
        Gallant::Signal1<MapTransitionController*>& MapTransitionController::getTransitionFinishedSignal()
        {
            return transitionFinishedSignal;
        }
    }
}
