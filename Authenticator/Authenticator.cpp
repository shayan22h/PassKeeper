#include "Authenticator.h"

// Define the static const string
const string Authenticator::auth_message = "tehran";

Authenticator::Authenticator(int _typeOfAuthentication, PassKeeper& _refToPassKeeper): 
typeOfAuthentication(_typeOfAuthentication),PasskeeperRefObj(_refToPassKeeper)
{
    // Register callback for authentication event
    PasskeeperRefObj.Subscribe_To_PassKeeper(Event_Authenticate, auth_message, 
    [this](Event_Id_t event_id ,std::string& rsp_str) {
        return this->ProcessAuthentication(rsp_str, event_id);
    });
    
}

Authenticator::~Authenticator()
{

}
Event_Status Authenticator::ProcessAuthentication(string& ref_rsp_str, Event_Id_t event_id)
{
    (void)event_id; // Suppress unused parameter warning

    ref_rsp_str = "Validation Approved ";
    #ifdef DEBUG
    cout<< "[Authenticator]  Processing the Authentication: " <<  endl;
    #endif
    return status_success;
}