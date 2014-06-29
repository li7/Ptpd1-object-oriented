#all:
#	 g++ -w -o ptpd ptpd.cc protocol.cc probe.cc classes/RunTimeOpts.cc classes/TimeInternal.cc classes/PtpClock.cc classes/msgTmp.cc classes/MsgHeader.cc classes/MsgDelayResp.cc classes/TimeRepresentation.cc classes/MsgSync.cc classes/MsgManagement.cc classes/MsgManagementPayload.cc classes/ClockIdentity.cc classes/Parent.cc classes/Port.cc classes/Current.cc classes/GlobalTime.cc classes/DefaultData.cc classes/Foreign.cc classes/NetPath.cc classes/MsgFollowUp.cc classes/IntervalTimer.cc classes/one_way_delay_filter.cc classes/offset_from_master_filter.cc sys.cc net.cc startup.cc arith.cc bmc.cc msg.cc classes/ForeignMasterRecord.cc servo.cc timer.cc

CC = g++
CFLAGS = -w -Wall #-DBSD_INTERFACE_FUNCTIONS
#CPPFLAGS = -DPTPD_DBG -DPTPD_NO_DAEMON

PROG = ptpd
SRCS = ptpd.cc arith.cc bmc.cc probe.cc protocol.cc \
	msg.cc net.cc servo.cc startup.cc sys.cc timer.cc \
	classes/ClockIdentity.cc classes/Current.cc \
	classes/DefaultData.cc classes/Foreign.cc \
	classes/ForeignMasterRecord.cc classes/GlobalTime.cc \
	classes/IntervalTimer.cc \
	classes/MsgDelayResp.cc classes/MsgFollowUp.cc \
	classes/MsgHeader.cc classes/MsgManagement.cc \
	classes/MsgManagementPayload.cc classes/MsgSync.cc \
	classes/msgTmp.cc classes/NetPath.cc \
	classes/offset_from_master_filter.cc \
	classes/one_way_delay_filter.cc classes/Parent.cc \
	classes/Port.cc classes/PtpClock.cc \
	classes/RunTimeOpts.cc classes/TimeInternal.cc \
	classes/TimeRepresentation.cc

OBJS = $(SRCS:.cc=.o)

HDRS = classes/ptpd.h classes/constants.h classes/datatypes.h \
        classes/ptpd_dep.h classes/constants_dep.h \
	classes/datatypes_dep.h classes/ClockIdentity.h \
	classes/Current.h classes/DefaultData.h \
	classes/Foreign.h classes/ForeignMasterRecord.h \
	classes/GlobalTime.h classes/IntervalTimer.h \
	classes/MsgDelayReq.h classes/MsgDelayResp.h \
	classes/MsgFollowUp.h classes/MsgHeader.h \
	classes/MsgManagement.h classes/MsgManagementPayload.h \
	classes/MsgSync.h classes/msgTmp.h classes/NetPath.h \
	classes/offset_from_master_filter.h \
	classes/one_way_delay_filter.h classes/Parent.h \
	classes/Port.h classes/PtpClock.h classes/RunTimeOpts.h \
	classes/TimeInternal.h classes/TimeRepresentation.h 

.cc.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f *.o

real_clean:
	rm -f ptpd
