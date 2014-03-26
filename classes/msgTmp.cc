#include "msgTmp.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
msgTmp::msgTmp()
{
}

/*****************accessors***************/
/*const MsgSync& msgTmp::get_sync() const
{return sync;}
*/

MsgSync& msgTmp::get_sync()
{return sync;}

MsgFollowUp msgTmp::get_follow() const
{return follow;}

MsgDelayReq msgTmp::get_req() const
{return req;}

MsgDelayResp msgTmp::get_resp() const
{return resp;}

MsgManagement msgTmp::get_manage() const
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

ostream& operator<<(ostream& s, const msgTmp& it)
{
        return s;
}

