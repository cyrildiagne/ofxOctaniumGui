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
    
    logger = ofPtr<ofxOctaniumGuiLogger>(new ofxOctaniumGuiLogger());
    logger->setLogWindow(appGui->getLogWindow());
    
    ofLog::setChannel(logger);
    
    ofAddListener(ofEvents().keyPressed, this, &ofxOctaniumGui::keyPressed);
}

void ofxOctaniumGui::show() {
    
    ofxGwen::show();
    ofShowCursor();
}

void ofxOctaniumGui::hide() {
    
    ofxGwen::hide();
    ofHideCursor();
}

void ofxOctaniumGui::addSlider(string name, float& prop, float minValue, float maxValue) {
    
    if(!appGui->getMenu()->i_settings) {
        addWindowMenuItem(MENU_ITEM_SETTINGS);
    }
    appGui->getSettingsWindow()->addSlider(name, prop, minValue, maxValue);
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
            
        case 's': {
            
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
