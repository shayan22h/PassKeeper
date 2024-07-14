#include "App.h"
#include <iostream>



App::App()
{
    // Constructor 
}
App::~App()
{
    
}

void App::App_task()
{
    
    unique_lock<mutex> lock(mtx);
    cv.wait(lock,[this]{ return !messageQueue.empty();});

    
    while(!messageQueue.empty())
    {
        string msg = messageQueue.front(); // Get the first message
        messageQueue.pop(); // remove it from the Queue
        lock.unlock(); // Unlock the mutex to allow other threads to access the queue

        // Process the message
        cout << "MSG Receive in Application Ready for processing: " << msg << std::endl;


        lock.lock(); // Re-lock the mutex before the next iteration
    }
    
}

void App::Receive_Msg(const string& msg)
{
    cout << " Message Received in Application ";
    lock_guard<mutex> lock(mtx); // Lock the mutex
    messageQueue.push(msg); // Add the message to the queue
    cv.notify_one(); // Notify one waiting thread
}


