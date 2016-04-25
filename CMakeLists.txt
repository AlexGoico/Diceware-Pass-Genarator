cmake_minimum_required(VERSION 3.0)

add_executable(diceware diceware.cpp)

set_property(TARGET diceware PROPERTY CXX_STANDARD 11)
set_property(TARGET diceware PROPERTY CXX_STANDARD_REQUIRED ON)
