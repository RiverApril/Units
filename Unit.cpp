//
//  Unit.cpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#include "Unit.hpp"
#include "SDLHelper.hpp"


Unit::~Unit(){
    if(nav){
        nav->remove(this);
    }
}

void Unit::draw(SDL_Renderer* renderer){
    setRenderDrawColorRGB(renderer, 0x000000);
    RECT(rect, x-1-viewX, y-1-viewY, 3, 3);
    SDL_RenderFillRect(renderer, &rect);
}

void Unit::drawSelected(SDL_Renderer* renderer){
    setRenderDrawColorRGB(renderer, 0x8080FF);
    RECT(rect, x-2-viewX, y-2-viewY, 5, 5);
    SDL_RenderDrawRect(renderer, &rect);
}

void Unit::update(){
    if(nav && navID == 0){
        nav->update();
    }
    if(moveToTarget){
        a = atan2f(targetY-y, targetX-x);
        x += cos(a) * speed;
        y += sin(a) * speed;
    }
}

void Unit::assignNavigator(Navigator* newNav){
    if(nav){
        nav->remove(this);
    }
    nav = newNav;
    nav->add(this);
}

bool Unit::closeEnoughToTarget(){
    return fabs(x - targetX) > speed*2 || fabs(y - targetY) > speed*2;
}




