#include "UI.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../AppCenter/AppCenter.h"

UI::UI() : PtrToAppObj(nullptr)
{

}

UI::~UI()
{

}

/*
*   @brief: Independent task polls every 100ms for a msg from user
            and then send the msg to AppCenter Comp
*/
void UI::Poll_Input_task(void)
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string stringInput;
        std::getline(std::cin, stringInput);
        if(!stringInput.empty())
        {
            UI_send_msg(stringInput);
        }
    }
}

/*
*   @brief: UI to send the msg to AppCenter 
*   @param[in]: _msg  string  msg to AppCenter
*   @return none
*/
void UI::UI_send_msg(const std::string& _msg)
{

    if (PtrToAppObj)
    {
        #ifdef DEBUG
        cout<< "[Poll_Input_task] UI Sends msg "<< _msg  << "to AppCenter " << endl;
        #endif
        PtrToAppObj->Receive_Msg(_msg);
    }
    else
    {
        #ifdef DEBUG
        cout<< "[Poll_Input_task] Panic AppCenter Comp is not hooked " << endl;
        #endif
    } 
}

/*
*   @brief: UI task creates an indenpendent task for UI receives msg from user
*           and then waits on receiving messages from AppCenter Component
*/
void UI::UI_task(void)
{
    std::thread InputThreadObj(&UI::Poll_Input_task,this);
    InputThreadObj.detach();
    while(true)
    {
        // Waiting for Reply from Application
        unique_lock<mutex> lock(ui_mtx);
        ui_cv.wait(lock, [this]{return !ui_messageQueue.empty();});
        while(!ui_messageQueue.empty())
        {
            string msg = ui_messageQueue.front();
            ui_messageQueue.pop();
            lock.unlock();
            #ifdef DEBUG
            cout<< "[UI TASK] MSG Received from AppCenter : " << msg << endl;
            #endif
            cout<< " Response From AppCenter : " << msg << endl;
            lock.lock();
        }
    }
}

void UI::SetApp(AppCenter* _ptrToAppObj)
{
    this->PtrToAppObj = _ptrToAppObj;
}

/*
*   @brief: to be called by AppCenter component so UI receives the msg
*   @param[in]: _msg  string message from AppCenter
*   @return none
*/
void UI::UI_Receive_MSG(const string& msg)
{
    #ifdef DEBUG
    cout<< "[AppCenter TASK] MSG placed in UI MSG Queue " << endl;
    #endif
    lock_guard<mutex> lock(ui_mtx);
    ui_messageQueue.push(msg);
    ui_cv.notify_one();
}