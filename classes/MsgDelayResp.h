#ifndef MSGDELAYRESP_H
#define MSGDELAYRESP_H
#include "TimeRepresentation.h"
#include "constants.h"
#include <iostream>

using namespace std;

class MsgDelayResp{

public:

	/*************Constructor************/
	MsgDelayResp();

	/****************accessors***********/
	TimeRepresentation& get_delayReceiptTimestamp();
	UInteger32 get_delayReceiptTimestamp_seconds() const;
	Integer32 get_delayReceiptTimestamp_nanoseconds() const;
	UInteger8 get_requestingSourceCommunicationTechnology() const;
	Octet* get_requestingSourceUuid();
	UInteger16 get_requestingSourcePortId() const;
	UInteger16 get_requestingSourceSequenceId() const;

	/****************mutators***********/
	void set_delayReceiptTimestamp(TimeRepresentation drt);
	void set_delayReceiptTimestamp_seconds(UInteger32 sec);
	void set_delayReceiptTimestamp_nanoseconds(Integer32 nsec);
	void set_requestingSourceCommunicationTechnology(UInteger8 rsct);
	void set_requestingSourceUuid(const void *rsu, int length);
	void set_requestingSourcePortId(UInteger16 rspi);
	void set_requestingSourceSequenceId(UInteger16 rssi);

        friend ostream& operator<<(ostream& s, const MsgDelayResp& it);


private:
	TimeRepresentation delayReceiptTimestamp;
	UInteger8 requestingSourceCommunicationTechnology;
	Octet requestingSourceUuid[PTP_UUID_LENGTH];
	UInteger16 requestingSourcePortId;
	UInteger16 requestingSourceSequenceId;
};

ostream& operator<<(ostream& s, const MsgDelayResp& it);

#endif
