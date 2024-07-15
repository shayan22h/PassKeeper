#include "UI.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../App/App.h"

UI::UI() : PtrToAppObj(nullptr)
{
    // constructor
}

UI::~UI()
{
    //constructor
}

void UI::SetApp(App* _ptrToAppObj)
{
    this->PtrToAppObj = _ptrToAppObj;
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

    if (PtrToAppObj)
    {
        std::cout << "Sending  " << _str << " to Application" << std::endl;
        PtrToAppObj->Receive_Msg(_str);
    }
    else
    {
        std::cout << "No App Interface for UI Component " << std::endl;
    }
    
}