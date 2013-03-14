//
//  LogWindow.cpp
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#include "LogWindow.h"

using namespace octanium::gui;
using namespace Gwen;

/* LogWindow */

GWEN_CONTROL_CONSTRUCTOR( LogWindow )
{
    SetTitle( Utility::Format( L"Logs" ) );
    SetSize( 300, 400 );
    SetPos( Pos::Center );
    Hide();
    
    m_TextOutput = new Controls::ListBox( this );
    m_TextOutput->Dock( Pos::Fill );
}

void LogWindow::log(LogLevel level, const string & module, const string & message){
    
	stringstream out;
	out << "" << module << ":";
	out << getLogLevelName(level) << message << endl;
    m_TextOutput->AddItem(out.str());
	m_TextOutput->ScrollToBottom();
}

string LogWindow::getLogLevelName(LogLevel level) {
    
    switch (level) {
        case LOG_LEVEL_LOG: return "";
        case LOG_LEVEL_WARNING: return "Warning :";
        case LOG_LEVEL_ERROR: return "ERROR :";
        default:
            break;
    }
}

void LogWindow::log(LogLevel level, const string &  module, const char* format, ...){
	va_list args;
	va_start(args, format);
	log(level, module, format, args);
	va_end(args);
}

void LogWindow::log(LogLevel level, const string &  module, const char* format, va_list args){
    
    char argsBuff[1024];
    snprintf(argsBuff, 1024, format, args);
    
    stringstream out;
	out << "" << module << ":";
	out << getLogLevelName(level);
    out << argsBuff;
    
    m_TextOutput->AddItem(out.str());
	m_TextOutput->ScrollToBottom();
}