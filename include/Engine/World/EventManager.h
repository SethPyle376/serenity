#pragma once

#include <map>
#include <string>
#include <queue>

#include "Event.h"

class EventManager {
private:
    
public:
    static int count;
    static std::map<std::string, std::map<int, std::queue<Event>>> eventList;

    static void dispatch(Event event) {
        event.id = count++;
        eventList[event.componentType][event.targetId].push(event);
    }

    static std::queue<Event> getEvents(std::string type, int nodeId) {
        std::queue<Event> eventQueue = eventList[type][nodeId];
        eventList[type][nodeId] = std::queue<Event>();
        return eventQueue;
    }
};

int EventManager::count = 0;
std::map<std::string, std::map<int, std::queue<Event>>> EventManager::eventList = {};