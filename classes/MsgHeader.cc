#include "MsgHeader.h"
#include "stdio.h"
#include <iostream>
#include <string.h>

using namespace std;

MsgHeader::MsgHeader()
{
versionPTP = 1;
versionNetwork = 1;
}

/* Accessors */
UInteger16 MsgHeader::get_versionPTP() const 
{return versionPTP;}

UInteger16 MsgHeader::get_versionNetwork() const 
{return versionNetwork;}

Octet* MsgHeader::get_subdomain()
{return subdomain;}

UInteger8 MsgHeader::get_messageType() const 
{return messageType;}

UInteger8 MsgHeader::get_sourceCommunicationTechnology() const 
{return sourceCommunicationTechnology;}

Octet * MsgHeader::get_sourceUuid()
{return sourceUuid;}

Octet MsgHeader::get_sourceUuid(int position)
{return sourceUuid[position];}

UInteger16 MsgHeader::get_sourcePortId() const
{return sourcePortId;}

UInteger16 MsgHeader::get_sequenceId() const
{return sequenceId;}

UInteger8 MsgHeader::get_control() const
{return control;}

Octet * MsgHeader::get_flags()
{return flags;}

/* Mutators */
void MsgHeader::set_versionPTP(UInteger16 vp)
{versionPTP = vp;}

void MsgHeader::set_versionNetwork(UInteger16 vn)
{versionNetwork = vn;}

void MsgHeader::set_subdomain(const void *sd, int length)
{memcpy(subdomain,sd,length);}

void MsgHeader::set_messageType(UInteger8 mt)
{messageType = mt;}

void MsgHeader::set_sourceCommunicationTechnology(UInteger8 sct)
{sourceCommunicationTechnology = sct;}

void MsgHeader::set_sourceUuid(const void *su, int length)
{memcpy(sourceUuid,su,length);}

void MsgHeader::set_sourcePortId(UInteger16 spid)
{sourcePortId = spid;}

void MsgHeader::set_sequenceId(UInteger16 sid)
{sequenceId = sid;}

void MsgHeader::set_control(UInteger8 c)
{control = c;}

void MsgHeader::set_flags(const void *f, int length)
{memcpy(flags,f,length);}

MsgHeader &MsgHeader::operator=(const MsgHeader & other_t)
{
	versionPTP = other_t.versionPTP;
	versionNetwork = other_t.versionNetwork;
	memcpy(subdomain,other_t.subdomain,PTP_SUBDOMAIN_NAME_LENGTH);
	messageType = other_t.messageType;
	sourceCommunicationTechnology = other_t.sourceCommunicationTechnology;
	memcpy(sourceUuid,other_t.sourceUuid,PTP_UUID_LENGTH);
	sourcePortId = other_t.sourcePortId;
	sequenceId = other_t.sequenceId;
	control = other_t.control;
	memcpy(flags,other_t.flags,2);

	return *this;	
}

ostream& operator<<(ostream& s, const MsgHeader& it)
{
	cout << "Version PTP : " << it.versionPTP << endl;
	cout << "Version Network : " << it.versionNetwork << endl;
	cout << "Subdomain : " << it.subdomain << endl;
	printf("MessageType : %d\n",it.messageType);
	printf("Source Comm Tech : %d\n",it.sourceCommunicationTechnology);
	printf("Source Uuid : %d\n",*it.sourceUuid);
	cout << "Source PortID : " << it.sourcePortId << endl;
	cout << "Sequence ID : " << it.sequenceId << endl;
	printf("Control : %d\n",it.control);
	printf("flags : %d\n",*it.flags);

	return s;
}
