//
//  Menu.cpp
//  guitar_test1
//
//  Created by kikko on 3/14/13.
//
//

#include "Menu.h"

/// TODO : get rid of oF dependency here (ofSystemLoadDialog && ofToDataPath)
#include "ofUtils.h"
#include "ofSystemUtils.h"

using namespace octanium::gui;
using namespace Gwen;

GWEN_CONTROL_CONSTRUCTOR( Menu )
{
    m_app = m_file = m_window = NULL;
    i_new = i_load = i_save = i_save_as = NULL;
    i_logs = i_settings = i_help = NULL;
}

void Menu::addItem(MenuType menuType, int itemType, string label, string shortcut, string icon)
{
    Controls::MenuItem *menu = getMenu(menuType);
    Controls::MenuItem **menuItemPtr = getMenuItemPtr(itemType);
    Controls::MenuItem *menuItem = *menuItemPtr;
    
    if(menuItem) delete menuItem; // Todo : test this!
    
    *menuItemPtr = menuItem = menu->GetMenu()->AddItem(label, icon, shortcut);
    
    // allright this shouldn't be specified here yet
    switch (menuType) {
        case MENU_FILE:
            menuItem->SetAction( this, &ThisClass::fileItemSelected ); break;
        case MENU_WINDOW:
        case MENU_APP:
            menuItem->SetAction( this, &ThisClass::windowItemSelected ); break;
            
        default:
            break;
    }
}

Controls::MenuItem * Menu::getMenu(MenuType type)
{
    switch (type) {
        case MENU_FILE:
            if(m_file==NULL) m_file = AddItem( L"File" );
            return m_file;
        case MENU_WINDOW:
            if(m_window==NULL) m_window = AddItem( L"Window" );
            return m_window;
        case MENU_APP:
            if(m_app==NULL) m_app = AddItem( "", "picto_logo.png", "\t\t" );
            return m_app;
        default:
            return NULL;
    }
}

Gwen::Controls::MenuItem ** Menu::getMenuItemPtr(int type) {
    
    switch (type) {
            
        case MENU_ITEM_NEW:     return &i_new;
        case MENU_ITEM_LOAD:    return &i_load;
        case MENU_ITEM_SAVE:    return &i_save;
        case MENU_ITEM_SAVE_AS: return &i_save_as;
        case MENU_ITEM_LOGS:    return &i_logs;
        case MENU_ITEM_SETTINGS:return &i_settings;
        case MENU_ITEM_ABOUT:   return &i_about;
        
        default:
            break;
    }
}

void Menu::windowItemSelected( Base* pControl )
{
    int windowType = -1;
    if(pControl == i_logs) {
        windowType = WINDOW_LOG;
    }
    else if(pControl == i_settings) {
        windowType = WINDOW_SETTINGS;
    }
    else if(pControl == i_about) {
        windowType = WINDOW_ABOUT;
    }
    
    for (int i=0; i < v_WindowMenuDelegates.size(); i++) {
        v_WindowMenuDelegates[i]->openWindow(windowType);
    }
}

void Menu::fileItemSelected( Base* pControl ) {
    
    Controls::MenuItem* item = (Controls::MenuItem*) pControl;
    if (item == i_new) {
        for (int i=0; i < v_FileMenuDelegates.size(); i++) {
            v_FileMenuDelegates[i]->newFile();
        }
    }
    else if (item == i_load) {
        ofFileDialogResult dialogResult = ofSystemLoadDialog("", false, ofToDataPath("", true));
        if(dialogResult.bSuccess) {
            for (int i=0; i < v_FileMenuDelegates.size(); i++) {
                v_FileMenuDelegates[i]->loadFile(dialogResult.filePath);
            }
        }
    }
    else if (item == i_save || item == i_save_as) {
        ofFileDialogResult dialogResult = ofSystemSaveDialog("", "Save file as..");
        if(dialogResult.bSuccess) {
            for (int i=0; i < v_FileMenuDelegates.size(); i++) {
                v_FileMenuDelegates[i]->saveFile(dialogResult.filePath);
            }
        }
    }
}