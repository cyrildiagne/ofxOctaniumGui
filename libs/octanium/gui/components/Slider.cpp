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

Slider::Slider( Gwen::Controls::Base* pParent, const Gwen::String& pName ) : BaseComponent( pParent, pName )
//GWEN_CONTROL_CONSTRUCTOR( Slider )
{
    SetSize( 300, 38 );
    
    label = new Controls::Label(this);
    label->SetPos(0, 10);
    label->SetFont(label->GetFont()->facename, 7, false);
    
    input = new NumericUpDownFloat(this);
    input->onChanged.Add( this, &Slider::inputChanged );
    input->SetSize(80, 20);
    input->SetPos(190, 4);
    input->SetTextColor(GetSkin()->Colors.Label.Bright);
    input->SetFont(input->GetFont()->facename, 7, false);
    
    slider = new Controls::HorizontalSlider(this);
    slider->onValueChanged.Add( this, &Slider::sliderMoved );
    slider->SetSize(284, 20);
    slider->SetPos(-6, 21);
    
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

void Slider::setFloatValue(float val)
{
    bSilentEvents = true;
    {
        *_value = val;
        slider->SetFloatValue(val);
        input->SetValue(val);
    }
    bSilentEvents = false;
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