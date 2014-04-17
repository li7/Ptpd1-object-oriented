#include "ClockIdentity.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
ClockIdentity::ClockIdentity()
{
	clockCommunicationTechnology = 0;
        memset(&clockUuidField,0,PTP_UUID_LENGTH);
        clockPortField = 0;
        memset(&manufacturerIdentity,0,MANUFACTURER_ID_LENGTH);
}

/*****************accessors***************/
UInteger8 ClockIdentity::get_clockCommunicationTechnology() const
{return clockCommunicationTechnology;}

Octet ClockIdentity::get_clockUuidField() const
{return *clockUuidField;}

Octet ClockIdentity::get_clockUuidField(int position) const
{return clockUuidField[position];}

UInteger16 ClockIdentity::get_clockPortField() const
{return clockPortField;}

Octet ClockIdentity::get_manufacturerIdentity() const
{return *manufacturerIdentity;}

Octet ClockIdentity::get_manufacturerIdentity(int position) const
{return manufacturerIdentity[position];}

/****************mutators******************/
void ClockIdentity::set_clockCommunicationTechnology(UInteger8 cct)
{clockCommunicationTechnology = cct;}

void ClockIdentity::set_clockUuidField(const void *cuf, int length)
{memcpy(clockUuidField,cuf,length);}

void ClockIdentity::set_clockPortField(UInteger16 cpf)
{clockPortField = cpf;}

void ClockIdentity::set_manufacturerIdentity(const void *mi, int length)
{memcpy(manufacturerIdentity,mi,length);}

ClockIdentity &ClockIdentity::operator=(const ClockIdentity & other_t)
{
	clockCommunicationTechnology = other_t.clockCommunicationTechnology;
	memcpy(clockUuidField,other_t.clockUuidField,strlen(other_t.clockUuidField));
	clockPortField = other_t.clockPortField;
	memcpy(manufacturerIdentity,other_t.manufacturerIdentity,strlen(other_t.manufacturerIdentity));
	return *this;
}

ostream& operator<<(ostream& s, const ClockIdentity& it)
{
        cout <<"clockCommunicationTechnology : " << it.clockCommunicationTechnology << endl;
	cout << "clockPortField: " << it.clockPortField << endl;
	cout << "clockUuidField: " << it.clockUuidField << endl;

        return s;
}

