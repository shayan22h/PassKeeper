#include <iostream>
#include "PassKeeper.h"

#define MAX_NO_EVENTS_SUPPORTED 5
PassKeeper::PassKeeper():Passkeeper_state(PassKeeper_idle)
{
    Event_Table_Entry_Cnt = 0;
    for (uint8_t i= 0; i < MAX_NO_EVENTS_SUPPORTED; i++)
    {
        /* Event Table Initialization */
        Event_Table[i].PtrToStr = nullptr;
        Event_Table[i].Event_Id = Event_Invalid;
        Event_Table[i].Callback = nullptr;
    }
}

PassKeeper::~PassKeeper()
{

}

/*
*   @brief: The state Machine of PassKeeper Logic controller
*   @param[in]: _event_id  event requested by user
*   @return status(bool) true valid event id in accordance with state
                         false invalid event id in accordance with state
*/
bool PassKeeper::PassKeeper_StateMachine_Handler(Event_Id_t _event_id)
{
    bool status = false;
    if(Passkeeper_state == PassKeeper_idle && _event_id == Event_Authenticate)
    {
        status = true;
        Passkeeper_state = PassKeeper_Authenticated;
    }
    else if (Passkeeper_state == PassKeeper_Authenticated)
    {

    }
    return status;
}

bool PassKeeper::Subscribe_To_PassKeeper(Event_Id_t _event_id, const string& _pToStr,
    function <Event_Status(Event_Id_t,string&, string&)> _callback)
{
    bool status = false;
#ifdef DEBUG
    cout<< "[PassKeeper] SubScription Request " << endl;
#endif
    if (Event_Table_Entry_Cnt < MAX_NO_EVENTS_SUPPORTED)
    {
        
        Event_Table_t& entry = Event_Table[Event_Table_Entry_Cnt]; 
        Event_Table_Entry_Cnt++;

        entry.Event_Id = _event_id;
        entry.Callback = _callback;
        entry.PtrToStr = &_pToStr;

        status = true;
    
        #ifdef DEBUG
        cout<< "[PassKeeper] SubScription succes -> str is " << _pToStr << endl;
        #endif
    }
    return status;
}

void PassKeeper::AppCenter_FW_msg_To_PassKeeper(const string& _refToReq,
    string& _refToResp)
{
    //TODO -- REMOVE this
    if (_refToReq == "exit")
    {
        exit(0);
    }
    #ifdef DEBUG
    cout<< "[Pass Keeper] Processing the MSG :---------- " << _refToReq << endl;
    #endif
    Event_Status status = status_match_not_found;

    size_t spacePos = _refToReq.find(' ');
    string payloadStr = "";
    string headerStr = _refToReq;
    if (spacePos != string::npos)
    {
        headerStr = _refToReq.substr(0, spacePos);
        payloadStr = _refToReq.substr(spacePos + 1);
    }

    for (uint8_t i= 0; i <MAX_NO_EVENTS_SUPPORTED; i++)
    {
        if (Event_Table[i].PtrToStr && headerStr == *(Event_Table[i].PtrToStr) 
        && Event_Table[i].Callback)
        {
            //Pass Keeper Controller State Machine
            if (PassKeeper_StateMachine_Handler(Event_Table[i].Event_Id))
            {
                // Dispatch The Callback to the right component 
                status = Event_Table[i].Callback(Event_Table[i].Event_Id, payloadStr, _refToResp);
            }
            else
            {
                status = stats_invalid_request;
                _refToResp = "Invalid Request";
            }
            break;
        }
    }
    if (status == status_match_not_found)
    {
        #ifdef DEBUG
        cout<< "[Pass Keeper] No matching event found: " <<  endl;
        #endif
        _refToResp = "Match not found";
    }
    
}