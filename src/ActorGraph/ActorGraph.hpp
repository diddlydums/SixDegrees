#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Actor.hpp"
using namespace std;

class ActorGraph {
  protected:
    // add data structures used in actor graph
    unordered_map<string, Actor*> n;

  public:
   
    void clearhelper();
    ActorGraph();

    unordered_map<string, Actor*> getNodes();

  
    bool buildGraph(istream& is);


    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    int getSize();
    string format(string unformat);

    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
