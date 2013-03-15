//
//  AppGuiBase.h
//  example
//
//  Created by kikko on 3/12/13.
//
//

#ifndef __example__AppGuiBase__
#define __example__AppGuiBase__

#include "Gwen/Gwen.h"
#include "Gwen/Align.h"
#include "Gwen/Utility.h"
#include "Gwen/Controls.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/StatusBar.h"

#include "octanium/gui/Types.h"
#include "octanium/gui/Delegates.h"
#include "octanium/gui/components/LogWindow.h"
#include "octanium/gui/components/SettingsWindow.h"
#include "octanium/gui/components/Menu.h"

using namespace std;

namespace octanium {
    
    namespace gui {
        
        class AboutWindow : public Gwen::Controls::WindowControl {
            
        public:
            
            GWEN_CONTROL( AboutWindow, Gwen::Controls::WindowControl );
            
            Gwen::Controls::Label*	m_Text;
        };
        
        
        class AppGuiBase : public Gwen::Controls::Base, octanium::gui::WindowMenuDelegate {
            
        public:
            
            GWEN_CONTROL( AppGuiBase, Gwen::Controls::Base );
            
            void Render( Gwen::Skin::Base* skin );
            
            void addLogsWindowMenu();
            
            // WindowMenuDelegate
            void openWindow(int windowType);
            
            Menu* getMenu() { return menu; }
            
            LogWindow* getLogWindow() { return logWindow; }
            SettingsWindow* getSettingsWindow() { return settingsWindow; }
            
        private:
            
            LogWindow*                  logWindow;
            SettingsWindow*             settingsWindow;
            
            Menu*                       menu;
            
            Gwen::Controls::MenuStrip*  m_MenuStrip;
            Gwen::Controls::StatusBar*	m_StatusBar;
            unsigned int				m_iFrames;
            float						m_fLastSecond;
            
            void initMenu();
            
        };
    }
}

#endif /* defined(__example__AppGuiBase__) */
