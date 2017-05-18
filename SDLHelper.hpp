//
//  SDLHelper.hpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#include <SDL2/SDL.h>

#ifndef SDLHelper_hpp
#define SDLHelper_hpp

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define RECT(r, rx, ry, rw, rh) SDL_Rect r;r.x=rx;r.y=ry;r.w=rw;r.h=rh

extern int viewX;
extern int viewY;

void setRenderDrawColorRGB(SDL_Renderer* renderer, unsigned int rgb);

void setRenderDrawColorARGB(SDL_Renderer* renderer, unsigned int argb);

#endif /* SDLHelper_hpp */
