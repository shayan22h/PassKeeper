#include "XmlHandler.h"
#include "tinyxml2.h"

using namespace tinyxml2;

const string XmlHandler::xmlHandler_message = "GetPass";

XmlHandler::XmlHandler(PassKeeper& _refToPassKeeper):
PassKeeperRefObj(_refToPassKeeper)
{
    // Register Callbacks for XML Handler Events
    PassKeeperRefObj.Subscribe_To_PassKeeper(
        Event_GetPass, xmlHandler_message,
        [this](Event_Id_t event_id ,std::string& req_str,std::string& rsp_str){
            return this->ProcessXmlHandleEvent(event_id,req_str,rsp_str);
        }
    );
}

XmlHandler::~XmlHandler()
{

}

Event_Status XmlHandler::ProcessXmlHandleEvent(Event_Id_t event_id,string& req_str, string& ref_rsp_str)
{
    Event_Status status = status_fail;
    // Load the XML file
    XMLDocument xmlDoc;
    XMLError eResult = xmlDoc.LoadFile("../../XMLFile/credentials.xml");
    if (eResult != XML_SUCCESS) {
        ref_rsp_str = "failed to load the file";
        return status_fail;
    }

    // Get the root element (Credentials)
    XMLNode* root = xmlDoc.FirstChildElement("Credentials");
    if (root == nullptr) {
        ref_rsp_str = "Failed to find root element 'Credentials'\n";
        return status_fail;
    }

    // Iterate through each Account element
    XMLElement* accountElement = root->FirstChildElement("Account");
  
    if (accountElement == nullptr) {
        ref_rsp_str = "No 'Account' elements found under 'Credentials'\n";
        return status_fail;
    }

    while (accountElement != nullptr) {

        // Get the Website element
        XMLElement* websiteElement = accountElement->FirstChildElement("Website");
        if (websiteElement != nullptr  && req_str == websiteElement->GetText()) {
            // If Website matches, retrieve UserName and Password
            XMLElement* userNameElement = accountElement->FirstChildElement("UserName");
            XMLElement* passwordElement = accountElement->FirstChildElement("Password");

            if (userNameElement != nullptr && passwordElement != nullptr) {
                string userName = userNameElement->GetText();
                string password = passwordElement->GetText();

                // Do something with userName and password
                cout << "UserName: " << userName << "\n";
                cout << "Password: " << password << "\n";

                status = status_success;
                ref_rsp_str = "username " + userName + " ---- " +" Password " + password;
                break;
            }
        }

        // Move to the next Account element
        accountElement = accountElement->NextSiblingElement("Account");
    }
    //if at this point status is not succes it means a match has not been found
    if (status != status_success)
    {
        ref_rsp_str = "Requested website is not in the XML File ";
    }

    return status;
}
