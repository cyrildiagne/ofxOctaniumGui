//
//  Types.h
//  guitar_test1
//
//  Created by kikko on 3/13/13.
//
//

#ifndef guitar_test1_Types_h
#define guitar_test1_Types_h


namespace octanium {
    
    namespace gui {

        enum MenuType {
            MENU_FILE = 0,
            MENU_WINDOW = 1
        };

        enum MenuItemType {
            MENU_ITEM_NEW,
            MENU_ITEM_LOAD,
            MENU_ITEM_SAVE,
            MENU_ITEM_SAVE_AS,
            MENU_ITEM_LOGS,
            MENU_ITEM_SETTINGS
        };

        enum DefaultWindowType {
            WINDOW_LOG,
            WINDOW_SETTINGS
        };
        
    }
}

#endif
