cmake_minimum_required(VERSION 3.27)
project(algolab)
set(CMAKE_CXX_STANDARD 14)


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
add_executable(tiles Week6/Tiles/src/main.cpp)

target_link_libraries(coin_tossing Boost::boost)
target_link_libraries(knights Boost::boost)
target_link_libraries(london Boost::boost)
target_link_libraries(tiles Boost::boost)


# Week 7

add_executable(bistro Week7/Bistro/src/main.cpp)
add_executable(germs Week7/Germs/src/main.cpp)
add_executable(h1n1 Week7/H1N1/src/main.cpp)
add_executable(golden_eye Week7/GoldenEye/src/main.cpp)

target_link_libraries(bistro CGAL::CGAL)
target_link_libraries(germs CGAL::CGAL)
target_link_libraries(h1n1 CGAL::CGAL)
target_link_libraries(golden_eye CGAL::CGAL)
target_link_libraries(golden_eye Boost::boost)


# Week 8

add_executable(what_is_the_maximum Week8/WhatIsTheMaximum/src/main.cpp)
add_executable(diet Week8/Diet/src/main.cpp)
add_executable(inball Week8/Inball/src/main.cpp)
add_executable(suez Week8/Suez/src/main.cpp)

target_link_libraries(what_is_the_maximum CGAL::CGAL)
target_link_libraries(diet CGAL::CGAL)
target_link_libraries(inball CGAL::CGAL)
target_link_libraries(suez CGAL::CGAL)


# Week 9

add_executable(canteen Week9/Canteen/src/main.cpp)
add_executable(placing_knights Week9/PlacingKnights/src/main.cpp)
add_executable(real_estate_market Week9/RealEstateMarket/src/main.cpp)
add_executable(algocoon Week9/Algocoon/src/main.cpp)

target_link_libraries(canteen Boost::boost)
target_link_libraries(placing_knights Boost::boost)
target_link_libraries(real_estate_market Boost::boost)
target_link_libraries(algocoon Boost::boost)


# Week 10

add_executable(san_francisco Week10/SanFrancisco/src/main.cpp)
add_executable(surveillance_photograph Week10/SurveillancePhotograph/src/main.cpp)
add_executable(rubeus_hagrid Week10/RubeusHagrid/src/main.cpp)
add_executable(clues Week10/Clues/src/main.cpp)

target_link_libraries(surveillance_photograph Boost::boost)
target_link_libraries(clues Boost::boost)
target_link_libraries(clues CGAL::CGAL)


# Week 11

add_executable(asterix_and_the_chariot_race Week11/AsterixAndTheChariotRace/src/main.cpp)
add_executable(dean_thomas Week11/DeanThomas/src/main.cpp)
add_executable(legions Week11/Legions/src/main.cpp)
add_executable(phantom_menace Week11/PhantomMenace/src/main.cpp)

target_link_libraries(dean_thomas CGAL::CGAL)
target_link_libraries(legions CGAL::CGAL)
target_link_libraries(phantom_menace Boost::boost)


# Week 12

add_executable(new_york Week12/NewYork/src/main.cpp)
add_executable(return_of_the_jedi Week12/ReturnOfTheJedi/src/main.cpp)
add_executable(rumpelstitskin Week12/Rumpelstitskin/src/main.cpp)
add_executable(world_cup Week12/WorldCup/src/main.cpp)

target_link_libraries(return_of_the_jedi Boost::boost)
target_link_libraries(rumpelstitskin Boost::boost)
target_link_libraries(world_cup CGAL::CGAL)


# Problems Of The Week

add_executable(deck_of_cards ProblemOfTheWeek/DeckOfCards/src/main.cpp)
add_executable(james_bonds_sovereign ProblemOfTheWeek/JamesBondsSovereigns/src/main.cpp)
add_executable(the_iron_islands ProblemOfTheWeek/TheIronIslands/src/main.cpp)
add_executable(planet_express ProblemOfTheWeek/PlanetExpress/src/main.cpp)
add_executable(motorcycles ProblemOfTheWeek/Motorcycles/src/main.cpp)
add_executable(octopussy ProblemOfTheWeek/Octopussy/src/main.cpp)
add_executable(octopussy_alternative ProblemOfTheWeek/Octopussy/src/main_fromleaves.cpp)
add_executable(kingdom_defense ProblemOfTheWeek/KingdomDefense/src/main.cpp)
add_executable(idefix ProblemOfTheWeek/Idefix/src/main.cpp)
add_executable(lannister ProblemOfTheWeek/Lannister/src/main.cpp)
add_executable(india ProblemOfTheWeek/India/src/main.cpp)

add_executable(schneewittchen ProblemOfTheWeek/Schneewittchen/src/main.cpp)

target_link_libraries(motorcycles CGAL::CGAL)
target_link_libraries(planet_express Boost::boost)
target_link_libraries(kingdom_defense Boost::boost)
target_link_libraries(idefix CGAL::CGAL)
target_link_libraries(idefix Boost::boost)
target_link_libraries(lannister CGAL::CGAL)
target_link_libraries(india Boost::boost)
target_link_libraries(schneewittchen CGAL::CGAL)






