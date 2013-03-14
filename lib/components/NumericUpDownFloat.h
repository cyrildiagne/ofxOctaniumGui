//
//  NumericUpDownFloat.h
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#ifndef __guitar_test1__NumericUpDownFloat__
#define __guitar_test1__NumericUpDownFloat__

#include "Gwen/Gwen.h"
#include "Gwen/Controls/NumericUpDown.h"

namespace octanium {
    namespace gui {
        
        class NumericUpDownFloat : public Gwen::Controls::TextBoxNumeric {
            
        public:
            
            GWEN_CONTROL( NumericUpDownFloat, TextBoxNumeric );
            
            virtual void SetMin( float i );
            virtual void SetMax( float i );
            virtual void SetValue( float i );
            
            Gwen::Event::Caller	onChanged;
            
        private:
            
            virtual void OnEnter();
            virtual void OnChange();
            virtual void OnTextChanged();
            
            virtual void OnButtonUp( Base* control );
            virtual void OnButtonDown( Base* control );
            
            virtual bool OnKeyUp( bool bDown )	{	if ( bDown ) OnButtonUp( NULL ); return true;   }
            virtual bool OnKeyDown( bool bDown ){	if ( bDown ) OnButtonDown( NULL ); return true; }
            
            virtual void SyncTextFromNumber();
            virtual void SyncNumberFromText();
            
            virtual void CalcIncrement();
            
            float m_iNumber;
            float m_iMax;
            float m_iMin;
        
            float m_inc;
        };
        
    }
}



#endif /* defined(__guitar_test1__NumericUpDownFloat__) */
