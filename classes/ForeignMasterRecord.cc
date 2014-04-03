#include "ForeignMasterRecord.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
ForeignMasterRecord::ForeignMasterRecord()
{
}

/*****************accessors***************/
UInteger8 ForeignMasterRecord::get_foreign_master_communication_technology() const
{return foreign_master_communication_technology;}

Octet* ForeignMasterRecord::get_foreign_master_uuid()
{return foreign_master_uuid;}

UInteger16 ForeignMasterRecord::get_foreign_master_port_id() const
{return foreign_master_port_id;}

UInteger16 ForeignMasterRecord::get_foreign_master_syncs() const
{return foreign_master_syncs;}

MsgHeader& ForeignMasterRecord::get_header()
{return header;}

MsgSync& ForeignMasterRecord::get_sync()
{return sync;}

/****************mutators******************/
void ForeignMasterRecord::set_foreign_master_communication_technology(UInteger8 fmct)
{foreign_master_communication_technology = fmct;}

void ForeignMasterRecord::set_foreign_master_uuid(Octet *fmu, int length)
{memcpy(foreign_master_uuid,fmu,length);}

void ForeignMasterRecord::set_foreign_master_port_id(UInteger16 fmpi)
{foreign_master_port_id = fmpi;}

void ForeignMasterRecord::set_foreign_master_syncs(UInteger16 fms)
{foreign_master_syncs = fms;}

void ForeignMasterRecord::set_header(MsgHeader head)
{header = head;}

void ForeignMasterRecord::set_sync(MsgSync syn)
{sync = syn;}

ostream& operator<<(ostream& s, const ForeignMasterRecord& it)
{
	cout << "foreign master communication technology: " << it.foreign_master_communication_technology << endl;
	cout << "foreign master uuid: " << it.foreign_master_uuid << endl;

        return s;
}

