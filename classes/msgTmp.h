#ifndef MSGTMP_H
#define MSGTMP_H
#include "MsgSync.h"
#include "MsgDelayReq.h"
#include "MsgFollowUp.h"
#include "MsgDelayResp.h"
#include "MsgManagement.h"
#include "constants.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class msgTmp{

public:

	/********Constructor********/
	msgTmp();

	/********Accsessor********/
	MsgSync& get_sync();
	//MsgSync get_sync() const;
	MsgFollowUp get_follow() const;
	MsgDelayReq get_req() const;
	MsgDelayResp get_resp() const;
	MsgManagement get_manage() const;

	/********Mutators*******/
	void set_sync(MsgSync s);
	void set_follow(MsgFollowUp f);
	void set_req(MsgDelayReq r);
	void set_resp(MsgDelayResp r);
	void set_manage(MsgManagement m);

	/********Operators*******/
	friend ostream& operator<<(ostream& s, const msgTmp& it);

private:
        MsgSync sync;
        MsgFollowUp follow;
        MsgDelayReq req;
        MsgDelayResp resp;
        MsgManagement manage;
};

ostream& operator<<(ostream& s, const msgTmp& it);

#endif
