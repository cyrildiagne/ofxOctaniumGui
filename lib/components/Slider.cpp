//
//  Slider.cpp
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#include "Slider.h"

using namespace octanium::gui;
using namespace Gwen;

GWEN_CONTROL_CONSTRUCTOR( Slider )
{
    SetSize( 300, 38 );
    SetPos( Pos::Center );
    
    label = new Controls::Label(this);
    label->SetPos(10, 10);
    label->SetFont(label->GetFont()->facename, 7, false);
    
    input = new NumericUpDownFloat(this);
    input->onChanged.Add( this, &Slider::inputChanged );
    input->SetSize(80, 20);
    input->SetPos(200, 4);
    input->SetTextColor(GetSkin()->Colors.Label.Bright);
    input->SetFont(input->GetFont()->facename, 7, false);
    
    slider = new Controls::HorizontalSlider(this);
    slider->onValueChanged.Add( this, &Slider::sliderMoved );
    slider->SetSize(280, 20);
    slider->SetPos(4, 21);
    
    bSilentEvents = false;
}

void Slider::setup(std::string labelText, float& value, float minFloat, float maxFloat) {
    
    _minFloat = minFloat;
    _maxFloat = maxFloat;
    _value = &value;
    
    slider->SetRange(minFloat, maxFloat);
    slider->SetFloatValue(value);
    
    input->SetMin(minFloat);
    input->SetMax(maxFloat);
    input->SetValue(value);
    
    label->SetText(labelText);
}

void Slider::sliderMoved( Base* pControl )
{
    if(bSilentEvents) return;
    
    bSilentEvents = true;
    {
        *_value = slider->GetFloatValue();
        input->SetValue(*_value);
    }
    bSilentEvents = false;
}

void Slider::inputChanged( Base* pControl )
{
    if(bSilentEvents) return;
    
    bSilentEvents = true;
    {
        *_value = input->GetFloatFromText();
        slider->SetFloatValue(*_value);
    }
    bSilentEvents = false;
}