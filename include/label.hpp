#pragma once

#include <widget.hpp>
#include <Arduino.h>
#include <colors.hpp>
#include <themes.hpp>

namespace UI
{
    class Label : public Widget
    {
        public:

        enum class Style {
            Normal,
            Highlight,
	    Heading
        };

        explicit Label(const Rect &rect, const String &text, Widget * const parent = nullptr);
        explicit Label(
                const Rect &rect,
                const String &text,
                Theme const& theme,
                Style style = Style::Normal,
                Widget * const parent = nullptr);

        void setTextColor(Color color) { textColor_ = color; }
        Color getTextColor() const { return textColor_; }

        virtual void setFaceColor(Color color) override { origFaceColor_ = color; }

        virtual void setTheme(Theme const& theme) override
        {
            switch (style_)
            {
                default:
                    setTextColor(theme.colors.text);
                    break;
                case Style::Highlight:
                    setTextColor(theme.colors.highlight);
                    break;
                case Style::Heading:
                    setTextColor(theme.colors.heading);
                    break;
            }
            setFaceColor(theme.colors.background);
            setInverted(getInverted()); // update drawn colors
        }

        void setInverted(bool inverted);
        bool getInverted() const { return inverted_; }

        void setText(const String &newText) { text_ = newText; }

        Label& usingStyle(Style style)
        {
            style_ = style;
            return *this;
        }


        protected:

        String text_;
        Color textColor_;
        Color drawTextColor_;
        Color origFaceColor_;
        Style style_;
        bool inverted_;

        void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const override;

    };
}
