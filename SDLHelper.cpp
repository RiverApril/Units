//
//  SDLHelper.cpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#include "SDLHelper.hpp"

int viewX = 0;
int viewY = 0;

void setRenderDrawColorRGB(SDL_Renderer* renderer, unsigned int rgb){
    SDL_SetRenderDrawColor(renderer, (rgb>>16)&0xFF, (rgb>>8)&0xFF, (rgb)&0xFF, 0xFF);
}

void setRenderDrawColorARGB(SDL_Renderer* renderer, unsigned int argb){
    SDL_SetRenderDrawColor(renderer, (argb>>16)&0xFF, (argb>>8)&0xFF, (argb)&0xFF, (argb>>24)&0xFF);
}
