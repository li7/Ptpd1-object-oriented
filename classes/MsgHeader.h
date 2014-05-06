#ifndef MSGHEADER_H
#define MSGHEADER_H
#include "datatypes_dep.h"
#include "constants.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
#include <iostream>

using namespace std;

class MsgHeader {

public: 

	/* constructor */
	MsgHeader();

	/* accessors */
	UInteger16 get_versionPTP() const;
        UInteger16 get_versionNetwork() const;
        Octet*   get_subdomain();
        UInteger8 get_messageType() const;
        UInteger8 get_sourceCommunicationTechnology() const;
        Octet * get_sourceUuid();
        Octet get_sourceUuid(int position);
        UInteger16 get_sourcePortId() const;
        UInteger16 get_sequenceId() const;
        UInteger8 get_control() const;
        Octet * get_flags();

	/* mutators */
	void set_versionPTP(UInteger16 vp);
        void set_versionNetwork(UInteger16 vn);
        void set_subdomain(const void *sd, int length);
        void set_messageType(UInteger8 mt);
        void set_sourceCommunicationTechnology(UInteger8 sct);
        void set_sourceUuid(const void *su,int length);
        void set_sourcePortId(UInteger16 spid);
        void set_sequenceId(UInteger16 sid);
        void set_control(UInteger8 c);
        void set_flags(const void *f, int length);

	/* operators */
	MsgHeader &operator=(const MsgHeader & other_t);
        friend ostream& operator<<(ostream& s, const MsgHeader& it);

private:
	    UInteger16 versionPTP;
            UInteger16 versionNetwork;
            Octet subdomain[PTP_SUBDOMAIN_NAME_LENGTH];
            UInteger8 messageType;
            UInteger8 sourceCommunicationTechnology;
            Octet sourceUuid[PTP_UUID_LENGTH];
            UInteger16 sourcePortId;
            UInteger16 sequenceId;
            UInteger8 control;
            Octet flags[2];
};

ostream& operator<<(ostream& s, const MsgHeader& it);
#endif
