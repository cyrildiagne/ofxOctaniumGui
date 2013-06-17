//
//  SettingsWindow.cpp
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#include "SettingsWindow.h"

#include "octanium/gui/components/Slider.h"
#include "octanium/gui/components/Checkbox.h"

using namespace octanium::gui;
using namespace Gwen;

GWEN_CONTROL_CONSTRUCTOR( SettingsWindow )
{
    SetTitle( Utility::Format( L"Settings" ) );
    
    delegate = NULL;
    
    SetSize(310, 300);
    SetPos(50, 50);
    SetPadding(5);
    SetMinimumSize(Gwen::Point(310, 110));
    SetMaximumSize(Gwen::Point(310, 200));
    
    bts = new Controls::Base(this);
    bts->SetSize(300, 30);
    bts->SetShouldDrawBackground(true);
    bts->Dock(Pos::Bottom);
    bts->SetPadding( Padding(0, 8, 0, 2) );
    
    int btW = 66;
    
    btLoad = new Controls::Button(bts);
    btLoad->SetSize(btW, 20);
    btLoad->SetText("Load");
    btLoad->Dock(Pos::Left);
    btLoad->onPress.Add(this, &ThisClass::btClicked);
    
    btSave = new Controls::Button(bts);
    btSave->SetPos(btLoad->Width() + 20, 0);
    btSave->SetSize(btW, 20);
    btSave->SetText("Save");
    btSave->SetMargin(4);
    btSave->Dock(Pos::Left);
    btSave->onPress.Add(this, &ThisClass::btClicked);
    
    btSaveAs = new Controls::Button(bts);
    btSaveAs->SetPos(btLoad->Width() + 20, 0);
    btSaveAs->SetSize(btW, 20);
    btSaveAs->SetText("Save as..");
    btSaveAs->SetMargin(4);
    btSaveAs->Dock(Pos::Left);
    btSaveAs->onPress.Add(this, &ThisClass::btClicked);
    
    btReset = new Controls::Button(bts);
    btReset->SetPos(btLoad->Width() + 20, 0);
    btReset->SetSize(btW, 20);
    btReset->SetText("Reset");
    btReset->SetMargin(4);
    btReset->Dock(Pos::Left);
    btReset->onPress.Add(this, &ThisClass::btClicked);
    
    scroll = new Controls::ScrollControl(this);
    scroll->Dock(Pos::Fill);
    scroll->SetScroll(false, true);
    scroll->SetAutoHideBars(true);
    
    prev = NULL;
}

void SettingsWindow::btClicked(Controls::Base* bt)
{
    if(!delegate) return;
    
    if(bt==btLoad) {
        delegate->loadSettings();
    }
    else if(bt==btSave) {
        delegate->saveSettings();
    }
    else if(bt==btSaveAs) {
        delegate->saveSettingsAs();
    }
    else if(bt==btReset) {
        delegate->resetSettings();
    }
}

void SettingsWindow::addSlider(string name, float& prop, float minValue, float maxValue)
{
    Slider* slider = new Slider(scroll);
    slider->setup(name, prop, minValue, maxValue);
    
    if(prev) {
        Gwen::Align::PlaceBelow(slider, prev);
    }
    
    prev = slider;
    
    int h = min(Height() + slider->Height(), 500);
    
    SetMaximumSize(Gwen::Point(310, bts->Height() + 40 + slider->Bottom()));
    
    components.push_back(slider);
}

void SettingsWindow::addCheckbox(string name, bool& prop)
{
    Checkbox* checkbox = new Checkbox(scroll);
    checkbox->setup(name, prop);
    
    if(prev) {
        Gwen::Align::PlaceBelow(checkbox, prev);
    }
    
    prev = checkbox;
    
    int h = min(Height() + checkbox->Height(), 500);
    
    SetMaximumSize(Gwen::Point(310, bts->Height() + 40 + checkbox->Bottom()));
    
    components.push_back(checkbox);
}