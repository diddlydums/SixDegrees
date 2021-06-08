#include <gtest/gtest.h>

#include "Actor.hpp"

using namespace std;
using namespace testing;

TEST(ActorGraphTests, TEST_constructor) {
    string name = "Javier Bardem";
    string year = "2001";
    bool isActor = true;
    Actor test(name, isActor);

    string movie = "No Country For Old Men";
    isActor = false;
    Actor testMovie(movie, isActor);

    ASSERT_EQ(test.getName(), name);
    ASSERT_EQ(testMovie.getName(), movie);
}

TEST(ActorGraphTests, TEST_addNeighbor) {
    string name = "Jack Nicholson";
    string movie = "The Shining";
    string year = "1995";
    Actor actor(name, true);
    Actor movieNode(movie, false);
    Actor* temp = &movieNode;

    actor.add(movie, temp);

    Actor* test = actor.getNext(movie);

    ASSERT_EQ(test, temp);
}

TEST(ActorGraphTests, TEST_getAdjacent) {
    string name = "Johnny Depp";
    string movie = "Pirates Of The Caribbean";
    string year = "2000";
    Actor actor(name, true);
    Actor movieNode(movie, false);
    Actor* temp = &movieNode;

    actor.add(movie, temp);

    vector<Actor*> neighborVector = actor.getAdjacents();

    ASSERT_EQ(neighborVector.size(), 1);
    ASSERT_EQ(neighborVector.at(0), temp);
}

TEST(ActorGraphTests, TEST_checkIsMovie) {
    string name = "Shrek";
    string year = "2001";
    bool isActor = false;
    Actor* movie = new Actor(name, isActor);
    ASSERT_EQ(movie->isMovie(), true);
}