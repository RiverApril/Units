//
//  main.cpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#include <vector>

#include "Unit.hpp"
#include "SDLHelper.hpp"

using namespace std;

#define SCROLL_SPEED 1

vector<Entity*> entityList;

vector<Unit*> selected;

vector<pair<float, float>> route;

int dragX1 = 0;
int dragY1 = 0;
int dragX2 = 0;
int dragY2 = 0;
bool dragging = false;

int main(int argc, const char * argv[]) {
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Unable to initialize SDL:  %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
    
    if(!window){
        fprintf(stderr, "Unable to create window and renderer:  %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Event event;
    
    bool running = true;
    
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    
    while (running) {
        SDL_PollEvent(&event);
        
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        mx += viewX;
        my += viewY;
        
        switch(event.type){
                
            case SDL_QUIT: {
                running = false;
                break;
            }
            case SDL_KEYDOWN:{
                switch(event.key.keysym.scancode){
                    case SDL_SCANCODE_SPACE:{
                        entityList.push_back(new Unit(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT));
                        break;
                    }
                    case SDL_SCANCODE_1:{
                        for(Unit* u : selected){
                            if(u->nav){
                                u->nav->formation = FORMATION_RECT;
                            }
                        }
                        break;
                    }
                    case SDL_SCANCODE_2:{
                        for(Unit* u : selected){
                            if(u->nav){
                                u->nav->formation = FORMATION_CIRCLE;
                            }
                        }
                        break;
                    }
                    default: break;
                }
                break;
            }
            case SDL_KEYUP:{
                switch(event.key.keysym.scancode){
                    default: break;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                
                if(event.button.button == 1){
                    dragging = true;
                    dragX1 = mx;
                    dragY1 = my;
                }
                if(event.button.button == 3){
                    
                    route.push_back({mx, my});
                    
                    if(!keys[SDL_SCANCODE_LSHIFT]){
                        Navigator* nav = new Navigator();
                        nav->setRoute(route);
                        nav->patrol = true;
                        route.clear();
                        
                        for(Unit* u : selected){
                            u->assignNavigator(nav);
                        }
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                if(event.button.button == 1){
                    dragging = false;
                    dragX2 = mx;
                    dragY2 = my;
                    if(!keys[SDL_SCANCODE_LSHIFT]){
                        selected.clear();
                    }
                    for(Entity* e : entityList){
                        Unit* u = dynamic_cast<Unit*>(e);
                        if(u){
                            if(u->x >= min(dragX1, dragX2) &&
                               u->y >= min(dragY1, dragY2) &&
                               u->x <= max(dragX1, dragX2) &&
                               u->y <= max(dragY1, dragY2)){
                                if(!keys[SDL_SCANCODE_LSHIFT] || find(selected.begin(), selected.end(), u) == selected.end()){
                                    selected.push_back(u);
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
        
        setRenderDrawColorRGB(renderer, 0xFFFFFF);
        SDL_RenderClear(renderer);
        
        
        if(dragging){
            dragX2 = mx;
            dragY2 = my;
            SDL_Rect rect;
            rect.x = min(dragX1, dragX2) - viewX;
            rect.y = min(dragY1, dragY2) - viewY;
            rect.w = abs(dragX1 - dragX2);
            rect.h = abs(dragY1 - dragY2);
            setRenderDrawColorRGB(renderer, 0x0000FF);
            SDL_RenderDrawRect(renderer, &rect);
        }
        
        for(Entity* e : entityList){
            e->draw(renderer);
            e->update();
        }
        
        for(Unit* u : selected){
            u->drawSelected(renderer);
        }
        
        SDL_RenderPresent(renderer);
    }
    
    return 0;
}
