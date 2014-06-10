#include "PtpClock.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
PtpClock::PtpClock()
{
	netPath;
}

/*****************accessors***************/
UInteger8 PtpClock::get_clock_communication_technology() const
{return clock_communication_technology;}

Octet* PtpClock::get_clock_uuid_field()
{return clock_uuid_field;}

UInteger16 PtpClock::get_clock_port_id_field() const
{return clock_port_id_field;}

UInteger8 PtpClock::get_clock_stratum() const
{return clock_stratum;}

Octet* PtpClock::get_clock_identifier()
{return clock_identifier;}

Integer16 PtpClock::get_clock_variance() const
{return clock_variance;}

Boolean PtpClock::get_clock_followup_capable() const
{return clock_followup_capable;}

Boolean PtpClock::get_preferred() const
{return preferred;}

Boolean PtpClock::get_initializable() const
{return initializable;}

Boolean PtpClock::get_external_timing() const
{return external_timing;}

Boolean PtpClock::get_is_boundary_clock() const
{return is_boundary_clock;}

Integer8 PtpClock::get_sync_interval() const
{return sync_interval;}

Octet* PtpClock::get_subdomain_name()
{return subdomain_name;}

UInteger16 PtpClock::get_number_ports() const
{return number_ports;}

UInteger16 PtpClock::get_number_foreign_records() const
{return number_foreign_records;}

UInteger16 PtpClock::get_steps_removed() const
{return steps_removed;}

TimeInternal& PtpClock::get_offset_from_master()
{return offset_from_master;}

UInteger32 PtpClock::get_offset_from_master_seconds() const
{return offset_from_master.get_seconds();}

Integer32 PtpClock::get_offset_from_master_nanoseconds() const
{return offset_from_master.get_nanoseconds();}

TimeInternal& PtpClock::get_one_way_delay() 
{return one_way_delay;}

UInteger32 PtpClock::get_one_way_delay_seconds() 
{return one_way_delay.get_seconds();}

Integer32 PtpClock::get_one_way_delay_nanoseconds() 
{return one_way_delay.get_nanoseconds();}

UInteger8 PtpClock::get_parent_communication_technology() const
{return parent_communication_technology;}

Octet* PtpClock::get_parent_uuid()
{return parent_uuid;}

UInteger16 PtpClock::get_parent_port_id() const
{return parent_port_id;}

UInteger16 PtpClock::get_parent_last_sync_sequence_number() const
{return parent_last_sync_sequence_number;}

Boolean PtpClock::get_parent_followup_capable() const
{return parent_followup_capable;}

Boolean PtpClock::get_parent_external_timing() const
{return parent_external_timing;}

Integer16 PtpClock::get_parent_variance() const
{return parent_variance;}

Boolean PtpClock::get_parent_stats() const
{return parent_stats;}

Integer16 PtpClock::get_observed_variance() const
{return observed_variance;}

Integer32 PtpClock::get_observed_drift() const
{return observed_drift;}

Boolean PtpClock::get_utc_reasonable() const
{return utc_reasonable;}

UInteger8 PtpClock::get_grandmaster_communication_technology() const
{return grandmaster_communication_technology;}

Octet* PtpClock::get_grandmaster_uuid_field()
{return grandmaster_uuid_field;}

UInteger16 PtpClock::get_grandmaster_port_id_field() const
{return grandmaster_port_id_field;}

UInteger8 PtpClock::get_grandmaster_stratum() const
{return grandmaster_stratum;}

Octet* PtpClock::get_grandmaster_identifier()
{return grandmaster_identifier;}

Integer16 PtpClock::get_grandmaster_variance() const
{return grandmaster_variance;}

Boolean PtpClock::get_grandmaster_preferred() const
{return grandmaster_preferred;}

Boolean PtpClock::get_grandmaster_is_boundary_clock() const
{return grandmaster_is_boundary_clock;}

UInteger16 PtpClock::get_grandmaster_sequence_number() const
{return grandmaster_sequence_number;}

Integer16 PtpClock::get_current_utc_offset() const
{return current_utc_offset;}

Boolean PtpClock::get_leap59() const
{return leap_59;}

Boolean PtpClock::get_leap61() const
{return leap_61;}

UInteger16 PtpClock::get_epoch_number() const
{return epoch_number;}

UInteger8 PtpClock::get_port_state() const
{return port_state;}

UInteger16 PtpClock::get_last_sync_event_sequence_number() const
{return last_sync_event_sequence_number;}

UInteger16 PtpClock::get_last_general_event_sequence_number() const
{return last_general_event_sequence_number;}

Octet* PtpClock::get_subdomain_address()
{return subdomain_address;}

Octet PtpClock::get_subdomain_address(int i)
{return subdomain_address[i];}

Octet* PtpClock::get_event_port_address()
{return event_port_address;}

Octet PtpClock::get_event_port_address(int i)
{return event_port_address[i];}

Octet* PtpClock::get_general_port_address()
{return general_port_address;}

Octet PtpClock::get_general_port_address(int i)
{return general_port_address[i];}

UInteger8& PtpClock::get_port_communication_technology()
{return port_communication_technology;}

Octet* PtpClock::get_port_uuid_field()
{return port_uuid_field;}

Octet PtpClock::get_port_uuid_field(int position) const
{return port_uuid_field[position];}

UInteger16 PtpClock::get_port_id_field() const
{return port_id_field;}

Boolean PtpClock::get_burst_enabled() const
{return burst_enabled;}

ForeignMasterRecord& PtpClock::get_foreign()
{return *foreign;}

ForeignMasterRecord& PtpClock::get_foreign(int i)
{return foreign[i];}

Boolean& PtpClock::get_halfEpoch()
{return halfEpoch;}

Integer16 PtpClock::get_max_foreign_records() const
{return max_foreign_records;}

Integer16 PtpClock::get_foreign_record_i() const
{return foreign_record_i;}

Integer16 PtpClock::get_foreign_record_best() const
{return foreign_record_best;}

Boolean PtpClock::get_record_update() const
{return record_update;}

UInteger32& PtpClock::get_random_seed()
{return random_seed;}

MsgHeader& PtpClock::get_msgTmpHeader()
{return msgTmpHeader;}

msgTmp& PtpClock::get_msgtmp()
{return msgtmp;}

MsgSync& PtpClock::get_msgtmp_sync()
{return msgtmp.get_sync();}

Octet* PtpClock::get_msgObuf()
{return msgObuf;}

Octet* PtpClock::get_msgIbuf()
{return msgIbuf;}

TimeInternal& PtpClock::get_master_to_slave_delay()
{return master_to_slave_delay;}

UInteger32 PtpClock::get_master_to_slave_delay_seconds()
{return master_to_slave_delay.get_seconds();}

Integer32 PtpClock::get_master_to_slave_delay_nanoseconds()
{return master_to_slave_delay.get_nanoseconds();}

TimeInternal& PtpClock::get_slave_to_master_delay()
{return slave_to_master_delay;}

UInteger32 PtpClock::get_slave_to_master_delay_seconds()
{return slave_to_master_delay.get_seconds();}

Integer32 PtpClock::get_slave_to_master_delay_nanoseconds()
{return slave_to_master_delay.get_nanoseconds();}

TimeInternal& PtpClock::get_delay_req_receive_time()
{return delay_req_receive_time;}

TimeInternal& PtpClock::get_delay_req_send_time()
{return delay_req_send_time;}

TimeInternal& PtpClock::get_sync_receive_time()
{return sync_receive_time;}

UInteger16 PtpClock::get_Q() const
{return Q;}

UInteger16 PtpClock::get_R() const
{return R;}

Boolean PtpClock::get_sentDelayReq() const
{return sentDelayReq;}

UInteger16 PtpClock::get_sentDelayReqSequenceId() const
{return sentDelayReqSequenceId;}

Boolean PtpClock::get_waitingForFollow() const
{return waitingForFollow;}

offset_from_master_filter& PtpClock::get_ofm_filt()
{return ofm_filt;}

one_way_delay_filter& PtpClock::get_owd_filt()
{return owd_filt;}

Boolean PtpClock::get_message_activity() const
{return message_activity;}

IntervalTimer& PtpClock::get_itimer()
{return *itimer;}

NetPath& PtpClock::get_netPath()
{return netPath;}

bool PtpClock::get_flag()
{return flag;}

/****************mutators******************/
void PtpClock::set_clockCommunicationTechnology(UInteger8 cct)
{clock_communication_technology = cct;}

void PtpClock::set_clockUuidField(Octet *cuf, int length)
{memcpy(clock_uuid_field,cuf,length);}

void PtpClock::set_clockPortField(UInteger16 cpf)
{clock_port_id_field = cpf;}

void PtpClock::set_clockStratum(UInteger8 cs)
{clock_stratum = cs;}

void PtpClock::set_clockIdentifier(const void *ci, int length)
{memcpy(clock_identifier,ci,length);}

void PtpClock::set_clockVariance(Integer16 cv)
{clock_variance = cv;}

void PtpClock::set_clockFollowupCapable(Boolean cfc)
{clock_followup_capable = cfc;}

void PtpClock::set_preferred(Boolean p)
{preferred = p;}

void PtpClock::set_initializable(Boolean i)
{initializable = i;}

void PtpClock::set_externalTiming(Boolean i)
{external_timing = i;}

void PtpClock::set_isBoundaryClock(Boolean ibc)
{is_boundary_clock = ibc;}

void PtpClock::set_syncInterval(Integer8 si)
{sync_interval = si;}

void PtpClock::set_subdomainName(Octet *sn, int length)
{memcpy(subdomain_name,sn,length);}

void PtpClock::set_numberPorts(UInteger16 np)
{number_ports = np;}

void PtpClock::set_numberForeignRecords(UInteger16 nfr)
{number_foreign_records = nfr;}

void PtpClock::set_stepsRemoved(UInteger16 sr)
{steps_removed = sr;}

void PtpClock::set_offsetFromMaster(TimeInternal ofm)
{offset_from_master = ofm;}

void PtpClock::set_offsetFromMaster_seconds(UInteger32 sec)
{offset_from_master.set_seconds(sec);}

void PtpClock::set_offsetFromMaster_nanoseconds(Integer32 nsec)
{offset_from_master.set_nanoseconds(nsec);}

void PtpClock::set_oneWayDelay(TimeInternal owd)
{one_way_delay = owd;}

void PtpClock::set_oneWayDelay_seconds(UInteger32 sec)
{one_way_delay.set_seconds(sec);}

void PtpClock::set_oneWayDelay_nanoseconds(Integer32 nsec)
{one_way_delay.set_nanoseconds(nsec);}

void PtpClock::set_parentCommunicationTechnology(UInteger8 pct)
{parent_communication_technology = pct;}

void PtpClock::set_parentUuid(Octet *pu, int length)
{memcpy(parent_uuid,pu,length);}

void PtpClock::set_parentPortId(UInteger16 ppi)
{parent_port_id = ppi;}

void PtpClock::set_parentLastSyncSequenceNumber(UInteger16 plss)
{parent_last_sync_sequence_number = plss;}

void PtpClock::set_parentFollowupCapable(Boolean pfc)
{parent_followup_capable = pfc;}

void PtpClock::set_parentExternalTiming(Boolean pet)
{parent_external_timing = pet;}

void PtpClock::set_parentVariance(Integer16 pv)
{parent_variance = pv;}

void PtpClock::set_parentStats(Boolean ps)
{parent_stats = ps;}

void PtpClock::set_observedVariance(Integer16 ov)
{observed_variance = ov;}

void PtpClock::set_observedDrift(Integer32 od)
{observed_drift = od;}

void PtpClock::set_utcReasonable(Boolean ur)
{utc_reasonable = ur;}

void PtpClock::set_grandmasterCommunicationTechnology(UInteger8 gct)
{grandmaster_communication_technology = gct;}

void PtpClock::set_grandmasterUuidField(Octet *guf, int length)
{memcpy(grandmaster_uuid_field,guf,length);}

void PtpClock::set_grandmasterPortIdField(UInteger16 gpf)
{grandmaster_port_id_field = gpf;}

void PtpClock::set_grandmasterStratum(UInteger8 gs)
{grandmaster_stratum = gs;}

void PtpClock::set_grandmasterIdentifier(Octet *gi, int length)
{memcpy(grandmaster_identifier,gi,length);}

void PtpClock::set_grandmasterVariance(Integer16 gv)
{grandmaster_variance = gv;}

void PtpClock::set_grandmasterPreferred(Boolean gp)
{grandmaster_preferred = gp;}

void PtpClock::set_grandmasterIsBoundaryClock(Boolean gibc)
{grandmaster_is_boundary_clock = gibc;}

void PtpClock::set_grandmasterSequenceNumber(UInteger16 gsn)
{grandmaster_sequence_number = gsn;}

void PtpClock::set_currentUtcOffset(Integer16 cuo)
{current_utc_offset = cuo;}

void PtpClock::set_leap59(Boolean l59)
{leap_59 = l59;}

void PtpClock::set_leap61(Boolean l61)
{leap_61 = l61;}

void PtpClock::set_epochNumber(UInteger16 en)
{epoch_number = en;}

void PtpClock::set_portState(UInteger8 ps)
{port_state = ps;}

void PtpClock::set_lastSyncEventSequenceNumber(UInteger16 lsesn)
{last_sync_event_sequence_number = lsesn;}

void PtpClock::set_lastGeneralEventSequenceNumber(UInteger16 lgesn)
{last_general_event_sequence_number = lgesn;}

void PtpClock::set_subdomainAddress(Octet *sa, int length)
{memcpy(subdomain_address,sa,length);}

void PtpClock::set_subdomainAddress(int i, Octet sa)
{subdomain_address[i] = sa;}

/*void PtpClock::set_eventPortAddress(Octet *epa, int length)
{memcpy(event_port_address,epa,length);}
*/
void PtpClock::set_eventPortAddress(Octet length)
{memset(event_port_address,length,PORT_ADDRESS_LENGTH);
}
/*
void PtpClock::set_generalPortAddress(Octet *gpa, int length)
{memcpy(general_port_address,gpa,length);}
*/
void PtpClock::set_generalPortAddress(Octet length)
{memset(general_port_address,length,PORT_ADDRESS_LENGTH);
}

void PtpClock::set_portCommunicationTechnology(UInteger8 pct)
{port_communication_technology = pct;}

void PtpClock::set_portUuidField(Octet *puf, int length)
{memcpy(port_uuid_field,puf,length);}

void PtpClock::set_portIdField(UInteger16 pif)
{port_id_field = pif;}

void PtpClock::set_burstEnabled(Boolean be)
{burst_enabled = be;}

/*void PtpClock::set_foreign(ForeignMasterRecord *f)
{foreign = f;
if (f == NULL) flag = false;
else flag = true;}
*/

void PtpClock::set_foreign(int x)
{foreign = (ForeignMasterRecord *) calloc(x,sizeof(ForeignMasterRecord));
if (foreign == NULL) flag = false;
else flag = true;}

void PtpClock::free_foreign()
{free(foreign);}

void PtpClock::set_halfEpoch(Boolean he)
{halfEpoch = he;}

void PtpClock::set_max_foreign_records(Integer16 mfr)
{max_foreign_records = mfr;}

void PtpClock::set_foreign_record_i(Integer16 fri)
{foreign_record_i = fri;}

void PtpClock::set_foreign_record_best(Integer16 frb)
{foreign_record_best = frb;}

void PtpClock::set_record_update(Boolean ru)
{record_update = ru;}

void PtpClock::set_random_seed(UInteger32 rs)
{random_seed = rs;}

void PtpClock::set_msgTmpHeader(MsgHeader mth)
{msgTmpHeader = mth;}

void PtpClock::set_msgtmp(msgTmp mt)
{msgtmp= mt;}

void PtpClock::set_msgObuf(Octet *mob, int length)
{memcpy(msgObuf,mob,length);}

void PtpClock::set_msgIbuf(Octet *mib, int length)
{memcpy(msgIbuf,mib,length);}

void PtpClock::set_master_to_slave_delay(TimeInternal mtsd)
{master_to_slave_delay = mtsd;}

void PtpClock::set_master_to_slave_delay_seconds(UInteger32 sec)
{master_to_slave_delay.set_seconds(sec);}

void PtpClock::set_master_to_slave_delay_nanoseconds(Integer32 nsec)
{master_to_slave_delay.set_nanoseconds(nsec);}

void PtpClock::set_slave_to_master_delay(TimeInternal stmd)
{slave_to_master_delay = stmd;}

void PtpClock::set_slave_to_master_delay_seconds(UInteger32 sec)
{slave_to_master_delay.set_seconds(sec);}

void PtpClock::set_slave_to_master_delay_nanoseconds(Integer32 nsec)
{slave_to_master_delay.set_nanoseconds(nsec);}

void PtpClock::set_delay_req_receive_time(TimeInternal drrt)
{delay_req_receive_time = drrt;}

void PtpClock::set_delay_req_send_time(TimeInternal drst)
{delay_req_send_time = drst;}

void PtpClock::set_sync_receive_time(TimeInternal srt)
{sync_receive_time = srt;}

void PtpClock::set_Q(UInteger16 q)
{Q = q;}

void PtpClock::set_R(UInteger16 r)
{R = r;}

void PtpClock::set_sentDelayReq(Boolean sdr)
{sentDelayReq = sdr;}

void PtpClock::set_sentDelayReqSequenceId(UInteger16 sdrsi)
{sentDelayReqSequenceId = sdrsi;}

void PtpClock::set_waitingForFollow(Boolean wff)
{waitingForFollow = wff;}

void PtpClock::set_ofm_filt(offset_from_master_filter of)
{ofm_filt = of;}

void PtpClock::set_owd_filt(one_way_delay_filter of)
{owd_filt = of;}

void PtpClock::set_owd_filt_s_exp(Integer32 s)
{owd_filt.set_s_exp(s);}

void PtpClock::set_message_activity(Boolean ma)
{message_activity = ma;}

void PtpClock::set_itimer(IntervalTimer *i, int length)
{memcpy(itimer,i,length);}

void PtpClock::set_netPath(NetPath np)
{netPath = np;}

ostream& operator<<(ostream& s, const PtpClock& it)
{
	cout << "port Uuid field: " << it.port_uuid_field << endl;
	cout << "offset from master: " << it.offset_from_master << endl;
        return s;
}

