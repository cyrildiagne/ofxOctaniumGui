//
//  NumericUpDownFloat.cpp
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#include "NumericUpDownFloat.h"

using namespace Gwen;
using namespace octanium::gui;

GWEN_CONTROL_CONSTRUCTOR( NumericUpDownFloat )
{
	SetSize( 100, 20 );
    
    Gwen::Controls::Base* pSplitter = new Gwen::Controls::Base( this );
    pSplitter->Dock( Pos::Right );
    pSplitter->SetWidth( 13 );
    
    Gwen::Controls::NumericUpDownButton_Up* pButtonUp = new Gwen::Controls::NumericUpDownButton_Up( pSplitter );
    pButtonUp->onPress.Add( this, &NumericUpDownFloat::OnButtonUp );
    pButtonUp->SetTabable( false );
    pButtonUp->Dock( Pos::Top );
    pButtonUp->SetHeight( 7 );
    
	Gwen::Controls::NumericUpDownButton_Down* pButtonDown = new Gwen::Controls::NumericUpDownButton_Down( pSplitter );
    pButtonDown->onPress.Add( this, &NumericUpDownFloat::OnButtonDown );
    pButtonDown->SetTabable( false );
    pButtonDown->Dock( Pos::Fill );
    pButtonUp->SetPadding( Padding( 0, 1, 1, 0 ) );
    
	m_iMax = 100.0;
	m_iMin = 0.0;
	m_iNumber = 0.0;
    m_inc = 1.0;
	SetText( "0.00" );
}

void NumericUpDownFloat::OnButtonUp( Base* /*control*/ )
{
	SyncNumberFromText();
	SetValue( m_iNumber + m_inc );
}

void NumericUpDownFloat::OnButtonDown( Base* /*control*/ )
{
	SyncNumberFromText();
	SetValue( m_iNumber - m_inc );
}


void NumericUpDownFloat::SyncTextFromNumber()
{
	SetText( Utility::ToString( m_iNumber ) );
}

void NumericUpDownFloat::SyncNumberFromText()
{
	SetValue( GetFloatFromText() );
}

void NumericUpDownFloat::SetMin( float i )
{
	m_iMin = i;
}

void NumericUpDownFloat::SetMax( float i )
{
	m_iMax = i;
}

void NumericUpDownFloat::CalcIncrement()
{
    m_inc = fabs(m_iMax-m_iMin) / 100;
}

void NumericUpDownFloat::SetValue( float i )
{
	if ( i > m_iMax ) i = m_iMax;
	if ( i < m_iMin ) i = m_iMin;
    
	if ( m_iNumber == i )
	{
		return;
	}
    
	m_iNumber = i;
    
	// Don't update the text if we're typing in it..
	// Undone - any reason why not?
	//if ( !HasFocus() )
	{
		SyncTextFromNumber();
	}
    
	OnChange();
}

void NumericUpDownFloat::OnChange()
{
	onChanged.Call( this );
}

void NumericUpDownFloat::OnTextChanged()
{
	BaseClass::OnTextChanged();
    
	SyncNumberFromText();
}

void NumericUpDownFloat::OnEnter()
{
	SyncNumberFromText();
	SyncTextFromNumber();
    
	BaseClass::OnEnter();
}