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

#include "ofxXmlSettings.h"
#include "ofxOctaniumGuiLogger.h"

using namespace octanium::gui;

class ofxOctaniumGui : public ofxGwen, public SettingsWindowDelegate {
    
public:
    
    void setup();
    
    void show();
    void hide();
    void toggleView() { if (isVisible()) hide(); else show(); }
    
    void loadSettings(string filename);
    
    void loadSettings();
    void saveSettings();
    void saveSettingsAs();
    void resetSettings();
    
    AppGuiBase* get() { return appGui; }
    
    /* Components */
    
    void addSlider(string name, float& prop, float minValue, float maxValue);
    void addCheckbox(string name, bool& prop);
    
    /* App Menu */
    
    void addAppMenuItem(MenuItemType type, string label, string shortcut = "", string icon = "") {
        appGui->getMenu()->addItem(MENU_APP, type, label, shortcut, icon);
    }
    
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
    
    ofxXmlSettings settingsXML;
    string currSettingsFilePath;
    
    char* getComponentId(string label);
    
    void save(string filename);
    void load(string xmlPath);
    void keyPressed(ofKeyEventArgs& args);
};

#endif
