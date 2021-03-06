#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Actor {
  private:
    bool isActor;
    string name;
    unordered_map<string, Actor*> adjacents;

  public:
    Actor(string& name, bool isActor)
        : isActor(isActor), name(name), adjacents({}){};

    string getName() const;

    vector<Actor*> getAdjacents() const;

    Actor* getNext(string& nodeName);

    bool isMovie();

    void add(string& name, Actor* newNode);
};
#endif
