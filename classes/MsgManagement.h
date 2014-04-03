#ifndef MSGMANAGEMENT_H
#define MSGMANAGEMENT_H
#include "MsgManagementPayload.h"
#include "constants.h"
#include <iostream>

using namespace std;

class MsgManagement{

public:

	/*************Constructor************/
	MsgManagement();

	/****************accessors***********/
	UInteger8 get_targetCommunicationTechnology() const;
	Octet* get_targetUuid();
	UInteger16 get_targetPortId() const;
	Integer16 get_startingBoundaryHops() const;
	Integer16 get_boundaryHops() const;
	UInteger8 get_managementMessageKey() const;
	UInteger16 get_parameterLength() const;
	UInteger16 get_recordKey() const;

	MsgManagementPayload get_payload() const;

	/****************mutators***********/
	void set_targetCommunicationTechnology(UInteger8 tct);
	void set_targetUuid(const void *tu, int length);
	void set_targetPortId(UInteger16 tpi);
	void set_startingBoundaryHops(Integer16 sbh);
	void set_boundaryHops(Integer16 bh);
	void set_managementMessageKey(UInteger8 mmk);
	void set_parameterLength(UInteger16 pl);
	void set_recordKey(UInteger16 rk);
	
	void set_payload(MsgManagementPayload p);

	MsgManagement &operator=(const MsgManagement & other_t);
        friend ostream& operator<<(ostream& s, const MsgManagement& it);


private:
        UInteger8 targetCommunicationTechnology;
        Octet   targetUuid[PTP_UUID_LENGTH];
        UInteger16 targetPortId;
        Integer16 startingBoundaryHops;
        Integer16 boundaryHops;
        UInteger8 managementMessageKey;
        UInteger16 parameterLength;
        UInteger16 recordKey;

        MsgManagementPayload payload;
};

ostream& operator<<(ostream& s, const MsgManagement& it);

#endif
