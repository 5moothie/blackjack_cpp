#pragma once

#include<raylib.h>

class Background {
private:
  Texture2D texture;
  Vector2 position = {0.0f, 0.0f};
  Vector2 renderSize;

public:
  Background(const char* imagePath);
  ~Background();

  // no copying or moving
  Background(const Background&) = delete;
  Background& operator=(const Background&) = delete;
  Background(Background&&) noexcept = delete;
  Background& operator=(Background&&) noexcept = delete;


  void draw() const;

  void scaleToWidth(const int width);
  void scaleToHeight(const int height);
  void setWidth(const int width);
  void setHeight(const int height);

  void scaleToContainTexture(const int width, const int height);
  void scaleToOverflowTexture(const int width, const int height);
  void scale(const float k);

  void positionInTheMiddle(const int windowWidth, const int windowHeight);
};