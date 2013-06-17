//
//  ofxOctaniumGui.cpp
//  guitar_test1
//
//  Created by kikko on 3/12/13.
//
//

#include "ofxOctaniumGui.h"

#include "Gwen/Skins/TexturedBase.h"
#include "CustomSkin.h"

void ofxOctaniumGui::setup() {
    
    ofxGwen::setup("OpenSans.ttf", "octanium_skin.png");
    
    appGui = new AppGuiBase( getCanvas() );
    appGui->SetPos(0, 0);
    
    appGui->getSettingsWindow()->setDelegate(this);
    appGui->openWindow(WINDOW_SETTINGS);
    
    logger = ofPtr<ofxOctaniumGuiLogger>(new ofxOctaniumGuiLogger());
    logger->setLogWindow(appGui->getLogWindow());
    
    hide();
    
    ofLog::setChannel(logger);
    
    ofAddListener(ofEvents().keyPressed, this, &ofxOctaniumGui::keyPressed);
}

void ofxOctaniumGui::show() {
    
    ofxGwen::show();
    //ofShowCursor();
}

void ofxOctaniumGui::hide() {
    
    ofxGwen::hide();
    //ofHideCursor();
}

void ofxOctaniumGui::loadSettings(string filename) {
    load(filename);
}

void ofxOctaniumGui::loadSettings() {
    
    ofFileDialogResult dialogResult = ofSystemLoadDialog("", false, ofToDataPath("", true));
    if(dialogResult.bSuccess) {
        load(dialogResult.filePath);
    }
}

void ofxOctaniumGui::saveSettings(){
    
    if(currSettingsFilePath == "") {
        ofLog() << "Could not specify filename for xml. Use \"Save as\" or load a file another first";
    }
    save(currSettingsFilePath);
}

void ofxOctaniumGui::saveSettingsAs(){
    
    ofFileDialogResult dialogResult = ofSystemSaveDialog("", "Save file as..");
    if(dialogResult.bSuccess) {
        save(dialogResult.filePath);
    }
}

void ofxOctaniumGui::save(string filename) {
    
    while(settingsXML.getPushLevel()) settingsXML.popTag();
    settingsXML.clear();
    settingsXML.addTag("settings");
    settingsXML.pushTag("settings");
    vector<BaseComponent*> comps = appGui->getSettingsWindow()->getComponents();
    int currTag;
    for(int i=0; i<comps.size(); i++) {
        settingsXML.addValue( getComponentId( comps[i]->getName() ), comps[i]->getValue() );
    }
    
    if (settingsXML.saveFile(filename))
        ofLog() << "Settings saved as";
}

char* ofxOctaniumGui::getComponentId(string label) {
    
    char *cstr = new char[label.length() + 1];
    strcpy(cstr, label.c_str());
    int size = strlen(cstr);
    std::replace(&cstr[0], &cstr[size], ' ', '_');
    return cstr;
}

void ofxOctaniumGui::resetSettings(){
    
    load("default.xml");
}

void ofxOctaniumGui::load(string xmlPath) {
    
    currSettingsFilePath = xmlPath;
    
    if (settingsXML.loadFile(xmlPath)) {
        
        settingsXML.pushTag("settings");
        vector<BaseComponent*> comps = appGui->getSettingsWindow()->getComponents();
        int currTag;
        for(int i=0; i<comps.size(); i++) {
            float val = settingsXML.getValue( getComponentId( comps[i]->getName() ), 0.0f );
            comps[i]->setFloatValue( val );
        }
        
        ofLog() << "Settings loaded";
    }
}

void ofxOctaniumGui::addSlider(string name, float& prop, float minValue, float maxValue)
{
    if(!appGui->getMenu()->i_settings) {
        addWindowMenuItem(MENU_ITEM_SETTINGS);
    }
    appGui->getSettingsWindow()->addSlider(name, prop, minValue, maxValue);
}

void ofxOctaniumGui::addCheckbox(string name, bool& prop)
{
    if(!appGui->getMenu()->i_settings) {
        addWindowMenuItem(MENU_ITEM_SETTINGS);
    }
    appGui->getSettingsWindow()->addCheckbox(name, prop);
}

Gwen::Skin::Base* ofxOctaniumGui::createSkin(Gwen::Renderer::OpenGL *renderer, const string& default_font, const string& skin_texture_path)
{
    this->skin_texture_path = skin_texture_path;
        
	Gwen::Skin::TexturedBase *skin = new CustomSkin(renderer);
	skin->Init(skin_texture_path);
	skin->SetDefaultFont(Gwen::Utility::StringToUnicode(default_font), 9);
	
	skin->SetRender(renderer);
	return skin;
}

void ofxOctaniumGui::keyPressed(ofKeyEventArgs& args) {
    
    switch (args.key) {
        case 'f': {
            if(ofGetWindowMode() == OF_FULLSCREEN) {
                ofSetFullscreen(false);
                show();
            } else {
                ofSetFullscreen(true);
                hide();
            }
        } break;
            
        case '\t': {
            
            ofResizeEventArgs e;
            e.width = ofGetWidth();
            e.height = ofGetHeight();
            ofxGwen::windowResized(e);
            
            toggleView();
        } break;
            
        case 'r':
            reloadSkin();
            break;
            
        default:
            break;
    }
}
