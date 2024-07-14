#ifndef UI_H
#define UI_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

#include "../App/App.h"

class UI{
    public:
        UI(App& _application);
        ~UI();
        void UI_task(void);


    private:
        App& application;
        void Poll_Input_task(); // Independent Task polls for input
        void UI_Send_MsgToApp(const std::string& _str);
};

#endif // UI_H