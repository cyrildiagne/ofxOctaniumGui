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

#include "Slider.h"

using namespace std;

namespace octanium {
    
    namespace gui {
        
        class SettingsWindow : public Gwen::Controls::WindowControl {
            
        public:
            
            GWEN_CONTROL( SettingsWindow, Gwen::Controls::WindowControl );
            
            void addSlider(string name, float& prop, float minValue, float maxValue);
            
        private:
            
            vector<Gwen::Controls::Base*> components;
            Gwen::Controls::Base* prev;
        };
        
    }
}


#endif /* defined(__guitar_test1__SettingsWindow__) */
