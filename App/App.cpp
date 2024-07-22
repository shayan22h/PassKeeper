#include "App.h"
#include <iostream>

#include "../UI/UI.h"

#define MAX_NO_OF_SUBSCRIBERS 5

App::App() : PtrToUIObj(nullptr)
{
    this->evenId_Cnt = 0;
    //TODO Change the Tbl Size
    for (uint8_t i = 0; i < 5;i++)
    {
        this->eventTabl[i].PtrToStr = nullptr;
        this->eventTabl[i].event_id = 0;
        this->eventTabl[i].callback = nullptr;
    }
}
App::~App()
{
    
}

/*
* @brief: processing even t
* @param[in]: _msg  string input message from UI
* @return none
*/
void App::process_event(const string& _msg)
{
    if (_msg == "exit")
    {
        exit(0);
    }
    uint8_t i = 0xFF;
    for (i = 0; i < MAX_NO_OF_SUBSCRIBERS; i++) 
    {
        if (eventTabl[i].PtrToStr && _msg == *(eventTabl[i].PtrToStr) && eventTabl[i].callback) 
        {
            // Execute the callback function associated with this event
            eventTabl[i].callback(_msg);
            #ifdef DEBUG
            cout<< "[App Task] Match found in processing event -> ID:  " << i << endl;
            #endif
            break;
        }
    }
    if (i == MAX_NO_OF_SUBSCRIBERS)
    {
        #ifdef DEBUG
        cout<< "[App Task] No Match found in Processing the MSG " << endl;
        #endif
    }
}
/*
*   @brief: App to send the msg to UI 
*   @param[in]: _msg  string response msg to UI
*   @return none
*/
void App::App_send_msg(const string& _msg)
{
    if (PtrToUIObj)
    {
        #ifdef DEBUG
        cout<< "[App Task] App Sends msg " << _msg << " to UI "  << endl;
        #endif
        PtrToUIObj->UI_Receive_MSG(_msg);
    }
    else
    {
        #ifdef DEBUG
        cout<< "[App Task] Panic UI Comp is not hooked " << endl;
        #endif
    }
}

void App::SetUI(UI* _ptrToUIObj)
{
    this->PtrToUIObj = _ptrToUIObj;
}

/*
*   @brief: Application Task function polls waits to receive a message
*            from the UI to prefrom processing
*/
void App::App_task()
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
            cout<< "[App Task] Processing the MSG : " << msg << endl;
            #endif
            this->process_event(msg);
            this->App_send_msg(msg);
            lock.lock(); // Re-lock the mutex before the next iteration
        }
    }
}

/*
*   @brief: to be called by UI component so App receives the msg
*   @param[in]: _msg  string message from UI
*   @return none
*/
void App::Receive_Msg(const string& msg)
{
    #ifdef DEBUG
    cout<< "[Poll_Input_task] MSG placed in App MSG Queue " << endl;
    #endif
    lock_guard<mutex> lock(mtx); // Lock the mutex
    messageQueue.push(msg); // Add the message to the queue
    cv.notify_one(); // Notify one waiting thread
}

uint8_t App::Subscribe_To_App_Event(const string& _msg, 
        function<void(const string&)> _callback)
{
#ifdef DEBUG
    cout<< "[User Task] SubScription " << endl;
#endif
    uint8_t event_id = 0;
    if (evenId_Cnt < MAX_NO_OF_SUBSCRIBERS)
    {
        evenId_Cnt++;
        Event_table_t& entry = eventTabl[evenId_Cnt]; 
        entry.event_id = evenId_Cnt;
        entry.callback = _callback;
        entry.PtrToStr = &_msg;
    
        #ifdef DEBUG
        cout<< "[User Task] SubScription succes " << endl;
        #endif
    }

    return event_id;
}
