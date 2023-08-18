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
        Label* tmp = new Label(Rect(1,i,area_.width - 2, 1),"",this);
        menuLabel_.push_back(tmp);
    }

    selectLabel_ = new Label(Rect(0,0,1,1),"\x10S",this);
    upLabel_ = new Label(Rect(area.width-1,0,1,1)," ",this);
    downLabel_ = new Label(Rect(area.width-1,area.height-1,1,1),"\x19",this);
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
    unsigned last = lastItemToDisplay();
    unsigned first = firstItemToDisplay();

    for(unsigned i= first; i<= last; ++i, ++it)
    {
        (*it)->setText(items_.at(i));

        if (i == selectedItem_) {
            (*it)->setInverted(true);
            selectLabel_->moveTo(0,i-first);
        } else {
            (*it)->setInverted(false);
        }

        if(first == 0) {
            upLabel_->setText(" ");
        } else {
            upLabel_->setText("\x18");
        }

        if(last < items_.size() - 1) {
            downLabel_->setText("\x19");
        }else {
            downLabel_->setText(" ");
        }
    }
}

}//namespace UI
