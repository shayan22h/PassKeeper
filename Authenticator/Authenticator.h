#include <iostream>
#include <string>

#include "../PassKeeper/PassKeeper.h"
using namespace std;

class Authenticator{
    public:
    ~Authenticator();
    Authenticator(int _typeOfAuthentication, PassKeeper& _refToPassKeeper);
    Event_Status ProcessAuthentication(void);
    
    private:
    int typeOfAuthentication;
    PassKeeper& PasskeeperRefObj;
};