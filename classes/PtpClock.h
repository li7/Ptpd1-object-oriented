#ifndef PTPCLOCK_H
#define PTPCLOCK_H
#include "TimeInternal.h"
#include "MsgHeader.h"
#include "IntervalTimer.h"
#include "NetPath.h"
#include "offset_from_master_filter.h"
#include "one_way_delay_filter.h"
#include "ForeignMasterRecord.h"
#include "msgTmp.h"
#include "constants.h"
#include "constants_dep.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class PtpClock{

public:

        ForeignMasterRecord *foreign;
	/*************Constructor************/
	PtpClock();

	/****************accessors***********/
	/*Default Data set*/
        UInteger8 get_clock_communication_technology() const;
        Octet* get_clock_uuid_field();
        UInteger16 get_clock_port_id_field() const;
        UInteger8 get_clock_stratum() const;
        Octet* get_clock_identifier();
        Integer16 get_clock_variance() const;
        Boolean get_clock_followup_capable() const;
        Boolean get_preferred() const;
        Boolean get_initializable() const;
        Boolean get_external_timing() const;
        Boolean get_is_boundary_clock() const;
        Integer8 get_sync_interval() const;
        Octet* get_subdomain_name();
        UInteger16 get_number_ports() const;
        UInteger16 get_number_foreign_records() const;

	/*Current data set*/
        UInteger16 get_steps_removed() const;
        TimeInternal& get_offset_from_master();
        UInteger32 get_offset_from_master_seconds() const;
        Integer32 get_offset_from_master_nanoseconds() const;
        TimeInternal& get_one_way_delay();
        UInteger32 get_one_way_delay_seconds();
        Integer32 get_one_way_delay_nanoseconds();

	/*Parent data set*/
        UInteger8 get_parent_communication_technology() const;
        Octet* get_parent_uuid();
        UInteger16 get_parent_port_id() const;
        UInteger16 get_parent_last_sync_sequence_number() const;
        Boolean get_parent_followup_capable() const;
        Boolean get_parent_external_timing() const;
        Integer16 get_parent_variance() const;
        Boolean get_parent_stats() const;
        Integer16 get_observed_variance() const;
        Integer32 get_observed_drift() const;
        Boolean get_utc_reasonable() const;
        UInteger8 get_grandmaster_communication_technology() const;
        Octet* get_grandmaster_uuid_field();
        UInteger16 get_grandmaster_port_id_field() const;
        UInteger8 get_grandmaster_stratum() const;
        Octet* get_grandmaster_identifier();
        Integer16 get_grandmaster_variance() const;
        Boolean get_grandmaster_preferred() const;
        Boolean get_grandmaster_is_boundary_clock() const;
        UInteger16 get_grandmaster_sequence_number() const;

	/*Global time properties data set*/
	Integer16 get_current_utc_offset() const;
        Boolean get_leap59() const;
        Boolean get_leap61() const;
        UInteger16 get_epoch_number() const;

	/*Port configuration data set*/
        UInteger8 get_port_state() const;
        UInteger16 get_last_sync_event_sequence_number() const;
        UInteger16 get_last_general_event_sequence_number() const;
	Octet* get_subdomain_address();
	Octet get_subdomain_address(int i);
	Octet* get_event_port_address();
	Octet get_event_port_address(int i);
	Octet* get_general_port_address();
	Octet get_general_port_address(int i);
        UInteger8& get_port_communication_technology();
        Octet* get_port_uuid_field();
        Octet get_port_uuid_field(int position) const;
        UInteger16 get_port_id_field() const;
        Boolean get_burst_enabled() const;

	/*foreign master record data set*/
	ForeignMasterRecord& get_foreign();
	ForeignMasterRecord& get_foreign(int i);

	/*other*/
	Boolean& get_halfEpoch();
	Integer16 get_max_foreign_records() const;
	Integer16 get_foreign_record_i() const;
	Integer16 get_foreign_record_best() const;
	Boolean get_record_update() const;
	UInteger32& get_random_seed();

	MsgHeader& get_msgTmpHeader();

	msgTmp& get_msgtmp();
	MsgSync& get_msgtmp_sync();

	Octet* get_msgObuf();
	Octet* get_msgIbuf();
	
	TimeInternal& get_master_to_slave_delay();
	UInteger32 get_master_to_slave_delay_seconds();
	Integer32 get_master_to_slave_delay_nanoseconds();
	TimeInternal& get_slave_to_master_delay();
	UInteger32 get_slave_to_master_delay_seconds();
	Integer32 get_slave_to_master_delay_nanoseconds();

	TimeInternal& get_delay_req_receive_time();
	TimeInternal& get_delay_req_send_time();
	TimeInternal& get_sync_receive_time();

	UInteger16 get_Q() const;
	UInteger16 get_R() const;
	
	Boolean get_sentDelayReq() const;
	UInteger16 get_sentDelayReqSequenceId() const;
	Boolean get_waitingForFollow() const;

	offset_from_master_filter& get_ofm_filt();
	one_way_delay_filter& get_owd_filt();

	Boolean get_message_activity() const;

	IntervalTimer& get_itimer();

	NetPath& get_netPath();

	bool get_flag();

	/****************mutators***********/
        void set_clockCommunicationTechnology(UInteger8 cct);
        void set_clockUuidField(Octet *cuf, int length);
        void set_clockPortField(UInteger16 cpf);
        void set_clockStratum(UInteger8 cs);
        void set_clockIdentifier(const void *ci, int length);
        void set_clockVariance(Integer16 cv);
        void set_clockFollowupCapable(Boolean cfc);
        void set_preferred(Boolean p);
        void set_initializable(Boolean i);
        void set_externalTiming(Boolean et);
        void set_isBoundaryClock(Boolean ibc);
        void set_syncInterval(Integer8 si);
        void set_subdomainName(Octet *sn, int length);
        void set_numberPorts(UInteger16 np);
        void set_numberForeignRecords(UInteger16 nfr);
        void set_stepsRemoved(UInteger16 sr);
        void set_offsetFromMaster(TimeInternal ofm);
        void set_offsetFromMaster_seconds(UInteger32 sec);
        void set_offsetFromMaster_nanoseconds(Integer32 sec);
        void set_oneWayDelay(TimeInternal owd);
        void set_oneWayDelay_seconds(UInteger32 sec);
        void set_oneWayDelay_nanoseconds(Integer32 nsec);
        void set_parentCommunicationTechnology(UInteger8 cct);
        void set_parentUuid(Octet *pu, int length);
        void set_parentPortId(UInteger16 ppi);
        void set_parentLastSyncSequenceNumber(UInteger16 plss);
        void set_parentFollowupCapable(Boolean pfc);
        void set_parentExternalTiming(Boolean pet);
        void set_parentVariance(Integer16 pv);
        void set_parentStats(Boolean ps);
        void set_observedVariance(Integer16 ov);
        void set_observedDrift(Integer32 od);
        void set_utcReasonable(Boolean ur);
        void set_grandmasterCommunicationTechnology(UInteger8 gct);
        void set_grandmasterUuidField(Octet *guf, int length);
        void set_grandmasterPortIdField(UInteger16 gpf);
        void set_grandmasterStratum(UInteger8 gs);
        void set_grandmasterIdentifier(Octet *gi, int length);
        void set_grandmasterVariance(Integer16 gv);
        void set_grandmasterPreferred(Boolean gp);
        void set_grandmasterIsBoundaryClock(Boolean gibc);
        void set_grandmasterSequenceNumber(UInteger16 gsn);
        void set_currentUtcOffset(Integer16 cuo);
        void set_leap59(Boolean l59);
        void set_leap61(Boolean l61);
        void set_epochNumber(UInteger16 en);
        void set_portState(UInteger8 ps);
        void set_lastSyncEventSequenceNumber(UInteger16 lsesn);
        void set_lastGeneralEventSequenceNumber(UInteger16 lgesn);
        void set_subdomainAddress(Octet *sa, int length);
        void set_subdomainAddress(int i, Octet sa);

        //void set_eventPortAddress(Octet *epa, int length);
        void set_eventPortAddress(Octet length);
        //void set_generalPortAddress(Octet *epa, int length);
        void set_generalPortAddress(Octet length);
        void set_portCommunicationTechnology(UInteger8 pct);
        void set_portUuidField(Octet *puf, int length);
        void set_portIdField(UInteger16 pif);
        void set_burstEnabled(Boolean be);
	//void set_foreign(ForeignMasterRecord *f);
	void set_foreign(int x);
	void free_foreign();

	void set_halfEpoch(Boolean he);
	void set_max_foreign_records(Integer16 mfr);
	void set_foreign_record_i(Integer16 fri);
	void set_foreign_record_best(Integer16 frb);
	void set_record_update(Boolean ru);
	void set_random_seed(UInteger32 rs);
	void set_msgTmpHeader(MsgHeader mth);
	void set_msgtmp(msgTmp mt);
	void set_msgObuf(Octet *mob,int length);
	void set_msgIbuf(Octet *mib,int length);
	void set_master_to_slave_delay(TimeInternal mtsd);

	void set_master_to_slave_delay_seconds(UInteger32 sec);
	void set_master_to_slave_delay_nanoseconds(Integer32 nsec);

	void set_slave_to_master_delay(TimeInternal stmd);

	void set_slave_to_master_delay_seconds(UInteger32 sec);
	void set_slave_to_master_delay_nanoseconds(Integer32 nsec);

	void set_delay_req_receive_time(TimeInternal drrt);
	void set_delay_req_send_time(TimeInternal drst);
	void set_sync_receive_time(TimeInternal srt);
	void set_waitingForFollow(Boolean wwf);
	
	void set_Q(UInteger16 q);
	void set_R(UInteger16 r);
	void set_sentDelayReq(Boolean sdr);
	void set_sentDelayReqSequenceId(UInteger16 sdrsi);
	void set_ofm_filt(offset_from_master_filter of);
	void set_owd_filt(one_way_delay_filter of);
	void set_owd_filt_s_exp(Integer32 s);

	void set_message_activity(Boolean ma);
	void set_itimer(IntervalTimer *i, int length);
	void set_netPath(NetPath np);

        friend ostream& operator<<(ostream& s, const PtpClock& it);

private:
        /* Default data set */
        UInteger8 clock_communication_technology;
        Octet   clock_uuid_field[PTP_UUID_LENGTH];
        UInteger16 clock_port_id_field;
        UInteger8 clock_stratum;
        Octet   clock_identifier[PTP_CODE_STRING_LENGTH];
        Integer16 clock_variance;
        Boolean clock_followup_capable;
        Boolean preferred;
        Boolean initializable;
        Boolean external_timing;
        Boolean is_boundary_clock;
        Integer8 sync_interval;
        Octet   subdomain_name[PTP_SUBDOMAIN_NAME_LENGTH];
        UInteger16 number_ports;
        UInteger16 number_foreign_records;

        /* Current data set */
        UInteger16 steps_removed;
        TimeInternal offset_from_master;
        TimeInternal one_way_delay;

        /* Parent data set */
        UInteger8 parent_communication_technology;
        Octet   parent_uuid[PTP_UUID_LENGTH];
        UInteger16 parent_port_id;
        UInteger16 parent_last_sync_sequence_number;
        Boolean parent_followup_capable;
        Boolean parent_external_timing;
        Integer16 parent_variance;
        Boolean parent_stats;
        Integer16 observed_variance;
        Integer32 observed_drift;
        Boolean utc_reasonable;
        UInteger8 grandmaster_communication_technology;
        Octet   grandmaster_uuid_field[PTP_UUID_LENGTH];
        UInteger16 grandmaster_port_id_field;
        UInteger8 grandmaster_stratum;
        Octet   grandmaster_identifier[PTP_CODE_STRING_LENGTH];
        Integer16 grandmaster_variance;
        Boolean grandmaster_preferred;
        Boolean grandmaster_is_boundary_clock;
        UInteger16 grandmaster_sequence_number;

        /* Global time properties data set */
        Integer16 current_utc_offset;
        Boolean leap_59;
        Boolean leap_61;
        UInteger16 epoch_number;

        /* Port configuration data set */
        UInteger8 port_state;
        UInteger16 last_sync_event_sequence_number;
        UInteger16 last_general_event_sequence_number;
        Octet   subdomain_address[SUBDOMAIN_ADDRESS_LENGTH];
        Octet	event_port_address[PORT_ADDRESS_LENGTH];
        Octet	general_port_address[PORT_ADDRESS_LENGTH];
        UInteger8 port_communication_technology;
        Octet   port_uuid_field[PTP_UUID_LENGTH];
        UInteger16 port_id_field;
        Boolean burst_enabled;

        /* Foreign master data set */

        /* Other things we need for the protocol */
        Boolean halfEpoch;

        Integer16 max_foreign_records;
        Integer16 foreign_record_i;
        Integer16 foreign_record_best;
        Boolean record_update;
        UInteger32 random_seed;

        MsgHeader msgTmpHeader;

        msgTmp msgtmp;

        Octet   msgObuf[PACKET_SIZE];
        Octet   msgIbuf[PACKET_SIZE];

        TimeInternal master_to_slave_delay;
        TimeInternal slave_to_master_delay;

        TimeInternal delay_req_receive_time;
        TimeInternal delay_req_send_time;
        TimeInternal sync_receive_time;

        UInteger16 Q;
        UInteger16 R;

        Boolean sentDelayReq;
        UInteger16 sentDelayReqSequenceId;
        Boolean waitingForFollow;

        offset_from_master_filter ofm_filt;
        one_way_delay_filter owd_filt;

        Boolean message_activity;

        IntervalTimer itimer[TIMER_ARRAY_SIZE];

        NetPath netPath;

	bool flag;
};

ostream& operator<<(ostream& s, const PtpClock& it);

#endif
