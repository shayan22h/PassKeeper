#ifndef UI_H
#define UI_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

using namespace std;
class AppCenter; // FW declaration of AppCenter class

class UI{
    public:
        UI();
        ~UI();
        void UI_task(void);
        void UI_Receive_MSG(const string& msg);
        void SetApp(AppCenter* _ptrToAppObj);


    private:
        /** Variables **/
        AppCenter* PtrToAppObj;
        queue<string> ui_messageQueue;
        mutex ui_mtx;
        condition_variable ui_cv;
        /** Functions **/
        void Poll_Input_task(); // Independent Task polls for input
        void UI_send_msg(const std::string& _msg);
};

#endif // UI_H