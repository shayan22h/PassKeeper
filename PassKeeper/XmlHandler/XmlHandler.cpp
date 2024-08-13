#include "XmlHandler.h"

const string XmlHandler::xmlHandler_message = "GetPass";

XmlHandler::XmlHandler(PassKeeper& _refToPassKeeper):
PassKeeperRefObj(_refToPassKeeper)
{
    // Register Callbacks for XML Handler Events
    PassKeeperRefObj.Subscribe_To_PassKeeper(
        Event_GetPass, xmlHandler_message,
        [this](Event_Id_t event_id ,std::string& rsp_str){
            return this->ProcessXmlHandleEvent(rsp_str, event_id);
        }
    );
}

XmlHandler::~XmlHandler()
{

}

Event_Status XmlHandler::ProcessXmlHandleEvent(string& ref_rsp_str, Event_Id_t event_id)
{

}