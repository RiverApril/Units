//
//  Navigator.hpp
//  Units
//
//  Created by Braeden Atlee on 12/23/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#ifndef Navigator_hpp
#define Navigator_hpp

#include <vector>
#include <map>

#define FORMATION_RECT 0
#define FORMATION_CIRCLE 1

using namespace std;

struct Unit;

struct Navigator{
    vector<Unit*> units;
    
    vector<pair<float, float>> route;
    
    int nextNavID = 0;
    
    float averageX, averageY;
    float targetX, targetY;
    float targetAngle;
    float slowest;
    
    int formation = FORMATION_RECT;
    bool regroupFirst = true;
    bool patrol = false;
    
    map<int, float> orientX;
    map<int, float> orientY;
    
    bool needToPlanRoute = false;
    
    void add(Unit* unit);
    void remove(Unit* unit);
    void update();
    void setRoute(vector<pair<float, float>> newRoute);
    void appendRoute(vector<pair<float, float>> afterRoute);
    void planRoute();
    void nextDestination();
};

#endif /* Navigator_hpp */
