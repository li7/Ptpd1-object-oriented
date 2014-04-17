#include "MsgManagementPayload.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
MsgManagementPayload::MsgManagementPayload()
{
	clockIdentity;
	defaultData;
	current;
	parent;
	port;
	globalTime;
	foreign;
}

/*****************accessors***************/
ClockIdentity& MsgManagementPayload::get_clockIdentity()
{return clockIdentity;}

DefaultData& MsgManagementPayload::get_defaultData()
{return defaultData;}

Current& MsgManagementPayload::get_current()
{return current;}

Parent& MsgManagementPayload::get_parent()
{return parent;}

Port& MsgManagementPayload::get_port()
{return port;}

GlobalTime& MsgManagementPayload::get_globalTime()
{return globalTime;}

Foreign& MsgManagementPayload::get_foreign()
{return foreign;}

/****************mutators******************/
void MsgManagementPayload::set_clockIdentity(ClockIdentity ci)
{clockIdentity = ci;}

void MsgManagementPayload::set_clockIdentity_clockComTech(UInteger8 ci)
{clockIdentity.set_clockCommunicationTechnology(ci);}

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

