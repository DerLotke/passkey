#include "themes.hpp"

using namespace UI;

static std::map<String, Theme> const themes_{
    {
        "robotron",
        {
            .colors = {
                .background = TFT_BLACK,
                .text = TFT_GREEN,
                .highlight = TFT_GREEN,
                .heading = TFT_GREEN
            }
        }
    },
    {
        "cafe",
        {
            .colors = {
                .background = TFT_BROWN,
                .text = TFT_WHITE,
                .highlight = TFT_GOLD,
                .heading = TFT_SILVER
            }
        }
    },
    {
        "c64",
        {
            .colors = {
                .background = TFT_BLUE,
                .text = TFT_SKYBLUE,
                .highlight = TFT_SKYBLUE,
                .heading = TFT_SKYBLUE
            }
        }
    },
    {
        "hazelnut",
        {
            .colors = {
                .background = TFT_MAROON,
                .text = TFT_GOLD,
                .highlight = TFT_SILVER,
                .heading = TFT_GOLD
            }
        }
    },
    {
        "bumblebee",
        {
            .colors = {
                .background = TFT_YELLOW,
                .text = TFT_BLACK,
                .highlight = TFT_MAROON,
                .heading = TFT_BLACK
            }
        }
    },
};

auto UI::themes() -> std::map<String, Theme> const&
{
    return themes_;
}
