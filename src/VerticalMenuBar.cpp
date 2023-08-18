#include "menu.hpp"

namespace UI {

VerticalMenu::VerticalMenu(const AbstractMenuBar::MenuItems &menuItems,
                        Rect area,
                        unsigned selected = 0,
                        Widget * const parent = nullptr
                        ): AbstractMenuBar(menuItems, selected), 
                           Widget(area, parent)
{
    for(unsigned i=0; i< itemsOnDisplay(); ++i)
    {
        Label* tmp = new Label(Rect(1,i,area_.width - 1, 1),"",this);
        menuLabel_.push_back(tmp);
    }

    selectLabel_ = new Label(Rect(0,0,1,1),"\x10",this);
    updateDisplayedLabels();
}

VerticalMenu::~VerticalMenu()
{
    for(auto label : menuLabel_)
    {
        delete label;
    }

    menuLabel_.clear();
    delete selectLabel_;
}

unsigned VerticalMenu::itemsOnDisplay() const
{
    return area_.height;
}

void VerticalMenu::selectNext()
{
    AbstractMenuBar::selectNext();
    updateDisplayedLabels();
}

void VerticalMenu::selectPrevious()
{
    AbstractMenuBar::selectPrevious();
    updateDisplayedLabels();
}

void VerticalMenu::updateDisplayedLabels()
{
    for(auto label: menuLabel_)
    {
        label->setText("");
    }
    
    auto it = menuLabel_.begin();

    for(unsigned i= firstItemToDisplay(); i<= lastItemToDisplay(); ++i, ++it)
    {
        (*it)->setText(items_.at(i));

        if (i == selectedItem_) {
            (*it)->setInverted(true);
            selectLabel_->moveTo(0,i-firstItemToDisplay());
        } else {
            (*it)->setInverted(false);
        }
    }
}

}//namespace UI
