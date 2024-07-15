#ifndef APP_H
#define APP_H

// Include Libs
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>


using namespace std;
class UI; // FW declaration of UI class
class App{

    public:
        App();  
        ~App(); 
        void SetUI(UI* _ptrToUIObj);
        void App_task();
        void Receive_Msg(const string& msg);

    private:
        /** Variables **/
        UI* PtrToUIObj;
        queue<string> messageQueue;
        mutex mtx;
        condition_variable cv;
        /** Functions **/
        void process_event(const string& msg);

};
#endif // APP_H