#ifndef PASS_KEEPER_H
#define PASS_KEEPER_H

#include <string>
#include <functional>

using namespace std;
typedef enum{
    PassKeeper_idle = 0,
    PassKeeper_Authenticated
}PassKeeper_state_t;

typedef enum{
    Event_Invalid = 0,
    Event_Authenticate,
    Event_GetPass
}Event_Id_t;

typedef enum{
    status_success = 0,
    status_match_not_found,
    stats_invalid_request,
    status_fail
}Event_Status;

typedef struct{
    const string* PtrToStr;
    Event_Id_t Event_Id;
    function <Event_Status(Event_Id_t,string&, string&)> Callback;
}Event_Table_t;

class PassKeeper{

    public:
    PassKeeper();
    ~PassKeeper();
    void AppCenter_FW_msg_To_PassKeeper(const string& _refToReq,
    string& _refToResp);
    bool Subscribe_To_PassKeeper(Event_Id_t _event_id, const string& _pToStr,
    function <Event_Status(Event_Id_t, string&, string&)> _callback);

    private:
    Event_Table_t Event_Table[5];
    uint8_t Event_Table_Entry_Cnt;
    bool check_state(Event_Id_t _event_id);
    void update_state(Event_Id_t _event_id, Event_Status _event_status);
    PassKeeper_state_t Passkeeper_state;
};
#endif //PASS_KEEPER_H