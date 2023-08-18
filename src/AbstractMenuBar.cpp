#include "menu.hpp"

namespace UI
{
    AbstractMenuBar::AbstractMenuBar(const std::list<String> &menuItems,
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
        unsigned const displayedBefore = (itemsOnDisplay() - 1) / 2;
        return selectedItem_ > displayedBefore ? selectedItem_ - displayedBefore : 0; 
    }


    unsigned AbstractMenuBar::lastItemToDisplay() const
    {
        unsigned const displayedAfter = (itemsOnDisplay() - 1) / 2;
        return items_.size() > displayedAfter + selectedItem_ ? selectedItem_ + displayedAfter : items_.size(); 

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
