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

#include "Types.h"
#include "Delegates.h"
#include "LogWindow.h"
#include "SettingsWindow.h"

using namespace std;

#define APP_GUI_DELEGATE( ClassName )\
public: \
void add##ClassName(ClassName* delegate_) { v_##ClassName##s.push_back(delegate_); } \
vector<ClassName*> get##ClassName##s() { return v_##ClassName##s; } \
private: \
vector<ClassName*> v_##ClassName##s;

namespace octanium {
    
    namespace gui {
        
        class Menu : public Gwen::Controls::MenuStrip {
                        
            GWEN_CONTROL( Menu, Gwen::Controls::MenuStrip );
            
            // Delegates
            APP_GUI_DELEGATE( FileMenuDelegate );
            APP_GUI_DELEGATE( WindowMenuDelegate );
            
        public:
            
            void addItem(MenuType menu, int item, string label, string shortcut = "", string icon = "");
            Gwen::Controls::MenuItem * getMenu(MenuType);
            Gwen::Controls::MenuItem ** getMenuItemPtr(int type);
            
            Gwen::Controls::MenuItem *m_logo, *m_file, *m_window;
            Gwen::Controls::MenuItem *i_new, *i_load, *i_save, *i_save_as;
            Gwen::Controls::MenuItem *i_logs, *i_settings, *i_help;
            
            void menuItemSelected( Base* pControl );
            
            void aboutItemSelected( Base* pControl );
            void fileItemSelected( Base* pControl );
            void windowItemSelected( Base* pControl );
            
            void setAboutText(string text) { aboutText = text; }
            
        private:
            
            string aboutText;
        };
        
        
        
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
