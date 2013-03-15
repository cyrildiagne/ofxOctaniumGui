//
//  Slider.h
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#ifndef __guitar_test1__Slider__
#define __guitar_test1__Slider__

#include "Gwen/Gwen.h"
#include "Gwen/Align.h"
#include "Gwen/Utility.h"
#include "Gwen/Controls.h"

#include "octanium/gui/Types.h"
#include "octanium/gui/components/NumericUpDownFloat.h"


namespace octanium {
    
    namespace gui {
        
        class Slider : public BaseComponent {
        
        public:
            
            GWEN_CONTROL(Slider, Gwen::Controls::Base);
            
            void setup(std::string labelText, float& value, float minFloat, float maxFloat);
            
            virtual ~Slider() {};
            
            float getValue() { return *_value; }
            void setFloatValue(float val);
            std::string getName() { return std::string(label->GetText().c_str()); }
            
        private:
            
            void sliderMoved( Base* pControl );
            void inputChanged( Base* pControl );
            
            Gwen::Controls::HorizontalSlider* slider;
            Gwen::Controls::Label* label;
            NumericUpDownFloat* input;
            
            float _minFloat, _maxFloat;
            float* _value;
            
            bool bSilentEvents;
        };
    }
}

#endif /* defined(__guitar_test1__Slider__) */
