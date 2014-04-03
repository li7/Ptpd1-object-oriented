#ifndef FOREIGNMASTERRECORD_H
#define FOREIGNMASTERRECORD_H
#include "MsgHeader.h"
#include "MsgSync.h"
#include "constants.h"
#include <iostream>

using namespace std;

class ForeignMasterRecord{

public:

	/*************Constructor************/
	ForeignMasterRecord();

	/****************accessors***********/
	UInteger8 get_foreign_master_communication_technology() const;
	Octet* get_foreign_master_uuid();
	UInteger16 get_foreign_master_port_id() const;
	UInteger16 get_foreign_master_syncs() const;
	MsgHeader& get_header();
	MsgSync& get_sync();

	/****************mutators***********/
	void set_foreign_master_communication_technology(UInteger8 fmct);
	void set_foreign_master_uuid(Octet *fmu, int length);
	void set_foreign_master_port_id(UInteger16 fmpi);
	void set_foreign_master_syncs(UInteger16 fms);
	void set_header(MsgHeader head);
	void set_sync(MsgSync syn);

        friend ostream& operator<<(ostream& s, const ForeignMasterRecord& it);


private:
	UInteger8 foreign_master_communication_technology;
	Octet foreign_master_uuid[PTP_UUID_LENGTH];
	UInteger16 foreign_master_port_id;
	UInteger16 foreign_master_syncs;
	MsgHeader header;
	MsgSync sync;
};

ostream& operator<<(ostream& s, const ForeignMasterRecord& it);

#endif
