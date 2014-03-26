#ifndef CLOCKIDENTITY_H
#define CLOCKIDENTITY_H
#include "constants.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class ClockIdentity{

public:

	/*************Constructor************/
	ClockIdentity();

	/****************accessors***********/
	UInteger8 get_clockCommunicationTechnology() const;
	Octet get_clockUuidField() const;
	UInteger16 get_clockPortField() const;
	Octet get_manufacturerIdentity() const;

	/****************mutators***********/
	void set_clockCommunicationTechnology(UInteger8 cct);
	void set_clockUuidField(Octet *cuf, int length);
	void set_clockPortField(UInteger16 cpf );
	void set_manufacturerIdentity(Octet *mi, int length);

	ClockIdentity &operator=(const ClockIdentity & other_t);

        friend ostream& operator<<(ostream& s, const ClockIdentity& it);


private:
	UInteger8 clockCommunicationTechnology;
	Octet clockUuidField[PTP_UUID_LENGTH];
	UInteger16 clockPortField;
	Octet manufacturerIdentity[MANUFACTURER_ID_LENGTH];
};

ostream& operator<<(ostream& s, const ClockIdentity& it);

#endif
