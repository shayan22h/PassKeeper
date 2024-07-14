#include "UI.h"
#include <iostream>
#include <thread>
#include <chrono>

UI::UI(App& _application):application(_application)
{
    // constructor
}

UI::~UI()
{
    //constructor
}
void UI::UI_task(void)
{
    std::thread InputThreadObj(&UI::Poll_Input_task,this);
    InputThreadObj.detach();
    std::cout << " UI Task" << std::endl;
    while(true)
    {

    }
}

void UI::Poll_Input_task(void)
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::string stringInput;
        std::getline(std::cin, stringInput);
        if(!stringInput.empty())
        {
            UI_Send_MsgToApp(stringInput);
        }
    }
}
void UI::UI_Send_MsgToApp(const std::string& _str)
{
    // Print the string is 
    std::cout << "Sending  " << _str << " to Application" << std::endl;
    application.Receive_Msg(_str);
}