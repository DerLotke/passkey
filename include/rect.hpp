#pragma once

namespace UI {
    struct Rect
    {
        int x;
        int y;
        unsigned width;
        unsigned height;

        /** This creates an invalid rectangle */
        Rect(): x(0), y(0), width(0), height(0) {}

        /** This creates a potentialy valid rectangle */
        Rect(int _x, int _y, unsigned _width, unsigned _height):
            x(_x),
            y(_y),
            width(_width),
            height(_height)
        {
        }

        /**
         * @brief This converts the rectangle into screen coordinates
         * @return The converted rectangle
        */
        Rect toScreen() const;


        /** @brief This converts the rectangle into logical coordinates
         *  @return The converted rectangle
        */
        Rect toLogical() const;

        /** @brief Intersects two rectangles */
        Rect intersect(const Rect &other) const;

        /** @brief Returns if a rectangle is valid*/
        bool isValid() const;
    };
}
