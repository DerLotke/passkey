#include "menu.hpp"

namespace UI
{
    AbstractMenuBar::AbstractMenuBar(const std::vector<String> &menuItems,
                                     unsigned selected):
                                     items_(menuItems),
                                     selectedItem_(selected)
    {
    }

    AbstractMenuBar::~AbstractMenuBar()
    {
    }

    unsigned AbstractMenuBar::firstItemToDisplay() const
    {
        unsigned const displayed = itemsOnDisplay();
        unsigned displayedBefore = (displayed - 1) / 2;
        unsigned first = selectedItem_ > displayedBefore ? selectedItem_ - displayedBefore : 0;

        if (first + displayed >= items_.size())
        {
            unsigned over = (first + displayed) - items_.size();
            first = first >= over ? first - over : 0;
        }

        return first; 
    }


    unsigned AbstractMenuBar::lastItemToDisplay() const
    {
        unsigned const displayedAfter = firstItemToDisplay() + itemsOnDisplay() - 1;
        return items_.size() > displayedAfter ? displayedAfter : items_.size() - 1; 

    }

    unsigned AbstractMenuBar::itemsToDraw() const
    {
        return lastItemToDisplay() - firstItemToDisplay();
    }

    void AbstractMenuBar::selectNext()
    {
        selectedItem_ = (selectedItem_ + 1) % items_.size();
    }

    void AbstractMenuBar::selectPrevious()
    {
        if ((--selectedItem_) < 0) {
            selectedItem_ = items_.size() - 1;
        }
    }
} // namespace UI
