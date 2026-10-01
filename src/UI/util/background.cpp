#include "UI/util/background.hpp"
#include <raylib.h>
#include "UI/util/renderMath.hpp"

Background::Background(const char* imagePath): texture(LoadTexture(imagePath)) {

}

Background::~Background() {
  UnloadTexture(texture);
}


void Background::draw() const {
  Rectangle sourceRec = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
  Rectangle destRec = {position.x, position.y, renderSize.x, renderSize.y};

  DrawTexturePro(texture, sourceRec, destRec, {0.0f, 0.0f}, 0.0f, WHITE);
}

void Background::scaleToWidth(const int width) {
  RenderMath::scaleToWidth(renderSize, width);
}

void Background::scaleToHeight(const int height) {
  RenderMath::scaleToHeight(renderSize, height);
}

void Background::setWidth(const int width) {
  RenderMath::setWidth(renderSize, width);
}

void Background::setHeight(const int height) {
  RenderMath::setHeight(renderSize, height);
}

void Background::scaleToContainTexture(const int width, const int height) {
  RenderMath::scaleToContainTexture(renderSize, width, height);
}

void Background::scaleToOverflowTexture(const int width, const int height) {
  RenderMath::scaleToOverflowTexture(renderSize, width, height);
}

void Background::scale(const float k) {
  RenderMath::scale(renderSize, k);
}
