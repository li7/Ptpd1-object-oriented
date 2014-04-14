#ifndef PORT_H
#define PORT_H
#include "constants.h"
#include "datatypes_dep.h"
#include <iostream>
#include "constants_dep.h"

using namespace std;

class Port{

public:

	/*************Constructor************/
	Port();

	/****************accessors***********/
	UInteger16 get_returnedPortNumber() const;
	UInteger8 get_portState() const;
	UInteger16 get_lastSyncEventSequenceNumber() const;
	UInteger16 get_lastGeneralEventSequenceNumber() const;
	UInteger8 get_portCommunicationTechnology() const;
	Octet get_portUuidField() const;
	Octet get_portUuidField(int i) const;
	UInteger16 get_portIdField() const;
	Boolean get_burstEnabled() const;
	UInteger8 get_subdomainAddressOctets() const;
	UInteger8 get_eventPortAddressOctets() const;
	UInteger8 get_generalPortAddressOctets() const;
	Octet get_subdomainAddress() const;
	Octet get_subdomainAddress(int i) const;
	Octet get_eventPortAddress() const;
	Octet get_eventPortAddress(int i) const;
	Octet get_generalPortAddress() const;
	Octet get_generalPortAddress(int i) const;

	/****************mutators***********/
	void set_returnedPortNumber(UInteger16 rpn);
	void set_portState(UInteger8 ps);
	void set_lastSyncEventSequenceNumber(UInteger16 lsesn);
	void set_lastGeneralEventSequenceNumber(UInteger16 lgesn);
	void set_portCommunicationTechnology(UInteger8 pct);
	void set_portUuidField(const void *puf, int length);
	void set_portIdField(UInteger16 pif);
	void set_burstEnabled(Boolean be);
	void set_subdomainAddressOctets(UInteger8 sao);
	void set_eventPortAddressOctets(UInteger8 epao);
	void set_generalPortAddressOctets(UInteger8 gpao);
	void set_subdomainAddress(const void *sa, int length);
	void set_eventPortAddress(const void *epa, int length);
	void set_generalPortAddress(const void *gpa, int length);

	Port &operator=(const Port & other_t);

        friend ostream& operator<<(ostream& s, const Port& it);


private:
	UInteger16 returnedPortNumber;
	UInteger8 portState;
	UInteger16 lastSyncEventSequenceNumber;
	UInteger16 lastGeneralEventSequenceNumber;
	UInteger8 portCommunicationTechnology;
	Octet   portUuidField[PTP_UUID_LENGTH];
	UInteger16 portIdField;
	Boolean burstEnabled;
	UInteger8 subdomainAddressOctets;
	UInteger8 eventPortAddressOctets;
	UInteger8 generalPortAddressOctets;
	Octet   subdomainAddress[SUBDOMAIN_ADDRESS_LENGTH];
	Octet   eventPortAddress[PORT_ADDRESS_LENGTH];
	Octet   generalPortAddress[PORT_ADDRESS_LENGTH];
};

ostream& operator<<(ostream& s, const Port& it);

#endif
