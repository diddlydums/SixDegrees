add_library (actorgraph_dep ActorGraph.cpp)
target_include_directories(actorgraph_dep PUBLIC .)

add_library(Actor Actor.cpp)
target_include_directories(Actor PUBLIC .)
target_link_libraries(actorgraph_dep PUBLIC Actor)
