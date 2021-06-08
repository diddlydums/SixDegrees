#include "Actor.hpp"

#include <iostream>
#include <string>

using namespace std;

string Actor::getName() const { return name; }

vector<Actor*> Actor::getAdjacents() const {
    vector<Actor*> nodes;
    for (pair<string, Actor*> nod : adjacents) {
        nodes.push_back(nod.second);
    }
    return nodes;
}
Actor* Actor::getNext(string& name) {
    if (adjacents.find(name) != adjacents.end()) {
        return adjacents.at(name);
    }
    return nullptr;
}

bool Actor::isMovie() { return !isActor; }

void Actor::add(string& name, Actor* adjacent) {
    pair<string, Actor*> newNeighbor = {name, adjacent};
    adjacents.insert(newNeighbor);
}
