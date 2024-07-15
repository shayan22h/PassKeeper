#ifndef UI_H
#define UI_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class App; // FW declaration of App class

class UI{
    public:
        UI();
        ~UI();
        void UI_task(void);
        void SetApp(App* _ptrToAppObj);


    private:
        App* PtrToAppObj;
        void Poll_Input_task(); // Independent Task polls for input
        void UI_Send_MsgToApp(const std::string& _str);
};

#endif // UI_H