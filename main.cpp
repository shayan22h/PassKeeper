#include <iostream>
#include <thread>
#include <string>
#include "tinyxml2.h"
#include "AppCenter/AppCenter.h"
#include "UI/UI.h"
#include "PassKeeper/PassKeeper.h"
#include "PassKeeper/Authenticator/Authenticator.h"
using namespace std;
int main() {

    // Create the Pass Keeper Application
    PassKeeper PassKeeper;

    // Create the UI Com Frame work
    AppCenter AppCenter;
    UI UIHandler;

    // Create the Pass Keeper Application -> Components
    Authenticator AuthHandler(2,PassKeeper);

    AppCenter.SetPassKeeper(&PassKeeper);
    AppCenter.SetUI(&UIHandler);
    UIHandler.SetApp(&AppCenter);
    
    std::thread UIthread(&UI::UI_task,&UIHandler);
    std::thread Appthread(&AppCenter::App_task,&AppCenter);

    // Wait for threads to finish
    UIthread.join();
    Appthread.join();

    std::cout << "Authentication is " << std::endl;
    return 0;
}
