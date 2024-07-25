#include "AppCenter.h"
#include <iostream>

#include "../PassKeeper/PassKeeper.h"
#include "../UI/UI.h"


AppCenter::AppCenter() : PtrToPassKeeperAppObj(nullptr), PtrToUIObj(nullptr) 
{

}
AppCenter::~AppCenter()
{
    
}

/*
*   @brief: AppCenter to send the msg to UI 
*   @param[in]: _msg  string response msg to UI
*   @return none
*/
void AppCenter::AppCenter_send_msg(const string& _msg)
{
    if (PtrToUIObj)
    {
        #ifdef DEBUG
        cout<< "[AppCenter Task] AppCenter Sends msg " << _msg << " to UI "  << endl;
        #endif
        PtrToUIObj->UI_Receive_MSG(_msg);
    }
    else
    {
        #ifdef DEBUG
        cout<< "[AppCenter Task] Panic UI Comp is not hooked " << endl;
        #endif
    }
}

void AppCenter::SetPassKeeper(PassKeeper* _ptrToPassKeeperAppObj)
{
    this->PtrToPassKeeperAppObj = _ptrToPassKeeperAppObj;
}
void AppCenter::SetUI(UI* _ptrToUIObj)
{
    this->PtrToUIObj = _ptrToUIObj;
}

/*
*   @brief: AppCenter Task function polls waits to receive a message
*            from the UI to prefrom processing
*/
void AppCenter::App_task()
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[this]{ return !messageQueue.empty();});

        while(!messageQueue.empty())
        {
            string msg = messageQueue.front(); // Get the first message
            messageQueue.pop(); // remove it from the Queue
            lock.unlock(); // Unlock the mutex to allow other threads to access the queue

            #ifdef DEBUG
            cout<< "[AppCenter Task] Processing the MSG : " << msg << endl;
            #endif
            
            string response = "Application Error ";
            if (PtrToPassKeeperAppObj)
            {
                PtrToPassKeeperAppObj->AppCenter_FW_msg_To_PassKeeper(msg,response);
            }

            this->AppCenter_send_msg(response);
            lock.lock(); // Re-lock the mutex before the next iteration
        }
    }
}

/*
*   @brief: to be called by UI component so AppCenter receives the msg
*   @param[in]: _msg  string message from UI
*   @return none
*/
void AppCenter::Receive_Msg(const string& msg)
{
    #ifdef DEBUG
    cout<< "[Poll_Input_task] MSG placed in AppCenter MSG Queue " << endl;
    #endif
    lock_guard<mutex> lock(mtx); // Lock the mutex
    messageQueue.push(msg); // Add the message to the queue
    cv.notify_one(); // Notify one waiting thread
}
