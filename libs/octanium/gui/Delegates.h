//
//  Delegates.h
//  guitar_test1
//
//  Created by kikko on 3/12/13.
//
//

#ifndef guitar_test1_Delegates_h
#define guitar_test1_Delegates_h

namespace octanium {
    
    namespace gui {
        
        class FileMenuDelegate {
            
        public:
            
            FileMenuDelegate() {}
            virtual ~FileMenuDelegate() {}
            
            virtual void newFile() {}
            virtual void loadFile(std::string filename) {}
            virtual void saveFile(std::string filename) {}
        };
        
        class WindowMenuDelegate {
            
        public:
            
            WindowMenuDelegate() {}
            virtual ~WindowMenuDelegate() {}
            
            virtual void openWindow(int windowType) {}
        };
    }
}


#endif
