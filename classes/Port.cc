#include "Port.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
Port::Port()
{
        returnedPortNumber=0;
        portState=0;
        lastSyncEventSequenceNumber=0;
        lastGeneralEventSequenceNumber=0;
        portCommunicationTechnology=0;
        memset(&portUuidField,0,PTP_UUID_LENGTH);
        portIdField=0;
        burstEnabled=0;
        subdomainAddressOctets=0;
        eventPortAddressOctets=0;
        generalPortAddressOctets=0;
        memset(&subdomainAddress,0,SUBDOMAIN_ADDRESS_LENGTH);
        memset(&eventPortAddress,0,PORT_ADDRESS_LENGTH);
        memset(&generalPortAddress,0,PORT_ADDRESS_LENGTH);
}

/*****************accessors***************/
UInteger16 Port::get_returnedPortNumber() const
{return returnedPortNumber;}

UInteger8 Port::get_portState() const
{return portState;}

UInteger16 Port::get_lastSyncEventSequenceNumber() const
{return lastSyncEventSequenceNumber;}

UInteger16 Port::get_lastGeneralEventSequenceNumber() const
{return lastGeneralEventSequenceNumber;}

UInteger8 Port::get_portCommunicationTechnology() const
{return portCommunicationTechnology;}

Octet Port::get_portUuidField() const
{return *portUuidField;}

Octet Port::get_portUuidField(int i) const
{return portUuidField[i];}

UInteger16 Port::get_portIdField() const
{return portIdField;}

Boolean Port::get_burstEnabled() const
{return burstEnabled;}

UInteger8 Port::get_subdomainAddressOctets() const
{return subdomainAddressOctets;}

UInteger8 Port::get_eventPortAddressOctets() const
{return eventPortAddressOctets;}

UInteger8 Port::get_generalPortAddressOctets() const
{return generalPortAddressOctets;}

Octet Port::get_subdomainAddress() const
{return *subdomainAddress;}

Octet Port::get_subdomainAddress(int i) const
{return subdomainAddress[i];}

Octet Port::get_eventPortAddress() const
{return *eventPortAddress;}

Octet Port::get_eventPortAddress(int i) const
{return eventPortAddress[i];}

Octet Port::get_generalPortAddress() const
{return *generalPortAddress;}

Octet Port::get_generalPortAddress(int i) const
{return generalPortAddress[i];}

/****************mutators******************/
void Port::set_returnedPortNumber(UInteger16 rpn)
{returnedPortNumber = rpn;}

void Port::set_portState(UInteger8 ps)
{portState = ps;}

void Port::set_lastSyncEventSequenceNumber(UInteger16 lsesn)
{lastSyncEventSequenceNumber = lsesn;}

void Port::set_lastGeneralEventSequenceNumber(UInteger16 lgesn)
{lastGeneralEventSequenceNumber = lgesn;}

void Port::set_portCommunicationTechnology(UInteger8 pct)
{portCommunicationTechnology = pct;}

void Port::set_portUuidField(const void *puf, int length)
{memcpy(portUuidField,puf,length);}

void Port::set_portIdField(UInteger16 pif)
{portIdField = pif;}

void Port::set_burstEnabled(Boolean be)
{burstEnabled = be;}

void Port::set_subdomainAddressOctets(UInteger8 sao)
{subdomainAddressOctets = sao;}

void Port::set_eventPortAddressOctets(UInteger8 epao)
{eventPortAddressOctets = epao;}

void Port::set_generalPortAddressOctets(UInteger8 gpao)
{generalPortAddressOctets = gpao;}

void Port::set_subdomainAddress(const void *sa, int length)
{memcpy(subdomainAddress,sa,length);}

void Port::set_eventPortAddress(const void *epa, int length)
{memcpy(eventPortAddress,epa,length);}

void Port::set_generalPortAddress(const void *gpa, int length)
{memcpy(generalPortAddress,gpa,length);}

Port &Port::operator=(const Port & other_t)
{
	returnedPortNumber = other_t.returnedPortNumber;
	portState = other_t.portState;
	lastSyncEventSequenceNumber = other_t.lastSyncEventSequenceNumber;
	lastGeneralEventSequenceNumber = other_t.lastGeneralEventSequenceNumber;
	portCommunicationTechnology = other_t.portCommunicationTechnology;
	memcpy(portUuidField,other_t.portUuidField,strlen(other_t.portUuidField));
	portIdField = other_t.portIdField;
	burstEnabled = other_t.burstEnabled;
	subdomainAddressOctets = other_t.subdomainAddressOctets;
	eventPortAddressOctets = other_t.eventPortAddressOctets;
	generalPortAddressOctets = other_t.generalPortAddressOctets;
	memcpy(subdomainAddress,other_t.subdomainAddress,strlen(other_t.subdomainAddress));
	memcpy(eventPortAddress,other_t.eventPortAddress,strlen(other_t.eventPortAddress));
	memcpy(generalPortAddress,other_t.generalPortAddress,strlen(other_t.generalPortAddress));
	return *this;
}

ostream& operator<<(ostream& s, const Port& it)
{
        return s;
}

