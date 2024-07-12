#include <iostream>
#include <string>

using namespace std;

class Authenticator{
    public:
    ~Authenticator();
    Authenticator(int _typeOfAuthentication);
    
    private:
    int typeOfAuthentication;
};