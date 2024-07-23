#include "Authenticator.h"

Authenticator::Authenticator(int _typeOfAuthentication, PassKeeper& _refToPassKeeper): 
typeOfAuthentication(_typeOfAuthentication),PasskeeperRefObj(_refToPassKeeper)
{
    // Constructor 

    // Subscribe to an event in the App with the event_id and a callback
    uint8_t event_id = 0;
    string auth_message = "verify";

    // Register callback for authentication event
    event_id = PasskeeperRefObj.Subscribe_To_PassKeeper(Event_Authenticate, auth_message, 
    [this](Event_Id_t event_id ,std::string& rsp_str) {
        return this->ProcessAuthentication();
    });

    if (event_id != 0xFF) {
        cout << "Subscribed to authentication event with event ID: " << (int)event_id << endl;
    } else {
        cout << "Failed to subscribe to authentication event." << endl;
    }
}

Authenticator::~Authenticator()
{

}
Event_Status Authenticator::ProcessAuthentication()
{
    return status_success;
}