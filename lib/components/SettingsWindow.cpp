//
//  SettingsWindow.cpp
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#include "SettingsWindow.h"

using namespace octanium::gui;
using namespace Gwen;

GWEN_CONTROL_CONSTRUCTOR( SettingsWindow )
{
    SetTitle( Utility::Format( L"Settings" ) );
    
    SetSize(300, 40);
    SetPos(200, 200);
    
    prev = NULL;
}

void SettingsWindow::addSlider(string name, float& prop, float minValue, float maxValue) {
    
    Slider* slider = new Slider(this);
    slider->setup(name, prop, minValue, maxValue);
    slider->Dock(Pos::Top);
    
    if(prev) {
        Gwen::Align::PlaceBelow(slider, prev);
    }
    
    prev = slider;
    
    SetSize(Width(), Height() + slider->Height());
    
    components.push_back(slider);
}