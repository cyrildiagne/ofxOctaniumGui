//
//  Menu.h
//  guitar_test1
//
//  Created by kikko on 3/14/13.
//
//

#ifndef __guitar_test1__Menu__
#define __guitar_test1__Menu__


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
            
            Gwen::Controls::MenuItem *m_app, *m_file, *m_window;
            Gwen::Controls::MenuItem *i_about;
            Gwen::Controls::MenuItem *i_new, *i_load, *i_save, *i_save_as;
            Gwen::Controls::MenuItem *i_logs, *i_settings, *i_help;
            
            void fileItemSelected( Base* pControl );
            void windowItemSelected( Base* pControl );
            
            void addAppMenu();
            
        private:
        };
        
    }
}

#endif /* defined(__guitar_test1__Menu__) */
