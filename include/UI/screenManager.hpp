#pragma once

enum class ProgramScreen {
  MAIN_MENU,
  BLACKJACK_GAME,
};


class ScreenManager {
private:
  ProgramScreen screen{ProgramScreen::MAIN_MENU};

public:
  void setScreen(ProgramScreen screen) noexcept { this->screen = screen; }
  [[nodiscard]] ProgramScreen getScreen() const noexcept { return screen; }
};

