cmake_minimum_required(VERSION 3.10)

project(Game)

find_package(SQLite3 REQUIRED)

add_executable(Game main.cpp Game.cpp Hero.cpp Enemy.cpp Monster.cpp Opponent.cpp Battle.cpp Cave.cpp Factory.cpp Weapon.cpp Database.cpp)

target_link_libraries(Game PRIVATE SQLite::SQLite3)