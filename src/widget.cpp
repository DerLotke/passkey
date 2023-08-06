#include "widget.hpp"

namespace UI
{
    Widget::Widget(const Rect &area, Widget * const parent): 
        area_(area), 
        parent_(parent),
        child_(nullptr),
        nextSibbling_(nullptr),
        faceColor_(DefaultFaceColor)
    {
        if (parent_) {
            
            Widget * firstChild = parent_->child_;
            if (firstChild) {
                nextSibbling_ = firstChild;
            }
            parent->child_ = this;
        }
    }

    Widget::~Widget()
    {
        if(parent_) {
            Widget * previousChild = nullptr;
            Widget * child = parent_->child_;

            while(child && child != this) {
                previousChild = child;
                child = child ->nextSibbling_;
            }

            if(previousChild && child) {
                previousChild ->nextSibbling_ = nextSibbling_;
            } else if( child ) {
                parent_->child_ = nextSibbling_;
            } // else the child was not found which would be an inconsistency error and should never happen
        }
    }
    
    void Widget::redraw(TFT_eSprite &drawBuffer, const Rect &clientArea) const
    {
        Rect const newClientArea = clientArea.intersect(area_);
        
        if(newClientArea.isValid())
        {
            draw(drawBuffer, newClientArea);

            Widget const * child = child_;
            while(child) {
                child->redraw(drawBuffer,newClientArea);
                child = child->nextSibbling_;
            }
        }
    }

    void Widget::draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const
    {
        Rect area = clientArea.toScreen();
        drawBuffer.fillRect(area.x, area.y, area.width, area.height, faceColor_);
    }
}
