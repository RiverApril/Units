//
//  Unit.hpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#ifndef Unit_hpp
#define Unit_hpp

#include "Entity.hpp"
#include "Navigator.hpp"

struct Unit : public Entity{
    Unit(float x, float y) : Entity(x, y){}
    Unit() : Entity(){}
    virtual ~Unit();
    
    float a = 0;
    float targetX = 0;
    float targetY = 0;
    bool moveToTarget = false;
    float speed = .5f;
    
    Navigator* nav = nullptr;
    int navID = -1;
    
    virtual void draw(SDL_Renderer* renderer);
    virtual void drawSelected(SDL_Renderer* renderer);
    virtual void update();
    void assignNavigator(Navigator* newNav);
    bool closeEnoughToTarget();
};

#endif /* Unit_hpp */
