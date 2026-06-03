cmake_minimum_required(VERSION 3.20)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(blackjack
  include/card.hpp
  include/suit.hpp
  include/rank.hpp
  include/hand.hpp
  include/deck.hpp
  include/shoe.hpp
  src/main.cpp
  src/card.cpp
  src/hand.cpp
  src/deck.cpp
  src/shoe.cpp
)

target_include_directories(blackjack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# find_package(raylib CONFIG REQUIRED)
# target_link_libraries(blackjack PRIVATE raylib)