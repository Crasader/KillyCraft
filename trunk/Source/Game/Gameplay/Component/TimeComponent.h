//
//  TimeComponent.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 31/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__TimeComponent__
#define __KillyCraft__TimeComponent__

#include "Component.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class TimeComponent : public Component
        {
        public:
            DECLARE_TYPE_WITH_BASE_TYPE(TimeComponent, Component);
            
            TimeComponent();
            
            virtual void update(float dt) override;
            
            float getTime() const;
            
        private:
            float time;
        };
    }
}

#endif /* defined(__KillyCraft__TimeComponent__) */
