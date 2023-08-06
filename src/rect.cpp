#include "rect.hpp"

namespace UI
{
    Rect Rect::toScreen() const
    {
        return Rect(x * 8, y * 16, width * 8, height * 16);
    }

    Rect Rect::toLogical() const
    {
        return Rect(x / 8, y / 16, width / 8, height / 16);
    }

    Rect Rect::intersect(const Rect &other) const
    {
        if(isValid() && other.isValid() && other.x < width && other.y < height) {
            const int newX = other.x + x;
            const int newY = other.y + y;
            const unsigned newWidth = other.x + other.width > width ? width - other.x : other.width;
            const unsigned newHeight = other.y + other.height > height ? height - other.y : other.height;
        
            return Rect( newX, newY, newWidth, newHeight);
        } else {
            return Rect();
        }
    }

    bool Rect::isValid() const
    {
        return !(x == 0 && y == 0 && width == 0 && height == 0);
    }

} // namespace UI
