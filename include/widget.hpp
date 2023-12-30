#pragma once

#include <TFT_eSPI.h>

#include <rect.hpp>
#include <colors.hpp>
#include <themes.hpp>


namespace UI {
    class Widget
    {
        public:
        explicit Widget(const Rect &area, Widget * const parent = nullptr);
        explicit Widget(const Rect &area, Theme const& theme, Widget * const parent = nullptr);
        virtual ~Widget();

        virtual void redraw(TFT_eSprite &drawBuffer, const Rect &clientArea) const;
        virtual void setFaceColor(Color color) { faceColor_ = color; }
        Color getFaceColor() const { return faceColor_; }

        virtual void setTheme(Theme const& theme) { faceColor_ = theme.colors.background; }

	void setHidden(bool hidden) { hidden_ = hidden; }
	bool isHidden() { return hidden_; }

        void moveTo(int x, int y) { area_.x = x; area_.y = y; }

	Widget const * getSibling() const {return nextSibling_;}

        protected:
        virtual void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const;

        Rect area_;
        Widget * parent_;
        Widget * child_;
        Widget * nextSibling_;
        Color faceColor_;
	bool hidden_;
    };
}
