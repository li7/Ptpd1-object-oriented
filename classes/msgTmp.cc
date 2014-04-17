#include "msgTmp.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
msgTmp::msgTmp()
{
}

/*****************accessors***************/
MsgSync& msgTmp::get_sync()
{return sync;}

MsgFollowUp& msgTmp::get_follow()
{return follow;}

MsgDelayReq& msgTmp::get_req()
{return req;}

MsgDelayResp& msgTmp::get_resp()
{return resp;}

MsgManagement& msgTmp::get_manage()
{return manage;}

/****************mutators******************/
void msgTmp::set_sync(MsgSync s)
{sync = s;}

void  msgTmp::set_follow(MsgFollowUp f)
{follow = f;}

void msgTmp::set_req(MsgDelayReq r)
{req = r;}

void msgTmp::set_resp(MsgDelayResp r)
{resp = r;}

void msgTmp::set_manage(MsgManagement m)
{manage = m;}

void msgTmp::set_manage(int m, int i)
{memset(&manage,0,sizeof(MsgManagement));}

ostream& operator<<(ostream& s, const msgTmp& it)
{
        return s;
}

