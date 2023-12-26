#include "menu.hpp"

namespace UI {

VerticalMenuBar::VerticalMenuBar(const AbstractMenuBar::MenuItems &menuItems,
                        Rect area,
                        unsigned selected = 0,
                        Widget * const parent = nullptr
                        ): AbstractMenuBar(menuItems, selected),
                           Widget(area, parent)
{
    for(unsigned i=0; i< itemsOnDisplay(); ++i)
    {
        menuLabel_.emplace_back(std::make_shared<Label>(Rect(1,i,area_.width - 2, 1),"",this));
    }

    selectLabel_ = std::make_shared<Label>(Rect(0,0,1,1),"\x10S",this);
    upLabel_ = std::make_shared<Label>(Rect(area.width-1,0,1,1)," ",this);
    downLabel_ = std::make_shared<Label>(Rect(area.width-1,area.height-1,1,1),"\x19",this);
    updateDisplayedLabels();
}

VerticalMenuBar::VerticalMenuBar(const AbstractMenuBar::MenuItems &menuItems,
                        Rect area,
                        Theme const& theme,
                        unsigned selected = 0,
                        Widget * const parent = nullptr
                        ): VerticalMenuBar(menuItems, area, selected, parent)
{
    setTheme(theme);
}

VerticalMenuBar::~VerticalMenuBar()
{
    /*All this is not needed but I feel better that way*/
    menuLabel_.clear();
    selectLabel_.reset();
    upLabel_.reset();
    downLabel_.reset();
}

unsigned VerticalMenuBar::itemsOnDisplay() const
{
    return area_.height;
}

void VerticalMenuBar::selectNext()
{
    AbstractMenuBar::selectNext();
    updateDisplayedLabels();
}

void VerticalMenuBar::selectPrevious()
{
    AbstractMenuBar::selectPrevious();
    updateDisplayedLabels();
}

void VerticalMenuBar::updateDisplayedLabels()
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

void VerticalMenuBar::setTheme(Theme const& theme)
{
    Widget::setTheme(theme);
    for (std::shared_ptr<Label> menuLabel : menuLabel_)
    {
        menuLabel->setTheme(theme);
    }
    selectLabel_->setTheme(theme);
    upLabel_->setTheme(theme);
    downLabel_->setTheme(theme);
}

}//namespace UI
