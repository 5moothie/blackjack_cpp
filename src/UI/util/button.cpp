#include "UI/util/button.hpp"
#include <raylib.h>
#include "UI/util/renderMath.hpp"

Button::Button(const char* imagePath, Vector2 imagePosition): 
      texture(LoadTexture(imagePath)), 
      position(imagePosition),
      renderSize({static_cast<float>(texture.width), static_cast<float>(texture.height)}) {
        
}

Button::Button(const char* imagePath): Button(imagePath, {0.0f, 0.0f}) {}

Button::~Button() {
  UnloadTexture(texture);
}

void Button::draw() const {
  Rectangle sourceRec = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
  Rectangle destRec = {position.x, position.y, renderSize.x, renderSize.y};

  DrawTexturePro(texture, sourceRec, destRec, {0.0f, 0.0f}, 0.0f, WHITE);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed) const {
  Rectangle hitBox = {position.x, position.y, renderSize.x, renderSize.y};

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
  RenderMath::setWidth(renderSize, width);
}

void Button::setHeight(const int height) {
  RenderMath::setHeight(renderSize, height);
}

int Button::getWidth() const {
  return renderSize.x;
}

int Button::getHeight() const {
  return renderSize.y;
}

void Button::scaleToWidth(const int width) {
  RenderMath::scaleToWidth(renderSize, width);
}

void Button::scaleToHeight(const int height) {
  RenderMath::scaleToHeight(renderSize, height);
}

void Button::scale(const float k) {
  RenderMath::scale(renderSize, k);
}

void Button::restoreOriginalDimensions() {
  renderSize.x = texture.width;
  renderSize.y = texture.height;
}

void Button::setPositionByMiddle(Vector2 position) {
  this->position.x = position.x - renderSize.x / 2.0f;
  this->position.y = position.y - renderSize.y / 2.0f;
}
