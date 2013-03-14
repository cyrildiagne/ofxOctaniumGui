//
//  ofxOctaniumApp.h
//  guitar_test1
//
//  Created by kikko on 3/12/13.
//
//

#ifndef guitar_test1_ofxOctaniumApp_h
#define guitar_test1_ofxOctaniumApp_h

#define OFXGWEN_USE_OFX_FONTSTASH

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


class ofxOctaniumGui : public ofxGwen {
    
public:
    
    void setup();
    
    void show();
    void hide();
    void toggleView() { if (isVisible()) hide(); else show(); }
    
    
    
    AppGuiBase* get() { return appGui; }
    
    /* Components */
    
    void addSlider(string name, float& prop, float minValue, float maxValue);
    
    /* File  Menu */
    
    void addFileMenuItem(MenuItemType type, string label, string shortcut = "", string icon = "") {
        appGui->getMenu()->addItem(MENU_FILE, type, label, shortcut, icon);
    }
    
    void addFileMenuDelegate( FileMenuDelegate* delegate ) {
        appGui->getMenu()->addFileMenuDelegate(delegate);
    }
    
    /* Window Menu */
    
    void addWindowMenuItem(MenuItemType type, string label="", string shortcut = "", string icon = "") {
        if(type == MENU_ITEM_LOGS)
            appGui->getMenu()->addItem(MENU_WINDOW, MENU_ITEM_LOGS, "Logs");
        else if(type == MENU_ITEM_SETTINGS)
            appGui->getMenu()->addItem(MENU_WINDOW, MENU_ITEM_SETTINGS, "Settings");
    }
    
protected:
    
    virtual Gwen::Skin::Base *createSkin(Gwen::Renderer::OpenGL *renderer, const string& default_font = "", const string& skin_texture_path = "");
    
private:
    
    AppGuiBase* appGui;
    
    ofPtr<ofxOctaniumGuiLogger> logger;
    
    void keyPressed(ofKeyEventArgs& args);
};

#endif
