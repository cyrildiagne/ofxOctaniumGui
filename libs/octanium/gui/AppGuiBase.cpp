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
#include "ofAppRunner.h"

using namespace octanium::gui;
using namespace Gwen;


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
    } else if(windowType == WINDOW_ABOUT) {
        AboutWindow* aWindow = new AboutWindow(GetParent());
        aWindow->m_Text->SetText("Octanium.eu 2012");
        int aW = aWindow->Width();
        int aH = aWindow->Height();
        aWindow->m_Text->SetPos( (aW-aWindow->m_Text->Width())*0.5, (aH-aWindow->m_Text->Height())*0.5 );
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
		m_StatusBar->SetText( lastStatus + Gwen::Utility::Format( L" - %i fps", /*m_iFrames * 2 */ (int)ofGetFrameRate() ) );
		m_fLastSecond = Gwen::Platform::GetTimeInSeconds() + 0.5f;
		m_iFrames = 0;
	}
    
	BaseClass::Render( skin );
}