#ifndef FOREIGN_H
#define FOREIGN_H
#include "constants.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class Foreign{

public:

	/*************Constructor************/
	Foreign();

	/****************accessors***********/
	UInteger16 get_returnedPortNumber() const;
	UInteger16 get_returnedRecordNumber() const;
	UInteger8 get_foreignMasterCommunicationTechnology() const;
	Octet get_foreignMasterUuid() const;
	Octet get_foreignMasterUuid(int i) const;
	UInteger16 get_foreignMasterPortId() const;
	UInteger16 get_foreignMasterSyncs() const;

	/****************mutators***********/
	void set_returnedPortNumber(UInteger16 rpn);
	void set_returnedRecordNumber(UInteger16 rrn);
	void set_foreignMasterCommunicationTechnology(UInteger8 fmct);
	void set_foreignMasterUuid(const void *fmu, int length);
	void set_foreignMasterPortId(UInteger16 fmpi);
	void set_foreignMasterSyncs(UInteger16 fms);

	Foreign &operator=(const Foreign & other_t);

        friend ostream& operator<<(ostream& s, const Foreign& it);


private:
	UInteger16 returnedPortNumber;
	UInteger16 returnedRecordNumber;
	UInteger8 foreignMasterCommunicationTechnology;
	Octet   foreignMasterUuid[PTP_UUID_LENGTH];
	UInteger16 foreignMasterPortId;
	UInteger16 foreignMasterSyncs;
};

ostream& operator<<(ostream& s, const Foreign& it);

#endif
