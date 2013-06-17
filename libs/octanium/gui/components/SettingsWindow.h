//
//  SettingsWindow.h
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#ifndef __guitar_test1__SettingsWindow__
#define __guitar_test1__SettingsWindow__

#include <iostream>
#include "Gwen/Gwen.h"
#include "Gwen/Align.h"
#include "Gwen/Utility.h"
#include "Gwen/Controls.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/ScrollControl.h"

#include "octanium/gui/Types.h"

using namespace std;

namespace octanium {
    
    namespace gui {
        
        class SettingsWindowDelegate {
            
        public:
            
            //SettingsWindowDelegate(){}
            virtual ~SettingsWindowDelegate(){}
            
            virtual void loadSettings(){};
            virtual void saveSettings(){};
            virtual void saveSettingsAs(){};
            virtual void resetSettings(){};
        };
        
        
        class SettingsWindow : public Gwen::Controls::WindowControl {
            
        public:
            
            GWEN_CONTROL( SettingsWindow, Gwen::Controls::WindowControl );
            
            void addSlider(string name, float& prop, float minValue, float maxValue);
            void addCheckbox(string name, bool& prop);
            
            void setDelegate(SettingsWindowDelegate* delegate) { this->delegate = delegate; }
            
            void btClicked(Gwen::Controls::Base* bt);
            
            const vector<BaseComponent*>& getComponents() { return components; }
            
        private:
            
            vector<BaseComponent*> components;
            Gwen::Controls::Base* prev;
            
            Gwen::Controls::ScrollControl* scroll;
            
            Gwen::Controls::Base* bts;
            Gwen::Controls::Button* btSave;
            Gwen::Controls::Button* btSaveAs;
            Gwen::Controls::Button* btLoad;
            Gwen::Controls::Button* btReset;
            
            SettingsWindowDelegate* delegate;
        };
        
    }
}


#endif /* defined(__guitar_test1__SettingsWindow__) */
