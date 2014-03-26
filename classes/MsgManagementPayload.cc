#include "MsgManagementPayload.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
MsgManagementPayload::MsgManagementPayload()
{
}

/*****************accessors***************/
ClockIdentity MsgManagementPayload::get_clockIdentity() const
{return clockIdentity;}

DefaultData MsgManagementPayload::get_defaultData() const
{return defaultData;}

Current MsgManagementPayload::get_current() const
{return current;}

Parent MsgManagementPayload::get_parent() const
{return parent;}

Port MsgManagementPayload::get_port() const
{return port;}

GlobalTime MsgManagementPayload::get_globalTime() const
{return globalTime;}

Foreign MsgManagementPayload::get_foreign() const
{return foreign;}

/****************mutators******************/
void MsgManagementPayload::set_clockIdentity(ClockIdentity ci)
{clockIdentity = ci;}

void  MsgManagementPayload::set_defaultData(DefaultData dd)
{defaultData = dd;}

void MsgManagementPayload::set_current(Current c)
{current = c;}

void MsgManagementPayload::set_parent(Parent p)
{parent = p;}

void MsgManagementPayload::set_port(Port p)
{port = p;}

void MsgManagementPayload::set_globalTime(GlobalTime gt)
{globalTime = gt;}

void MsgManagementPayload::set_foreign(Foreign f)
{foreign = f;}

MsgManagementPayload &MsgManagementPayload::operator=(const MsgManagementPayload & other_t)
{
	clockIdentity = other_t.clockIdentity;
	defaultData = other_t.defaultData;
	current = other_t.current;
	parent = other_t.parent;
	port = other_t.port;
	globalTime = other_t.globalTime;
	foreign = other_t.foreign;

	return *this;
}
ostream& operator<<(ostream& s, const MsgManagementPayload& it)
{
        cout << "clock identity : " << it.clockIdentity << endl;
        cout << "defaultData : " << it.defaultData << endl;
        cout << "foreign : " << it.foreign << endl;
	cout << "parent : " << it.parent << endl;

        return s;
}

