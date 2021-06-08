#include <gtest/gtest.h>
#include <fstream>

#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

TEST(ActorGraphTests, TwoActorsOneMovie) {
    string from = "Actor 1";
    string to = "Actor 2";
    string through = "Awesome Movie\t2020";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << from << "\t" << through << endl;
    ss << to << "\t" << through << endl;

    ActorGraph graph;
    bool isBuilt = graph.buildGraph(ss);
    ASSERT_TRUE(isBuilt);
}

// TODO: add more tests for actor graph

TEST(ActorGraphTests, TEST_format) {
    string unformat =
        "`Mike Myers`Shrek#@2001`Antonio Banderas`Zorro#@1998`Catherine "
        "Zeta-Jones";
    string compare =
        "(Mike Myers)--[Shrek#@2001]-->(Antonio "
        "Banderas)--[Zorro#@1998]-->(Catherine Zeta-Jones)";
    ActorGraph ag;
    ASSERT_EQ(compare, ag.format(unformat));
}

TEST(ActorGraphTests, TEST_BFS) {
    string listnames{
        "Actor/Actress	Movie	Year\nMike Myers\tShrek\t2001\nEddie "
        "Murphy\tShrek\t2001\nAntonio Banderas\tShrek\t2001"};
    string first = "Mike Myers";
    string last = "Antonio Banderas";
    string path;

    stringstream ss;
    for (int n = 0; n < listnames.length(); ++n) {
        ss << listnames[n];
    }
    ActorGraph graph;
    bool isBuilt = graph.buildGraph(ss);
    ASSERT_EQ(isBuilt, true);
    graph.BFS(first, last, path);
    string test = "(Mike Myers)--[Shrek#@2001]-->(Antonio Banderas)";
    ASSERT_EQ(path, test);
}