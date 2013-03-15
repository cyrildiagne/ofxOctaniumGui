//
//  LogWindow.h
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#ifndef __guitar_test1__LogWindow__
#define __guitar_test1__LogWindow__

#include <iostream>
#include "Gwen/Gwen.h"
#include "Gwen/Align.h"
#include "Gwen/Utility.h"
#include "Gwen/Controls.h"
#include "Gwen/Controls/WindowControl.h"

using namespace std;

namespace octanium {
    
    namespace gui {
        
        enum LogLevel {
            LOG_LEVEL_LOG,
            LOG_LEVEL_WARNING,
            LOG_LEVEL_ERROR
        };
        
        
        class LogWindow : public Gwen::Controls::WindowControl {
            
        public:
            
            GWEN_CONTROL( LogWindow, Gwen::Controls::WindowControl );
            
            void log(LogLevel level, const string & module, const string & message);
            void log(LogLevel level, const string & module, const char* format, ...);
            void log(LogLevel level, const string & module, const char* format, va_list args);
            
            Gwen::Controls::ListBox*	m_TextOutput;
            
        private:
            
            string getLogLevelName(LogLevel level);
        };

    }
}


#endif /* defined(__guitar_test1__LogWindow__) */
