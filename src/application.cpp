#include "application.hpp"
#include "ec1834.hpp"
#include <TFT_eSPI.h>

static TFT_eSPI tft_;
static TFT_eSprite backBuffer_(&tft_);
static bool tftInitialized_ = false;


namespace UI {
    Application::Application(Application * parent):
        Widget(getFullFrameRect(), parent)
    {
        if (!tftInitialized_)
        {
            tft_.init();

            backBuffer_.createSprite(TFT_HEIGHT, TFT_WIDTH);
            backBuffer_.setAttribute(UTF8_SWITCH,0);
            backBuffer_.fillScreen(TFT_BLACK);
            backBuffer_.setTextColor(TFT_GREEN, TFT_BLACK);
            ec1834bin_select(backBuffer_);

            tft_.setAttribute(UTF8_SWITCH,0);
            tft_.setRotation(1);
            tft_.fillScreen(TFT_BLACK);
            tft_.setTextColor(TFT_GREEN, TFT_BLACK);
            ec1834bin_select(tft_);
            tftInitialized_ = true;
        }
    }

    void Application::update()
    {
        redraw(backBuffer_, getFullFrameRect());
        backBuffer_.pushSprite(0,0);
    }
}
