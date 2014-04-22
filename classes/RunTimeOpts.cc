#include "RunTimeOpts.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
RunTimeOpts::RunTimeOpts()
{
}

/*****************accessors***************/
Integer8 RunTimeOpts::get_syncInterval() const
{return syncInterval;}

Octet* RunTimeOpts::get_subdomainName()
{return subdomainName;}

Octet* RunTimeOpts::get_clockIdentifier()
{return clockIdentifier;}

UInteger32 RunTimeOpts::get_clockVariance() const
{return clockVariance;}

UInteger8 RunTimeOpts::get_clockStratum() const
{return clockStratum;}

Boolean RunTimeOpts::get_clockPreferred() const
{return clockPreferred;}

Integer16 RunTimeOpts::get_currentUtcOffset() const
{return currentUtcOffset;}

UInteger16 RunTimeOpts::get_epochNumber() const
{return epochNumber;}

Octet* RunTimeOpts::get_ifaceName()
{return ifaceName;}

Boolean RunTimeOpts::get_noResetClock() const
{return noResetClock;}

Integer32 RunTimeOpts::get_maxReset() const
{return maxReset;}

Integer32 RunTimeOpts::get_maxDelay() const
{return maxDelay;}

Boolean RunTimeOpts::get_noAdjust() const
{return noAdjust;}

Boolean RunTimeOpts::get_displayStats() const
{return displayStats;}

Boolean RunTimeOpts::get_csvStats() const
{return csvStats;}

Octet* RunTimeOpts::get_unicastAddress()
{return unicastAddress;}

Octet RunTimeOpts::get_unicastAddress(int i) const
{return unicastAddress[i];}

Integer16 RunTimeOpts::get_ap() const
{return ap;}

Integer16 RunTimeOpts::get_ai() const
{return ai;}

Integer16 RunTimeOpts::get_s() const
{return s;}

TimeInternal& RunTimeOpts::get_inboundLatency()
{return inboundLatency;}

TimeInternal& RunTimeOpts::get_outboundLatency()
{return outboundLatency;}

Integer16 RunTimeOpts::get_max_foreign_records() const
{return max_foreign_records;}

Boolean RunTimeOpts::get_slaveOnly() const
{return slaveOnly;}

Boolean RunTimeOpts::get_probe() const
{return probe;}

UInteger8 RunTimeOpts::get_probe_management_key() const
{return probe_record_key;}

UInteger16 RunTimeOpts::get_probe_record_key() const
{return probe_record_key;}

Boolean RunTimeOpts::get_halfEpoch() const
{return halfEpoch;}

char* RunTimeOpts::get_file()
{return file;}

int RunTimeOpts::get_logFd() const
{return logFd;}

Boolean RunTimeOpts::get_useSysLog() const
{return useSysLog;}

int& RunTimeOpts::get_ttl()
{return ttl;}

char* RunTimeOpts::get_recordFile()
{return recordFile;}

FILE* RunTimeOpts::get_recordFP()
{return recordFP;}

/****************mutators******************/
void RunTimeOpts::set_syncInterval(Integer8 si)
{syncInterval = si;}

void RunTimeOpts::set_subdomainName(int sn, int length)
{memset(subdomainName,sn,length);}

void RunTimeOpts::set_subdomainName(const Octet *sn, int length)
{strncpy(subdomainName,sn,length);}

void RunTimeOpts::set_subdomainName(const void *sn, int length)
{memcpy(subdomainName,sn,length);}

void RunTimeOpts::set_clockIdentifier(int ci, int length)
{memset(clockIdentifier,ci,length);}

void RunTimeOpts::set_clockIdentifier(Octet *ci, int length)
{strncpy(clockIdentifier,ci,length);}

void RunTimeOpts::set_clockVariance(Integer16 cv)
{clockVariance = cv;}

void RunTimeOpts::set_clockStratum(UInteger8 cs)
{clockStratum = cs;}

void RunTimeOpts::set_clockPreferred(Boolean cp)
{clockPreferred = cp;}

void RunTimeOpts::set_currentUtcOffset(Integer16 cuo)
{currentUtcOffset = cuo;}

void RunTimeOpts::set_epochNumber(UInteger16 en)
{epochNumber = en;}

void RunTimeOpts::set_ifaceName(int ifn, int length)
{memset(ifaceName,ifn,length);}

void RunTimeOpts::set_ifaceName(Octet *ifn, int length)
{strncpy(ifaceName,ifn,length);}

void RunTimeOpts::set_noResetClock(Boolean nrc)
{noResetClock = nrc;}

void RunTimeOpts::set_maxReset(Integer32 mr)
{maxReset = mr;}

void RunTimeOpts::set_maxDelay(Integer32 md)
{maxDelay = md;}

void RunTimeOpts::set_noAdjust(Boolean na)
{noAdjust = na;}

void RunTimeOpts::set_displayStats(Boolean ds)
{displayStats = ds;}

void RunTimeOpts::set_csvStats(Boolean cs)
{csvStats = cs;}

void RunTimeOpts::set_unicastAddress(Octet *ua, int length)
{strncpy(unicastAddress,ua,length);}

void RunTimeOpts::set_unicastAddress(int position, int i)
{unicastAddress[position] = i;}

void RunTimeOpts::set_ap(Integer16 a)
{ap = a;}

void RunTimeOpts::set_ai(Integer16 a)
{ai = a;}

void RunTimeOpts::set_s(Integer16 i)
{s = i;}

void RunTimeOpts::set_inboundLatency(TimeInternal ibl)
{inboundLatency = ibl;}

void RunTimeOpts::set_inboundLatency_nanoseconds(Integer32 nsec)
{inboundLatency.set_nanoseconds(nsec);}

void RunTimeOpts::set_outboundLatency(TimeInternal obl)
{outboundLatency = obl;}

void RunTimeOpts::set_outboundLatency_nanoseconds(Integer32 nsec)
{outboundLatency.set_nanoseconds(nsec);}

void RunTimeOpts::set_max_foreign_records(Integer16 mfr)
{max_foreign_records = mfr;}

void RunTimeOpts::set_slaveOnly(Boolean so)
{slaveOnly = so;}

void RunTimeOpts::set_probe(Boolean p)
{probe = p;}

void RunTimeOpts::set_probe_management_key(UInteger8 pmk)
{probe_management_key = pmk;}

void RunTimeOpts::set_probe_record_key(UInteger16 prk)
{probe_record_key = prk;}

void RunTimeOpts::set_halfEpoch(Boolean he)
{halfEpoch = he;}

void RunTimeOpts::set_file(char *f, int length)
{strncpy(file,f,length);}

void RunTimeOpts::set_logFd(int lf)
{logFd = lf;}

void RunTimeOpts::set_useSysLog(Boolean usl)
{useSysLog = usl;}

void RunTimeOpts::set_ttl(int t)
{ttl = t;}

void RunTimeOpts::set_recordFile(char *rf, int length)
{strncpy(recordFile,rf,length);}

void RunTimeOpts::set_recordFP(char *rf)
{recordFP = fopen(rf,"w");}

ostream& operator<<(ostream& s, const RunTimeOpts& it)
{
        return s;
}

