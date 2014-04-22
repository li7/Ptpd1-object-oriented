#include "MsgDelayResp.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
MsgDelayResp::MsgDelayResp()
{
}

/*****************accessors***************/
TimeRepresentation& MsgDelayResp::get_delayReceiptTimestamp()
{return delayReceiptTimestamp;}

UInteger32 MsgDelayResp::get_delayReceiptTimestamp_seconds() const
{return delayReceiptTimestamp.get_seconds();}

Integer32 MsgDelayResp::get_delayReceiptTimestamp_nanoseconds() const
{return delayReceiptTimestamp.get_nanoseconds();}

UInteger8 MsgDelayResp::get_requestingSourceCommunicationTechnology() const
{return requestingSourceCommunicationTechnology;}

Octet* MsgDelayResp::get_requestingSourceUuid()
{return requestingSourceUuid;}

UInteger16 MsgDelayResp::get_requestingSourcePortId() const
{return requestingSourcePortId;}

UInteger16 MsgDelayResp::get_requestingSourceSequenceId() const
{return requestingSourceSequenceId;}

/****************mutators******************/
void MsgDelayResp::set_delayReceiptTimestamp(TimeRepresentation drt)
{delayReceiptTimestamp = drt;}

void MsgDelayResp::set_delayReceiptTimestamp_seconds(UInteger32 sec)
{delayReceiptTimestamp.set_seconds(sec);}

void MsgDelayResp::set_delayReceiptTimestamp_nanoseconds(Integer32 nsec)
{delayReceiptTimestamp.set_nanoseconds(nsec);}

void MsgDelayResp::set_requestingSourceCommunicationTechnology(UInteger8 rsct)
{requestingSourceCommunicationTechnology = rsct;}

void MsgDelayResp::set_requestingSourceUuid(const void *rsu, int length)
{memcpy(requestingSourceUuid,rsu,length);}

void MsgDelayResp::set_requestingSourcePortId(UInteger16 rspi)
{requestingSourcePortId = rspi;}

void MsgDelayResp::set_requestingSourceSequenceId(UInteger16 rssi)
{requestingSourceSequenceId = rssi;}

ostream& operator<<(ostream& s, const MsgDelayResp& it)
{
        cout << "delayReceiptTimestamp : " << it.delayReceiptTimestamp << endl;
        cout <<" requestSourceComTech : " << it.requestingSourceCommunicationTechnology << endl;
        cout << "sourceUuid : " << it.requestingSourceUuid << endl;
        cout <<"sourcePortId : " << it.requestingSourcePortId << endl;
        cout <<"sourceSequenceId : " << it.requestingSourceSequenceId << endl;
        return s;
}

