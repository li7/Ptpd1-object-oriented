#include "MsgManagement.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
MsgManagement::MsgManagement()
{
	targetCommunicationTechnology = 0;
        memset(&targetUuid,0,PTP_UUID_LENGTH);
        targetPortId = 0;
        startingBoundaryHops = 0;
        boundaryHops = 0;
        managementMessageKey = 0;
        parameterLength = 0;
        recordKey = 0;
        payload;
}

/*****************accessors***************/
UInteger8 MsgManagement::get_targetCommunicationTechnology() const
{return targetCommunicationTechnology;}

Octet* MsgManagement::get_targetUuid()
{return targetUuid;}

UInteger16 MsgManagement::get_targetPortId() const
{return targetPortId;}

Integer16 MsgManagement::get_startingBoundaryHops() const
{return startingBoundaryHops;}

Integer16 MsgManagement::get_boundaryHops() const
{return boundaryHops;}

UInteger8 MsgManagement::get_managementMessageKey() const
{return managementMessageKey;}

UInteger16 MsgManagement::get_parameterLength() const
{return parameterLength;}

UInteger16 MsgManagement::get_recordKey() const
{return recordKey;}

MsgManagementPayload MsgManagement::get_payload() const
{return payload;}

/****************mutators******************/
void MsgManagement::set_targetCommunicationTechnology(UInteger8 tct)
{targetCommunicationTechnology = tct;}

void MsgManagement::set_targetUuid(const void *tu, int length)
{memcpy(targetUuid,tu,length);}

void MsgManagement::set_targetPortId(UInteger16 tpi)
{targetPortId = tpi;}

void MsgManagement::set_startingBoundaryHops(Integer16 sbh)
{startingBoundaryHops = sbh;}

void MsgManagement::set_boundaryHops(Integer16 bh)
{boundaryHops = bh;}

void MsgManagement::set_managementMessageKey(UInteger8 mmk)
{managementMessageKey = mmk;}

void MsgManagement::set_parameterLength(UInteger16 pl)
{parameterLength = pl;}

void MsgManagement::set_recordKey(UInteger16 rk)
{recordKey = rk;}

void MsgManagement::set_payload(MsgManagementPayload p)
{payload = p;}

MsgManagement &MsgManagement::operator=(const MsgManagement & other_t)
{
	targetCommunicationTechnology = other_t.targetCommunicationTechnology;
	memcpy(targetUuid,other_t.targetUuid,strlen(targetUuid));
	targetPortId = other_t.targetPortId;
	startingBoundaryHops = other_t.startingBoundaryHops;
	boundaryHops = other_t.boundaryHops;
	managementMessageKey = other_t.managementMessageKey;
	parameterLength = other_t.parameterLength;
	recordKey = other_t.recordKey;
	payload = other_t.payload;

	return *this;
}
ostream& operator<<(ostream& s, const MsgManagement& it)
{
	cout << "targetCommunicationTechnology: " << it.targetCommunicationTechnology << endl;
	cout << "targetUuid: " << it.targetUuid << endl;
	cout << "payload: " << it.payload << endl;
	cout << "clock Uuid field" << it.payload << endl;

        return s;
}

