cmake_minimum_required(VERSION 3.10)

project(Game)

add_executable(Game main.cpp Game.cpp Hero.cpp Enemy.cpp Monster.cpp Opponent.cpp Battle.cpp Cave.cpp Factory.cpp)
