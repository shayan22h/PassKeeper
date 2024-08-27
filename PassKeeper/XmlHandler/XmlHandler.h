#include <iostream>
#include <string>

#include "../PassKeeper.h"

using namespace std;
class XmlHandler{
    public:
    ~XmlHandler();
    XmlHandler(PassKeeper& _refToPassKeeper);
    
    private:
    static const string xmlHandler_message;
    PassKeeper& PassKeeperRefObj;
    Event_Status ProcessXmlHandleEvent(Event_Id_t event_id,string& req_str, string& ref_rsp_str);


};