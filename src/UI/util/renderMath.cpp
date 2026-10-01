#include "UI/util/renderMath.hpp"
#include <algorithm>


namespace RenderMath {
  void scaleToWidth(Vector2& renderSize, const int desiredWidth) {
    renderSize.y = desiredWidth * renderSize.y / renderSize.x;
    renderSize.x = desiredWidth;
  }

  void scaleToHeight(Vector2& renderSize, const int desiredHeight) {
    renderSize.x = desiredHeight * renderSize.x / renderSize.y;
    renderSize.y = desiredHeight;
  }

  void setWidth(Vector2& renderSize, const int desiredWidth) {
    renderSize.x = desiredWidth;
  }

  void setHeight(Vector2& renderSize, const int desiredHeight) {
    renderSize.y = desiredHeight;
  }

  void scaleToContainTexture(Vector2& renderSize, const int desiredWidth, const int desiredHeight) {
    const float scaleX =  desiredWidth / renderSize.x;
    const float scaleY = desiredHeight / renderSize.y;

    const float finalScale = std::min(scaleX, scaleY);

    renderSize.x *= finalScale;
    renderSize.y *= finalScale;
  }

  void scaleToOverflowTexture(Vector2& renderSize, const int desiredWidth, const int desiredHeight) {
        const float scaleX =  desiredWidth / renderSize.x;
    const float scaleY = desiredHeight / renderSize.y;

    const float finalScale = std::max(scaleX, scaleY);

    renderSize.x *= finalScale;
    renderSize.y *= finalScale;
  }

  void scale(Vector2& renderSize, const float k) {
    renderSize.x *= k;
    renderSize.y *= k;
  }

}
