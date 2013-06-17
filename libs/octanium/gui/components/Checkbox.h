//
//  Checkbox.h
//  guitar_test2
//
//  Created by kikko on 3/19/13.
//
//

#ifndef __guitar_test2__Checkbox__
#define __guitar_test2__Checkbox__

#include "Gwen/Gwen.h"
#include "Gwen/Align.h"
#include "Gwen/Utility.h"
#include "Gwen/Controls.h"

#include "octanium/gui/Types.h"


namespace octanium {
    
    namespace gui {
        
        class Checkbox : public BaseComponent {
            
        public:
            
            GWEN_CONTROL(Checkbox, Gwen::Controls::Base);
            
            virtual ~Checkbox() {};
            
            void setup(std::string labelText, bool& value);
            
            bool getBoolValue() { return *_value; }
            void setBoolValue(bool val);
            std::string getName() { return std::string(m_Label->GetText().c_str()); }
            
        private:
            
            void checkboxChanged( Base* pControl );
            
            Gwen::Controls::CheckBox*		m_Checkbox;
            Gwen::Controls::LabelClickable*	m_Label;
            
            bool* _value;
            
            bool bSilentEvents;
        };
    }
}

#endif /* defined(__guitar_test2__Checkbox__) */
