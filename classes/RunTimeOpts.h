#ifndef RUNTIMEOPTS_H
#define RUNTIMEOPTS_H
#include "TimeInternal.h"
#include "constants.h"
#include "constants_dep.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class RunTimeOpts{

public:

	/*************Constructor************/
	RunTimeOpts();

	/****************accessors***********/
	Integer8 get_syncInterval() const;
	Octet* get_subdomainName();
	Octet* get_clockIdentifier();
	UInteger32 get_clockVariance() const;
	UInteger8 get_clockStratum() const;
	Boolean get_clockPreferred() const;
	Integer16 get_currentUtcOffset() const;
	UInteger16 get_epochNumber() const;
	Octet* get_ifaceName();
	Boolean get_noResetClock() const;
	Integer32 get_maxReset() const;
	Integer32 get_maxDelay() const;
	Boolean get_noAdjust() const;
	Boolean get_displayStats() const;
	Boolean get_csvStats() const;
	Octet* get_unicastAddress();
	Octet get_unicastAddress(int i) const;
	Integer16 get_ap() const;
	Integer16 get_ai() const;
	Integer16 get_s() const;
	TimeInternal& get_inboundLatency();
	TimeInternal& get_outboundLatency();
	Integer16 get_max_foreign_records() const;
	Boolean get_slaveOnly() const;
	Boolean get_probe() const;
	UInteger8 get_probe_management_key() const;
	UInteger16 get_probe_record_key() const;
	Boolean get_halfEpoch() const;
	char* get_file();
	int get_logFd() const;
	Boolean get_useSysLog() const;
	int& get_ttl();
	char* get_recordFile();
	FILE* get_recordFP();

	/****************mutators***********/
	void set_syncInterval(Integer8 si);
	void set_subdomainName(int sn, int length);
	void set_subdomainName(const Octet *sn, int length);
	void set_subdomainName(const void *sn, int length);
	void set_clockIdentifier(int ci, int length);
	void set_clockIdentifier(Octet *ci, int length);
	void set_clockVariance(Integer16 cv);
	void set_clockStratum(UInteger8 cs);
	void set_clockPreferred(Boolean cp);
	void set_currentUtcOffset(Integer16 cuo);
	void set_epochNumber(UInteger16 en);
	void set_ifaceName(int ifn, int length);
	void set_ifaceName(Octet *ifn, int length);
	void set_noResetClock(Boolean nrc);
	void set_maxReset(Integer32 mr);
	void set_maxDelay(Integer32 md);
	void set_noAdjust(Boolean na);
	void set_displayStats(Boolean ds);
	void set_csvStats(Boolean cs);
	void set_unicastAddress(Octet *ua, int length);
	void set_unicastAddress(int position, int i);
	void set_ap(Integer16 a);
	void set_ai(Integer16 a);
	void set_s(Integer16 i);
	void set_inboundLatency(TimeInternal ibl);
	void set_inboundLatency_nanoseconds(Integer32 nsec);

	void set_outboundLatency(TimeInternal obl);
	void set_outboundLatency_nanoseconds(Integer32 nsec);
	void set_max_foreign_records(Integer16 mfr);
	void set_slaveOnly(Boolean so);
	void set_probe(Boolean p);
	void set_probe_management_key(UInteger8 pmk);
	void set_probe_record_key(UInteger16 prk);
	void set_halfEpoch(Boolean he);
	void set_file(char *f, int length);
	void set_logFd(int lf);
	void set_useSysLog(Boolean p);
	void set_ttl(int t);
	void set_recordFile(char *rf, int length);
	void set_recordFP(char *rf);

        friend ostream& operator<<(ostream& s, const RunTimeOpts& it);


private:
        Integer8 syncInterval;
        Octet   subdomainName[PTP_SUBDOMAIN_NAME_LENGTH];
        Octet   clockIdentifier[PTP_CODE_STRING_LENGTH];
        UInteger32 clockVariance;
        UInteger8 clockStratum;
        Boolean clockPreferred;
        Integer16 currentUtcOffset;
        UInteger16 epochNumber;
        Octet   ifaceName[IFACE_NAME_LENGTH];
        Boolean noResetClock;
        Integer32 maxReset; /* Maximum number of nanoseconds to reset */
        Integer32 maxDelay; /* Maximum number of nanoseconds of delay */
        Boolean noAdjust;
        Boolean displayStats;
        Boolean csvStats;
        Octet   unicastAddress[NET_ADDRESS_LENGTH];
        Integer16 ap, ai;
        Integer16 s;
        TimeInternal inboundLatency, outboundLatency;
        Integer16 max_foreign_records;
        Boolean slaveOnly;
        Boolean probe;
        UInteger8 probe_management_key;
        UInteger16 probe_record_key;
        Boolean halfEpoch;
        char file[PATH_MAX];
        int logFd;
        Boolean useSysLog;
        int ttl;
        char recordFile[PATH_MAX];
        FILE *recordFP;
};

ostream& operator<<(ostream& s, const RunTimeOpts& it);

#endif
