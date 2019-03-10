#pragma once

#include <map>
#include <string>
#include <vector>

#include "Event.h"

class EventManager {
private:
    
public:
    static int count;
    static std::map<std::string, std::vector<Event>> eventList;
    static void dispatch(Event event) {
        event.id = count++;
        eventList[event.type].push_back(event);
    }

    static std::vector<Event> getEvents(std::string type, int nodeId) {
        std::vector<Event> returnVector;
        for (int i = 0; i < eventList[type].size(); i++) {
            if (eventList[type][i].targetId == nodeId) {
                returnVector.push_back(eventList[type][i]);
                eventList[type].erase(eventList[type].begin() + i);
            }
        }
        return returnVector;
    }
};

int EventManager::count = 0;
std::map<std::string, std::vector<Event>> EventManager::eventList = {};