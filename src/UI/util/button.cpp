#include "UI/util/button.hpp"
#include <raylib.h>

Button::Button(const char* imagePath, Vector2 imagePosition): 
      texture(LoadTexture(imagePath)), 
      position(imagePosition),
      startingWidth(texture.width),
      startingHeight(texture.height)
{

}

Button::Button(const char* imagePath): Button(imagePath, {0.0f, 0.0f}) {}

Button::~Button() {
  UnloadTexture(texture);
}

void Button::draw() const {
  DrawTextureV(texture, position, WHITE);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed) const {
  Rectangle hitBox = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};

  return CheckCollisionPointRec(mousePos, hitBox) && mousePressed;
}

void Button::setX(const float x) noexcept {
  position.x = x;
}

void Button::setY(const float y) noexcept {
  position.y = y;
}

float Button::getX() const noexcept {
  return position.x;
}

float Button::getY() const noexcept {
  return position.y;
}

void Button::setWidth(const int width) {
  texture.width = width;
}

void Button::setHeight(const int height) {
  texture.height = height;
}

int Button::getWidth() const {
  return texture.width;
}

int Button::getHeight() const {
  return texture.height;
}

void Button::scaleBySettingWidth(const int width) {
  texture.height = width*texture.height/texture.width;
  texture.width = width;
}

void Button::scaleBySettingHeight(const int height) {
  texture.width = height*texture.width/texture.height;
  texture.height = height;
}

void Button::scale(const float k) {
  texture.width *= k;
  texture.height *= k;
}

void Button::restoreOriginalDimensions() {
  texture.height = startingHeight;
  texture.width = startingWidth;
}

void Button::setPositionByMiddle(Vector2 position) {
  this->position.x = position.x - static_cast<float>(texture.width) / 2.0f;
  this->position.y = position.y - static_cast<float>(texture.height) / 2.0f;
}
