#include "DefaultData.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
DefaultData::DefaultData()
{
        clockCommunicationTechnology=0;
        memset(&clockUuidField,0,PTP_UUID_LENGTH);
        clockPortField=0;
        clockStratum=0;
        memset(&clockIdentifier,0,PTP_CODE_STRING_LENGTH);
        clockVariance=0;
        clockFollowupCapable=0;
        preferred=0;
	initializable=0;
        externalTiming=0;
        isBoundaryClock=0;
        syncInterval=0;
        memset(&subdomainName,0,PTP_SUBDOMAIN_NAME_LENGTH);
        numberPorts = 0;
        numberForeignRecords=0;

}

/*****************accessors***************/
UInteger8 DefaultData::get_clockCommunicationTechnology() const
{return clockCommunicationTechnology;}

Octet DefaultData::get_clockUuidField() const
{return *clockUuidField;}

Octet DefaultData::get_clockUuidField(int position) const
{return clockUuidField[position];}

UInteger16 DefaultData::get_clockPortField() const
{return clockPortField;}

UInteger8 DefaultData::get_clockStratum() const
{return clockStratum;}

Octet DefaultData::get_clockIdentifier() const
{return *clockIdentifier;}

Octet DefaultData::get_clockIdentifier(int position) const
{return clockIdentifier[position];}

Integer16 DefaultData::get_clockVariance() const
{return clockVariance;}

Boolean DefaultData::get_clockFollowupCapable() const
{return clockFollowupCapable;}

Boolean DefaultData::get_preferred() const
{return preferred;}

Boolean DefaultData::get_initializable() const
{return initializable;}

Boolean DefaultData::get_externalTiming() const
{return externalTiming;}

Boolean DefaultData::get_isBoundaryClock() const
{return isBoundaryClock;}

Integer8 DefaultData::get_syncInterval() const
{return syncInterval;}

Octet DefaultData::get_subdomainName() const
{return *subdomainName;}

Octet DefaultData::get_subdomainName(int x) const
{return subdomainName[x];}

UInteger16 DefaultData::get_numberPorts() const
{return numberPorts;}

UInteger16 DefaultData::get_numberForeignRecords() const
{return numberForeignRecords;}

/****************mutators******************/
void DefaultData::set_clockCommunicationTechnology(UInteger8 cct)
{clockCommunicationTechnology = cct;}

void DefaultData::set_clockUuidField(const void *cuf, int length)
{memcpy(clockUuidField,cuf,length);}

void DefaultData::set_clockPortField(UInteger16 cpf)
{clockPortField = cpf;}

void DefaultData::set_clockStratum(UInteger8 cs)
{clockStratum = cs;}

void DefaultData::set_clockIdentifier(const void *ci, int length)
{memcpy(clockIdentifier,ci,length);}

void DefaultData::set_clockVariance(Integer16 cv)
{clockVariance = cv;}

void DefaultData::set_clockFollowupCapable(Boolean cfc)
{clockFollowupCapable = cfc;}

void DefaultData::set_preferred(Boolean p)
{preferred = p;}

void DefaultData::set_initializable(Boolean i)
{initializable = i;}

void DefaultData::set_externalTiming(Boolean et)
{externalTiming = et;}

void DefaultData::set_isBoundaryClock(Boolean ibc)
{isBoundaryClock = ibc;}

void DefaultData::set_syncInterval(Integer8 si)
{syncInterval = si;}

void DefaultData::set_subdomainName(const void *sn, int length)
{memcpy(subdomainName,sn,length);}

void DefaultData::set_numberPorts(UInteger16 np)
{numberPorts = np;}

void DefaultData::set_numberForeignRecords(UInteger16 nfr)
{numberForeignRecords = nfr;}

DefaultData &DefaultData::operator=(const DefaultData & other_t)
{
	clockCommunicationTechnology = other_t.clockCommunicationTechnology;
	memcpy(clockUuidField,other_t.clockUuidField,strlen(other_t.clockUuidField));
	clockPortField = other_t.clockPortField;
	clockStratum = other_t.clockStratum;
	memcpy(clockIdentifier,other_t.clockIdentifier,strlen(other_t.clockIdentifier));
	clockVariance = other_t.clockVariance;
	clockFollowupCapable = other_t.clockFollowupCapable;
	preferred = other_t.preferred;
	initializable = other_t.initializable;
	isBoundaryClock = other_t.isBoundaryClock;
	syncInterval = other_t.syncInterval;
	memcpy(subdomainName,other_t.subdomainName,strlen(other_t.subdomainName));
	numberPorts = other_t.numberPorts;
	numberForeignRecords = other_t.numberForeignRecords;
	return *this;
}
ostream& operator<<(ostream& s, const DefaultData& it)
{
        return s;
}

