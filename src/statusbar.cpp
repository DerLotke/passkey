#include "statusbar.hpp"
#include "application.hpp"

Statusbar::Statusbar(int const pos, Widget * const parent):
    UI::Widget(UI::Rect(0,pos,UI::Application::getFullFrameRect().width,1), parent),
    statusText_(UI::Rect(0,0,UI::Application::getFullFrameRect().width-3,1),"\xc4\xc4\xb4PassKey 1.0\xc3\xc4\xb4", this),
    scrollLockLabel_(UI::Rect(UI::Application::getFullFrameRect().width-3,0,1,1),"S", this),
    numLockLabel_(UI::Rect(UI::Application::getFullFrameRect().width-2,0,1,1),"N", this),
    capsLockLabel_(UI::Rect(UI::Application::getFullFrameRect().width-1,0,1,1),"C", this)
    {}


Statusbar::Statusbar(int const pos, UI::Theme const& theme, Widget * const parent):
    Statusbar(pos, parent)
{
    statusText_.usingStyle(UI::Label::Style::Heading).setTheme(theme);
    scrollLockLabel_.usingStyle(UI::Label::Style::Highlight).setTheme(theme);
    numLockLabel_.usingStyle(UI::Label::Style::Highlight).setTheme(theme);
    capsLockLabel_.usingStyle(UI::Label::Style::Highlight).setTheme(theme);
}
