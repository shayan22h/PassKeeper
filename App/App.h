#ifndef APP_H
#define APP_H

// Include Libs
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
using namespace std;

class App{

    public:
        App();  // constructor 
        ~App(); // destructor
        void App_task();
        void Receive_Msg(const string& msg);

    private:
        queue<string> messageQueue;
        mutex mtx;
        condition_variable cv;

};
#endif // APP_H