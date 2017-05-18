//
//  Navigator.cpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#include "Navigator.hpp"
#include "Unit.hpp"

#define PI 3.14159265358979

#define UNIT_SPACING 10

void Navigator::add(Unit* unit){
    units.push_back(unit);
    unit->navID = nextNavID;
    nextNavID++;
    needToPlanRoute = true;
}

void Navigator::remove(Unit* unit){
    int i=0;
    nextNavID = 0;
    for(Unit* u : units){
        if(u == unit){
            units.erase(units.begin() + i);
            unit->nav = nullptr;
        }else{
            unit->navID = nextNavID;
            nextNavID++;
        }
        i++;
    }
    needToPlanRoute = true;
    if(units.size() == 0){
        delete this;
    }
}

void Navigator::setRoute(vector<pair<float, float>> newRoute){
    route = newRoute;
    
    needToPlanRoute = true;
}

void Navigator::appendRoute(vector<pair<float, float>> afterRoute){
    route.insert(route.end(), afterRoute.begin(), afterRoute.end());
    
    needToPlanRoute = true;
}

void Navigator::planRoute(){
    if(route.size() > 0){
        
        orientX = map<int, float>();
        orientY = map<int, float>();
        
        targetX = route[0].first;
        targetY = route[0].second;
        
        averageX = 0;
        averageY = 0;
        
        slowest = units.size() > 0 ? units[0]->speed : 0;
        
        
        for(Unit* u : units){
            averageX += u->x;
            averageY += u->y;
        }
        averageX /= units.size();
        averageY /= units.size();
        targetAngle = atan2f(targetY-averageY, targetX-averageX);
        
        int count = (int)units.size();
        int edge;
        switch(formation){
            default:
            case FORMATION_RECT:{
                edge = (int)floor(sqrtf(count));
                break;
            }
        }
        
        for(Unit* u : units){
            float ox, oy;
            switch(formation){
                default:
                case FORMATION_RECT:{
                    int i = u->navID;
                    ox = (i % (edge))*UNIT_SPACING - (edge*UNIT_SPACING/2);
                    oy = (i / (edge))*UNIT_SPACING - (edge*UNIT_SPACING/2);
                    break;
                }
                case FORMATION_CIRCLE:{
                    if(u->navID == 0){
                        ox = 0;
                        oy = 0;
                    }else{
                        int q = 0;
                        int r = 0;
                        int c = 0;
                        while(q < u->navID){
                            r += UNIT_SPACING;
                            c = floor((2*PI*r) / UNIT_SPACING);
                            if(q+c >= count){
                                c = (int)count-1 - q;
                            }
                            q += c;
                        }
                        int i = q - u->navID;
                        float a = ((2*PI) / c) * i;
                        ox = cos(a)*r;
                        oy = sin(a)*r;
                    }
                    break;
                }
                    
            }
            float oa = atan2f(oy, ox);
            float od = sqrt(ox*ox+oy*oy);
            orientX[u->navID] = cos(oa+targetAngle)*od;
            orientY[u->navID] = sin(oa+targetAngle)*od;
            slowest = min(slowest, u->speed);
        }
        
    }
}

void Navigator::nextDestination(){
    if(route.size() == 1){
        patrol = false;
    }
    if(patrol){
        route.insert(route.end(), route.begin(), route.begin()+1);
    }
    route.erase(route.begin());
    planRoute();
}

void Navigator::update(){
    
    // Function only called by the unit with navID == 0
    
    if(needToPlanRoute){
        planRoute();
        needToPlanRoute = false;
    }
    
    if(route.size() > 0){
        
        if(regroupFirst){
            
            
            bool gettingIntoPosition = false;

            for(Unit* u : units){
                u->targetX = averageX + orientX[u->navID];
                u->targetY = averageY + orientY[u->navID];
                if(u->closeEnoughToTarget()){
                    u->moveToTarget = true;
                    gettingIntoPosition = true;
                }else{
                    u->x = u->targetX;
                    u->y = u->targetY;
                    u->moveToTarget = false;
                }
            }
            
            if(!gettingIntoPosition){
                averageX += cos(targetAngle) * slowest;
                averageY += sin(targetAngle) * slowest;
                
                if(fabs(targetX-averageX) < 1 && fabs(targetY-averageY) < 1){
                    nextDestination();
                }
            }
        }else{
            
            bool moving = false;
            
            for(Unit* u : units){
                u->targetX = targetX + orientX[u->navID];
                u->targetY = targetY + orientY[u->navID];
                if(fabs(u->x - u->targetX) > u->speed*2 || fabs(u->y - u->targetY) > u->speed*2){
                    u->moveToTarget = true;
                    moving = true;
                }else{
                    u->x = u->targetX;
                    u->y = u->targetY;
                    u->moveToTarget = false;
                }
            }
            if(!moving){
                nextDestination();
            }
        }
    }
    
    
}




