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
                .border = TFT_GREEN
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
                .border = TFT_WHITE
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
                .border = TFT_SKYBLUE
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
                .border = TFT_GOLD
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
                .border = TFT_BLACK
            }
        }
    },
};

auto UI::themes() -> std::map<String, Theme> const&
{
    return themes_;
}
