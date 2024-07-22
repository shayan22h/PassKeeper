#include "Authenticator.h"

Authenticator::Authenticator(int _typeOfAuthentication, App& _appRef): 
typeOfAuthentication(_typeOfAuthentication),appRef(_appRef)
{
    // Constructor 

    // Subscribe to an event in the App with the event_id and a callback
    uint8_t event_id = 0;
    string auth_message = "verify";

    // Register callback for authentication event
    event_id = appRef.Subscribe_To_App_Event(auth_message, [this](const std::string& msg) {
        this->ProcessAuthentication();
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
void Authenticator::ProcessAuthentication()
{

}