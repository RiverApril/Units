//
//  Entity.hpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "SDLHelper.hpp"

struct Entity{
    Entity(float x, float y) : x(x), y(y){}
    Entity(){}
    virtual ~Entity(){}
    
    float x = 0;
    float y = 0;
    
    virtual void draw(SDL_Renderer* renderer){}
    virtual void update(){}
};

#endif /* Entity_hpp */
