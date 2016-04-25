add_executable(dwgen main.cpp)

add_library(diceware diceware.cpp)

set_property(TARGET diceware PROPERTY CXX_STANDARD 11)
set_property(TARGET diceware PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET dwgen PROPERTY CXX_STANDARD 11)
set_property(TARGET dwgen PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(dwgen diceware)
