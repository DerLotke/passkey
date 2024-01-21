#include "passkey_app.hpp"
#include "sdcard.hpp"
#include "config.hpp"

#include <functional>

PassKeyApplication::PassKeyApplication(UI::Theme const& theme): UI::Application(),
    keyboard_(false),
    statusBar_(0, theme, this),
    typekeyMenu_(
        [this]( UI::AbstractMenuBar& menuBar, UI::AbstractMenuBar::EventData const& eventData)
	    {
            onMenuEvent(menuBar, eventData);
        }, 
        this, 
        UI::VerticalMenu, 
        loadDirectoryContent(), 
        getMenuArea(),
        theme, 
        0)
{
    typekeyMenu_.makeActive();
}

PassKeyApplication::~PassKeyApplication()
{
}

void PassKeyApplication::update()
{
    UI::Application::update(); //Call the update from the base class

    keyboard_.tick(); // Tick the Keyboard here
}

void PassKeyApplication::updateStatusBar(UsbKeyboard::EventData const * const event)
{
    if(event)
    {
        statusBar_.setCapsLockStatus(event->self->isCapsLockSet());
        statusBar_.setNumLockStatus(event->self->isNumLockSet());
        statusBar_.setScrollLockStatus(event->self->isScrollLockSet());
    }
}

UI::AbstractMenuBar::MenuItems PassKeyApplication::loadDirectoryContent()
{
  UI::AbstractMenuBar::MenuItems result;
  std::shared_ptr<SDCard> sdCard = SDCard::load();
  std::shared_ptr<DIR> directory = sdCard->openDir("");

  dirent *dir;
  while((dir = readdir(directory.get())))
  {
      if(DT_REG == dir->d_type)
      {
            if (dir->d_name != configFileName())
	    {
                result.emplace_back(String(dir->d_name));
	    }
      }
  }

  if(result.empty()) {
    result.emplace_back(String("No Files found"));
  }

  return result;
}

void PassKeyApplication::onMenuEvent(UI::AbstractMenuBar &menuBar, UI::AbstractMenuBar::EventData const &eventData)
{
    	std::shared_ptr<SDCard> sdCard = SDCard::load();
        KeyStrokeFile file(sdCard->open(menuBar.selectedItem(), SDCard::OpenMode::FILE_READONLY));
        keyboard_.restoreOriginalLedState();
	    keyboard_.sendKeyStrokes(file);
}

UI::Rect PassKeyApplication::getMenuArea() const
{
    UI::Rect screen = getFullFrameRect();
    
    return UI::Rect(0,1,screen.width, screen.height -1);
}
