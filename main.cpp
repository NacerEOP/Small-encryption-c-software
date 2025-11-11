#include <iostream>
#include "Interface/interface.h"



int main(){
    HINSTANCE hInstance = GetModuleHandle(nullptr); // handle to current module
    InterfaceApp app(hInstance);
    return app.run(SW_SHOWDEFAULT);
    
}