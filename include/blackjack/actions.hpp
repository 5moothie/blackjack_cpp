#pragma once
enum class HandActions {
  NONE,
  HIT,
  STAND,
  DOUBLE,
  SPLIT,
};

enum class MainMenuActions {
  NONE,
  PLAY,
  QUIT,
};

enum class BetweenHandActions {
  NONE,
  MAIN_MENU,
  NEXT_HAND,
};