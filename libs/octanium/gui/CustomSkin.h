//
//  CustomSkin.h
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#ifndef __guitar_test1__CustomSkin__
#define __guitar_test1__CustomSkin__

#include "Gwen/Skins/TexturedBase.h"

namespace octanium {
    namespace gui {
        
        class CustomSkin : public Gwen::Skin::TexturedBase {
            
        public:
            CustomSkin( Gwen::Renderer::Base* renderer ) : Gwen::Skin::TexturedBase( renderer ){}
            
            virtual void DrawSlider( Gwen::Controls::Base* control, bool bIsHorizontal, int numNotches, int barSize )
            {
                if ( bIsHorizontal )
                {
                    Gwen::Rect rect = control->GetRenderBounds();
                    rect.x += barSize*0.5;
                    rect.w -= barSize;
                    rect.y += rect.h*0.5-1;
                    rect.h = 2;
                    GetRender()->SetDrawColor( Gwen::Color( 0, 0, 0, 100 ) );
                    DrawSliderNotchesH( rect, numNotches, barSize * 0.5 );
                    GetRender()->DrawFilledRect( rect );
                    
                    Gwen::Rect shadow = rect;
                    shadow.y += 2;
                    shadow.h = 1;
                    GetRender()->SetDrawColor( Gwen::Color( 255, 255, 255, 15 ) );
                    return GetRender()->DrawFilledRect( shadow );
                    
                }
                
                Gwen::Rect rect = control->GetRenderBounds();
                rect.y += barSize*0.5;
                rect.h -= barSize;
                rect.x += rect.w*0.5-1;
                rect.w = 2;
                GetRender()->SetDrawColor( Gwen::Color( 0, 0, 0, 100 ) );
                DrawSliderNotchesV( rect, numNotches, barSize * 0.4 );
                GetRender()->DrawFilledRect( rect );
                
                Gwen::Rect shadow = rect;
                shadow.x+=1;
                GetRender()->SetDrawColor( Gwen::Color( 255, 255, 255, 100 ) );
                return GetRender()->DrawFilledRect( shadow );
            }
        };
    }
}

#endif /* defined(__guitar_test1__CustomSkin__) */
