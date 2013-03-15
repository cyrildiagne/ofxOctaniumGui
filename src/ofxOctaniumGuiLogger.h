//
//  ofxOctaniumGuiLogger.h
//  guitar_test1
//
//  Created by kikko on 3/15/13.
//
//

#ifndef guitar_test1_ofxOctaniumGuiLogger_h
#define guitar_test1_ofxOctaniumGuiLogger_h

#include "ofxGwen.h"

#include "AppGuiBase.h"
#include "Delegates.h"
#include "LogWindow.h"

using namespace octanium::gui;

class ofxOctaniumGuiLogger : public ofBaseLoggerChannel {
public:
    
    void setLogWindow(LogWindow* logWindow_) {
        logWindow = logWindow_;
    }
    LogLevel getLogLevel(ofLogLevel level) {
        if(level<OF_LOG_WARNING) return LOG_LEVEL_LOG;
        else if(level<OF_LOG_ERROR) return LOG_LEVEL_WARNING;
        return LOG_LEVEL_ERROR;
    }
    void log(ofLogLevel level, const string & module, const string & message) {
        consoleChannel.log(level, module, message);
        logWindow->log(getLogLevel(level), module, message);
    }
    void log(ofLogLevel level, const string & module, const char* format, ...) {
        va_list args;
        va_start(args, format);
        log(level, module, format, args);
        va_end(args);
    }
    void log(ofLogLevel level, const string & module, const char* format, va_list args) {
        consoleChannel.log(level, module, format, args);
        LogLevel logLevel = getLogLevel(level);
        logWindow->log(logLevel, module, format, args);
    }
    
private:
    
    ofConsoleLoggerChannel consoleChannel;
    LogWindow* logWindow;
};

#endif
