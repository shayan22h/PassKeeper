#include <iostream>
#include "PassKeeper.h"

#define MAX_NO_EVENTS_SUPPORTED 5
PassKeeper::PassKeeper()
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

bool PassKeeper::Subscribe_To_PassKeeper(Event_Id_t _event_id, const string& _pToStr,
    function <Event_Status(Event_Id_t, string&)> _callback)
{
    bool status = false;
#ifdef DEBUG
    cout<< "[Pass Keeper : User Task] SubScription " << endl;
#endif
    uint8_t event_id = 0;
    if (Event_Table_Entry_Cnt < MAX_NO_EVENTS_SUPPORTED)
    {
        
        Event_Table_t& entry = Event_Table[Event_Table_Entry_Cnt]; 
        Event_Table_Entry_Cnt++;

        entry.Event_Id = _event_id;
        entry.Callback = _callback;
        entry.PtrToStr = &_pToStr;

        status = true;
    
        #ifdef DEBUG
        cout<< "[User Task] SubScription succes " << endl;
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
    cout<< "[Pass Keeper] Processing the MSG : " << _refToReq << endl;
    #endif
    Event_Status status = status_match_not_found;

    for (uint8_t i= 0; i <MAX_NO_EVENTS_SUPPORTED; i++)
    {
        if (Event_Table[i].PtrToStr && _refToReq == *(Event_Table[i].PtrToStr) 
        && Event_Table[i].Callback)
        {
            status = Event_Table[i].Callback(Event_Table[i].Event_Id, _refToResp);
            break;
        }
    }
    if (status == status_match_not_found)
    {
        #ifdef DEBUG
        cout<< "[Pass Keeper] No matching event found: " <<  endl;
        #endif
        _refToResp = "No matching event found";
    }
    
}