#include "ActorGraph.hpp"

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

void ActorGraph::clearhelper() {
    for (pair<string, Actor*> nod : n) {
        delete nod.second;
    }
    n.clear();
}

ActorGraph::ActorGraph() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraph(istream& is) {
    bool readHeader = false;

    while (is) {
        string s;
        if (!getline(is, s)) break;

        if (!readHeader) {
            readHeader = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            continue;
        }

        string actor(record[0]);
        string title = record[1] + "#@" + record[2];
        // string title(record[1]);
        // string year(record[2]);

        Actor* myActor = nullptr;
        if (n.find(actor) == n.end()) {
            myActor = new Actor(actor, true);
            n.insert({actor, myActor});
        } else {
            myActor = n.at(actor);
        }

        Actor* myMovie = nullptr;
        if (n.find(title) == n.end()) {
            myMovie = new Actor(title, false);
            n.insert({title, myMovie});
        } else {
            myMovie = n.at(title);
        }

        myMovie->add(actor, myActor);
        myActor->add(title, myMovie);
    }

    if (!is.eof()) {
        clearhelper();
        return false;
    }

    return true;
}

void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    queue<pair<string, Actor*>> q;
    Actor* first = NULL;
    Actor* last = NULL;
    unordered_map<Actor*, string> path;
    pair<string, Actor*> curr;

    if (n.find(fromActor) == n.end()) {
        return;
    } else {
        first = n.at(fromActor);
    }

    if (n.find(toActor) == n.end()) {
        return;
    } else {
        last = n.at(toActor);
    }

    for (auto i : n) {
        path.insert({i.second, ""});
    }

    q.push({"", first});

    while (!q.empty()) {
        curr = q.front();
        q.pop();

        if (curr.second == last) {
            string unformat = curr.first + "`" + curr.second->getName();
            shortestPath = format(unformat);
        }

        if (path.at(curr.second) == "") {
            path.at(curr.second) = curr.first;
            vector<Actor*> adjacents = curr.second->getAdjacents();
            unsigned int i = 0;
            while (i < adjacents.size()) {
                if (path.at(adjacents[i]) == "") {
                    q.push({curr.first + "`" + curr.second->getName(),
                            adjacents[i]});
                }
                ++i;
            }
        }
    }
}

string ActorGraph::format(string unformat) {
    string toformat = unformat;
    string postformat = "";

    toformat = toformat.substr(1);
    toformat = "(" + toformat + ")";

    char curr;
    bool isActor = true;
    unsigned int i = 0;

    while (i < toformat.length()) {
        curr = toformat.at(i);
        if (curr == '`')
            if (isActor) {
                postformat += ")--[";
                isActor = false;
            } else {
                postformat += "]-->(";
                isActor = true;
            }
        else {
            postformat += curr;
        }
        ++i;
    }
    return postformat;
}

ActorGraph::~ActorGraph() { clearhelper(); }

unordered_map<string, Actor*> ActorGraph::getNodes() { return n; }
