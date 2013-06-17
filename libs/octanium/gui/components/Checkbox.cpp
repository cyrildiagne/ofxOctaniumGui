//
//  Checkbox.cpp
//  guitar_test2
//
//  Created by kikko on 3/19/13.
//
//

#include "Checkbox.h"

using namespace octanium::gui;
using namespace Gwen;

Checkbox::Checkbox( Gwen::Controls::Base* pParent, const Gwen::String& pName ) : BaseComponent( pParent, pName )
//GWEN_CONTROL_CONSTRUCTOR( Checkbox )
{
    SetSize( 300, 19 );
    SetMargin(Margin(0, 5, 0, 4));
    
    m_Checkbox = new Controls::CheckBox( this );
    m_Checkbox->Dock( Pos::Left );
    m_Checkbox->SetMargin( Margin( 0, 2, 2, 2 ) );
    m_Checkbox->SetTabable( false );
    m_Checkbox->onCheckChanged.Add( this, &Checkbox::checkboxChanged );
    
    m_Label = new Controls::LabelClickable( this );
    m_Label->Dock( Pos::Fill );
    m_Label->onPress.Add( m_Checkbox, &Controls::CheckBox::OnPress );
    m_Label->SetTabable( false );
    m_Label->SetFont(m_Label->GetFont()->facename, 7, false);
    
    SetTabable( false );
    
    bSilentEvents = false;
}

void Checkbox::setup(std::string labelText, bool& value) {
    
    _value = &value;
    
    m_Checkbox->SetChecked(value);
    
    m_Label->SetText(labelText);
}

void Checkbox::checkboxChanged( Base* pControl )
{
    *_value = ((Controls::CheckBox*)pControl)->IsChecked();
}

void Checkbox::setBoolValue(bool val)
{
    *_value = val;
    
    bSilentEvents = true;
    {
        m_Checkbox->SetChecked(val);
    }
}