#include <iostream>
#include <thread>
#include <string>
#include "tinyxml2.h"
#include "Authenticator/Authenticator.h"
#include "App/App.h"
#include "UI/UI.h"
#include "PassKeeper/PassKeeper.h"
using namespace std;
int main() {

    // Create the Pass Keeper Application
    PassKeeper PassKeeper;

    // Create the UI Com Frame work
    App AppCenter;
    UI UIHandler;

    // Create the Pass Keeper Application -> Components
    Authenticator AuthHandler(2,PassKeeper);

    AppCenter.SetPassKeeper(&PassKeeper);
    AppCenter.SetUI(&UIHandler);
    UIHandler.SetApp(&AppCenter);
    
    std::thread UIthread(&UI::UI_task,&UIHandler);
    std::thread Appthread(&App::App_task,&AppCenter);

    // Wait for threads to finish
    UIthread.join();
    Appthread.join();

    std::cout << "Authentication is " << std::endl;
    return 0;
}
