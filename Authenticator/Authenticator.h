#include <iostream>
#include <string>

#include "../App/App.h"
using namespace std;

class Authenticator{
    public:
    ~Authenticator();
    Authenticator(int _typeOfAuthentication, App& _refToApp);
    void ProcessAuthentication(void);
    
    private:
    int typeOfAuthentication;
    App& appRef;
};