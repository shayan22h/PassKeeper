#ifndef APP_H
#define APP_H

// Include Libs
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

#include <map>
#include <functional>


using namespace std;

class UI; // FW declaration of UI class
class PassKeeper; // FW declaration PassKeeper Class
class AppCenter{

    public:
        AppCenter();  
        ~AppCenter(); 
        void SetPassKeeper(PassKeeper* _ptrToPassKeeperAppObj);
        void SetUI(UI* _ptrToUIObj);
        void App_task();
        void Receive_Msg(const string& msg);
        uint8_t Subscribe_To_App_Event(const string& _msg, 
        function<void(const string&)> _callback);

    private:
        /** Variables **/
        PassKeeper* PtrToPassKeeperAppObj;
        UI* PtrToUIObj;
        queue<string> messageQueue;
        mutex mtx;
        condition_variable cv;

        /** Functions **/
        void AppCenter_send_msg(const string& _msg);

};
#endif // APP_H