cmake_minimum_required(VERSION 3.27)
project(algolab)


find_package(CGAL)
find_package(Boost REQUIRED)

#C++ Introduction
add_executable(hello_world C++Introduction/HelloWorld/src/main.cpp)
add_executable(sum_it C++Introduction/SumIt/src/main.cpp)
add_executable(basic_data_types C++Introduction/BasicDataTypes/src/main.cpp)
add_executable(strings C++Introduction/Strings/src/main.cpp)
add_executable(vectors C++Introduction/Vectors/src/main.cpp)
add_executable(sets C++Introduction/Sets/src/main.cpp)
add_executable(maps C++Introduction/Maps/src/main.cpp)
add_executable(dfs C++Introduction/DFS/src/main.cpp)
add_executable(bfs C++Introduction/BFS/src/main.cpp)
add_executable(sort C++Introduction/Sort/src/main.cpp)


# Week 1
add_executable(build_the_sum Week1/BuildTheSum/src/main.cpp)
add_executable(dominoes Week1/Dominoes/src/main.cpp)
add_executable(even_pairs Week1/EvenPairs/src/main.cpp)
add_executable(even_matrices Week1/EvenMatrices/src/main.cpp)


# Week 2
add_executable(burning_coins Week2/BurningCoins/src/main.cpp)
add_executable(the_great_game Week2/TheGreatGame/src/main.cpp)
add_executable(beach_bars Week2/BeachBars/src/main.cpp)
add_executable(lord_voldemort Week2/LordVoldemort/src/main.cpp)


# Week 3
add_executable(important_bridges Week3/ImportantBridges/src/main.cpp)
add_executable(buddy_selection Week3/BuddySelection/src/main.cpp)
add_executable(ant_challenge Week3/AntChallenge/src/main.cpp)
add_executable(first_steps_with_bgl Week3/FirstStepsWithBGL/src/main.cpp)

target_link_libraries(important_bridges Boost::boost)
target_link_libraries(buddy_selection Boost::boost)
target_link_libraries(ant_challenge Boost::boost)
target_link_libraries(first_steps_with_bgl Boost::boost)


# Week 4
add_executable(hit Week4/Hit/src/main.cpp)
add_executable(first_hit Week4/FirstHit/src/main.cpp)
add_executable(antenna Week4/Antenna/src/main.cpp)
add_executable(hiking_maps Week4/HikingMaps/src/main.cpp)

target_link_libraries(hit CGAL::CGAL)
target_link_libraries(first_hit CGAL::CGAL)
target_link_libraries(antenna CGAL::CGAL)
target_link_libraries(hiking_maps CGAL::CGAL)


# Week 5
add_executable(moving_books Week5/MovingBooks/src/main.cpp)
add_executable(boats Week5/Boats/src/main.cpp)
add_executable(asterix_the_gaul Week5/AsterixTheGaul/src/main.cpp)
add_executable(severus_snape Week5/SeverusSnape/src/main.cpp)


# Week 6

add_executable(coin_tossing Week6/CoinTossingTournament/src/main.cpp)
add_executable(knights Week6/Knights/src/main.cpp)
add_executable(london Week6/London/src/main.cpp)
add_executable(london_alternative Week6/London/src/main_lessnodes.cpp)
add_executable(tiles Week6/Tiles/src/main.cpp)

target_link_libraries(coin_tossing Boost::boost)
target_link_libraries(knights Boost::boost)
target_link_libraries(london Boost::boost)
target_link_libraries(london_alternative Boost::boost)
target_link_libraries(tiles Boost::boost)


# Problems Of The Week

add_executable(deck_of_cards ProblemOfTheWeek/DeckOfCards/src/main.cpp)
add_executable(james_bonds_sovereign ProblemOfTheWeek/JamesBondsSovereigns/src/main.cpp)
add_executable(the_iron_islands ProblemOfTheWeek/TheIronIslands/src/main.cpp)
add_executable(planet_express ProblemOfTheWeek/PlanetExpress/src/main.cpp)
add_executable(motorcycles ProblemOfTheWeek/Motorcycles/src/main.cpp)

target_link_libraries(motorcycles CGAL::CGAL)
target_link_libraries(planet_express Boost::boost)







