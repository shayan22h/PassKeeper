#include <iostream>
#include <string>

#include "../PassKeeper.h"
using namespace std;

class Authenticator{
    public:
    ~Authenticator();
    Authenticator(int _typeOfAuthentication, PassKeeper& _refToPassKeeper);
    Event_Status ProcessAuthentication(string& ref_rsp_str,Event_Id_t event_id);
    
    private:
    int typeOfAuthentication;
    PassKeeper& PasskeeperRefObj;
    static const string auth_message;
};