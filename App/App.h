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
typedef struct{
    const string* PtrToStr;
    uint8_t event_id;
    function<void(const string&)> callback;
}Event_table_t;

class UI; // FW declaration of UI class
class App{

    public:
        App();  
        ~App(); 
        void SetUI(UI* _ptrToUIObj);
        void App_task();
        void Receive_Msg(const string& msg);
        uint8_t Subscribe_To_App_Event(const string& _msg, 
        function<void(const string&)> _callback);

    private:
        /** Variables **/
        UI* PtrToUIObj;
        queue<string> messageQueue;
        mutex mtx;
        condition_variable cv;
        /** Variables -- Event **/
        Event_table_t eventTabl[5];
        uint8_t evenId_Cnt;

        /** Functions **/
        void process_event(const string& _msg);
        void App_send_msg(const string& _msg);

};
#endif // APP_H