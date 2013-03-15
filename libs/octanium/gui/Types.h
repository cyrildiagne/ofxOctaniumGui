//
//  Types.h
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#ifndef guitar_test1_Types_h
#define guitar_test1_Types_h

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

namespace octanium {
    
    namespace gui {

        enum MenuType {
            MENU_APP,
            MENU_FILE,
            MENU_WINDOW
        };

        enum MenuItemType {
            MENU_ITEM_NEW,
            MENU_ITEM_LOAD,
            MENU_ITEM_SAVE,
            MENU_ITEM_SAVE_AS,
            MENU_ITEM_ABOUT,
            MENU_ITEM_LOGS,
            MENU_ITEM_SETTINGS
        };

        enum DefaultWindowType {
            WINDOW_LOG,
            WINDOW_SETTINGS,
            WINDOW_ABOUT
        };
        
        class IComponent {
        public:
            virtual ~IComponent(){};
            virtual float getValue() = 0;
            virtual void setFloatValue(float val) = 0;
            virtual std::string getName() = 0;
        };
        
        
        class BaseComponent : public Gwen::Controls::Base, public IComponent {
        public:
            GWEN_CONTROL( BaseComponent, Gwen::Controls::Base):Gwen::Controls::Base( pParent, pName ){};
            virtual ~BaseComponent() {}
            virtual float getValue() {}
            virtual void setFloatValue(float val) {}
            virtual std::string getName() {}
        };
    }
}

#endif
