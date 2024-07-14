#include <iostream>
#include <thread>
#include <string>
#include "tinyxml2.h"
#include "Authenticator/Authenticator.h"
#include "App/App.h"
#include "UI/UI.h"
using namespace std;
int main() {
    Authenticator AuthHandler(2);
    App ApplicationHandler;
    UI UIHandler(ApplicationHandler);

    std::thread UIthread(&UI::UI_task,&UIHandler);
    std::thread Appthread(&App::App_task,&ApplicationHandler);

    // Wait for threads to finish
    UIthread.join();
    Appthread.join();

    std::cout << "Authentication is " << std::endl;
    return 0;
}
