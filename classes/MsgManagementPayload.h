#ifndef MSGMANAGMENTPAYLOAD_H
#define MSGMANAGMENTPAYLOAD_H
#include "ClockIdentity.h"
#include "DefaultData.h"
#include "Current.h"
#include "Parent.h"
#include "Port.h"
#include "GlobalTime.h"
#include "Foreign.h"
#include "constants.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class MsgManagementPayload{

public:

	/********Constructor********/
	MsgManagementPayload();

	/********Accsessor********/
	ClockIdentity& get_clockIdentity();
	DefaultData& get_defaultData();
	Current& get_current();
	Parent& get_parent();
	Port& get_port();
	GlobalTime& get_globalTime();
	Foreign& get_foreign();

	/********Mutators*******/
	void set_clockIdentity(ClockIdentity ci);
	void set_clockIdentity_clockComTech(UInteger8 ci);
	void set_defaultData(DefaultData dd);
	void set_current(Current c);
	void set_parent(Parent p);
	void set_port(Port p);
	void set_globalTime(GlobalTime gt);
	void set_foreign(Foreign f);

	/********Operators*******/
	MsgManagementPayload &operator=(const MsgManagementPayload & other_t);
	friend ostream& operator<<(ostream& s, const MsgManagementPayload& it);

private:
	ClockIdentity clockIdentity;
	DefaultData defaultData;
	Current current;
	Parent parent;
	Port port;
	GlobalTime globalTime;
	Foreign foreign;
};

ostream& operator<<(ostream& s, const MsgManagementPayload& it);

#endif
