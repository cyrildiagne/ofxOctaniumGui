//
//  AppGuiBase.cpp
//  example
//
//  Created by kikko on 3/12/13.
//
//

#include "AppGuiBase.h"

#include <iostream.h>

#include "ofUtils.h"
#include "ofSystemUtils.h"

using namespace octanium::gui;
using namespace Gwen;

/* Menu */

GWEN_CONTROL_CONSTRUCTOR( Menu )
{
    m_file = m_window = NULL;
    i_new = i_load = i_save = i_save_as = NULL;
    i_logs = i_settings = i_help = NULL;
    
    m_logo = AddItem("", "picto_logo.png", "\t\t");
    m_logo->GetMenu()->AddItem("about")->SetAction( this, &ThisClass::aboutItemSelected );
}

void Menu::addItem(MenuType menuType, int itemType, string label, string shortcut, string icon)
{
    Controls::MenuItem *menu = getMenu(menuType);
    Controls::MenuItem **menuItemPtr = getMenuItemPtr(itemType);
    Controls::MenuItem *menuItem = *menuItemPtr;
    
    if(menuItem) delete menuItem; // Todo : test this!
    
    *menuItemPtr = menuItem = menu->GetMenu()->AddItem(label, icon, shortcut);
    
    switch (menuType) {
        case MENU_FILE:
            menuItem->SetAction( this, &ThisClass::fileItemSelected ); break;
        case MENU_WINDOW:
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
            
        default:
            break;
    }
}

void Menu::menuItemSelected( Base* pControl )
{
    //Gwen::Controls::MenuItem* pMenuItem = ( Gwen::Controls::MenuItem* ) pControl;
    //PrintText( Utility::Format( L"Menu Selected: %ls", pMenuItem->GetText().GetUnicode().c_str() ) );
}

void Menu::aboutItemSelected( Base* pControl )
{
    AboutWindow* aWindow = new AboutWindow(GetParent());
    aWindow->m_Text->SetText("Octanium.eu 2012");
    int aW = aWindow->Width();
    int aH = aWindow->Height();
    aWindow->m_Text->SetPos( (aW-aWindow->m_Text->Width())*0.5, (aH-aWindow->m_Text->Height())*0.5 );
}

void Menu::windowItemSelected( Base* pControl )
{
    int windowType = -1;
    if(pControl == i_logs) {
        windowType = WINDOW_LOG;
    } else if(pControl == i_settings) {
        windowType = WINDOW_SETTINGS;
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


/* AboutWindow */


GWEN_CONTROL_CONSTRUCTOR( AboutWindow )
{
    SetTitle( Utility::Format( L"About" ) );
    int w = 200;
    int h = 200;
    SetSize( w, h );
    SetPos( (GetParent()->Width()-w)*0.5,  (GetParent()->Height()-h)*0.5);
    SetDeleteOnClose(true);
    
    m_Text = new Controls::Label( this );
    m_Text->MakeColorBright();
    m_Text->Dock( Pos::Fill );
}



/* AppGuiBase */

GWEN_CONTROL_CONSTRUCTOR( AppGuiBase )
{
    SetSize(1024, 768);
    Dock( Pos::Fill );
    
    // menu
    menu = new Menu( this );
    
    // log window
    logWindow = new LogWindow( this );
    menu->addWindowMenuDelegate(this);
    
    // settings window
    settingsWindow = new SettingsWindow(this);
    settingsWindow->Hide();
    
    // status bar
	m_StatusBar = new Controls::StatusBar( this );
	m_StatusBar->Dock( Pos::Bottom );
    
    // start
    m_StatusBar->SendToBack();
	m_fLastSecond = Gwen::Platform::GetTimeInSeconds();
	m_iFrames = 0;
}

void AppGuiBase::openWindow(int windowType)
{
    if(windowType == WINDOW_LOG) {
        logWindow->Show();
    } else if (windowType == WINDOW_SETTINGS) {
        settingsWindow->Show();
    }
}

void AppGuiBase::Render( Gwen::Skin::Base* skin )
{
	m_iFrames++;
    
	if ( m_fLastSecond < Gwen::Platform::GetTimeInSeconds() )
	{
        Controls::Layout::Table* logTable = logWindow->m_TextOutput->GetTable();
        
        UnicodeString lastStatus;
        
        if( logTable->RowCount(0) ) {
            lastStatus = logTable->GetRow( logTable->RowCount(0)-1 )->GetText(0).GetUnicode();
            lastStatus.erase(lastStatus.size()-1);
        }
        
		m_StatusBar->SetText( lastStatus + Gwen::Utility::Format( L" - %i fps", m_iFrames * 2 ) );
		m_fLastSecond = Gwen::Platform::GetTimeInSeconds() + 0.5f;
		m_iFrames = 0;
	}
    
	BaseClass::Render( skin );
}