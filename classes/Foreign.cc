#include "Foreign.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
Foreign::Foreign()
{
}

/*****************accessors***************/
UInteger16 Foreign::get_returnedPortNumber() const
{return returnedPortNumber;}

UInteger16 Foreign::get_returnedRecordNumber() const
{return returnedRecordNumber;}

UInteger8 Foreign::get_foreignMasterCommunicationTechnology() const
{return foreignMasterCommunicationTechnology;}

Octet Foreign::get_foreignMasterUuid() const
{return *foreignMasterUuid;}

UInteger16 Foreign::get_foreignMasterPortId() const
{return foreignMasterPortId;}

UInteger16 Foreign::get_foreignMasterSyncs() const
{return foreignMasterSyncs;}

/****************mutators******************/
void Foreign::set_returnedPortNumber(UInteger16 rpn)
{returnedPortNumber = rpn;}

void Foreign::set_returnedRecordNumber(UInteger16 rrn)
{returnedRecordNumber = rrn;}

void Foreign::set_foreignMasterCommunicationTechnology(UInteger8 fmct)
{foreignMasterCommunicationTechnology = fmct;}

void Foreign::set_foreignMasterUuid(const void *fmu, int length)
{memcpy(foreignMasterUuid,fmu,length);}

void Foreign::set_foreignMasterPortId(UInteger16 fmpi)
{foreignMasterPortId = fmpi;}

void Foreign::set_foreignMasterSyncs(UInteger16 fms)
{foreignMasterSyncs = fms;}

Foreign &Foreign::operator=(const Foreign & other_t)
{
	returnedPortNumber = other_t.returnedPortNumber;
	returnedRecordNumber = other_t.returnedRecordNumber;
	foreignMasterCommunicationTechnology = other_t.foreignMasterCommunicationTechnology;
	memcpy(foreignMasterUuid,other_t.foreignMasterUuid,strlen(other_t.foreignMasterUuid));
	foreignMasterPortId = other_t.foreignMasterPortId;
	foreignMasterSyncs = other_t.foreignMasterSyncs;

	return *this;
}
ostream& operator<<(ostream& s, const Foreign& it)
{
        cout << "returned port number : " << it.returnedPortNumber << endl;
	cout << "returned record number: " << it.returnedRecordNumber << endl;

        return s;
}

