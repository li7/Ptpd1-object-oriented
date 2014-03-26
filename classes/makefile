CCC = g++
CCFLAGS = -ansi

all: MsgHeader TimeRepresentation TimeInternal MsgFollowUp MsgDelayResp ClockIdentity Current DefaultData Foreign ForeignMasterRecord GlobalTime IntervalTimer MsgHeader MsgManagement MsgManagementPayload MsgSync msgTmp NetPath offset_from_master_filter one_way_delay_filter Parent Port PtpClock RunTimeOpts

MsgHeader: MsgHeader_Driver.o MsgHeader.o
	$(CCC) -o MsgHeader MsgHeader_Driver.o MsgHeader.o

TimeRepresentation: TimeRepresentation_Driver.o TimeRepresentation.o
	$(CCC) -o TimeRepresentation TimeRepresentation_Driver.o TimeRepresentation.o

TimeInternal: TimeInternal_Driver.o TimeInternal.o
	$(CCC) -o TimeInternal TimeInternal_Driver.o TimeInternal.o

MsgFollowUp: MsgFollowUp_Driver.o MsgFollowUp.o TimeRepresentation.o
	$(CCC) -o MsgFollowUp MsgFollowUp_Driver.o MsgFollowUp.o TimeRepresentation.o

MsgDelayResp: MsgDelayResp_Driver.o MsgDelayResp.o TimeRepresentation.o
	$(CCC) -o MsgDelayResp MsgDelayResp_Driver.o MsgDelayResp.o TimeRepresentation.o

MsgSync: MsgSync_Driver.o MsgSync.o TimeRepresentation.o
	$(CCC) -o MsgSync MsgSync_Driver.o MsgSync.o TimeRepresentation.o

IntervalTimer: IntervalTimer_Driver.o IntervalTimer.o
	$(CCC) -o IntervalTimer IntervalTimer_Driver.o IntervalTimer.o

ForeignMasterRecord: ForeignMasterRecord_Driver.o ForeignMasterRecord.o MsgHeader.o MsgSync.o TimeRepresentation.o
	$(CCC) -o ForeignMasterRecord ForeignMasterRecord_Driver.o ForeignMasterRecord.o MsgHeader.o MsgSync.o TimeRepresentation.o

ClockIdentity: ClockIdentity_Driver.o ClockIdentity.o
	$(CCC) -o ClockIdentity ClockIdentity_Driver.o ClockIdentity.o

Current: Current_Driver.o Current.o TimeRepresentation.o
	$(CCC) -o Current Current_Driver.o Current.o TimeRepresentation.o

DefaultData: DefaultData_Driver.o DefaultData.o
	$(CCC) -o DefaultData DefaultData_Driver.o DefaultData.o

GlobalTime: GlobalTime_Driver.o GlobalTime.o TimeRepresentation.o
	$(CCC) -o GlobalTime GlobalTime_Driver.o GlobalTime.o TimeRepresentation.o

Parent: Parent_Driver.o Parent.o 
	$(CCC) -o Parent Parent_Driver.o Parent.o 

Port: Port_Driver.o Port.o 
	$(CCC) -o Port Port_Driver.o Port.o 

Foreign: Foreign_Driver.o Foreign.o 
	$(CCC) -o Foreign Foreign_Driver.o Foreign.o 

MsgManagementPayload: MsgManagementPayload_Driver.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o
	$(CCC) -o MsgManagementPayload MsgManagementPayload_Driver.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o

offset_from_master_filter: offset_from_master_filter_Driver.o offset_from_master_filter.o 
	$(CCC) -o offset_from_master_filter offset_from_master_filter_Driver.o offset_from_master_filter.o 

one_way_delay_filter: one_way_delay_filter_Driver.o one_way_delay_filter.o
	$(CCC) -o one_way_delay_filter one_way_delay_filter_Driver.o one_way_delay_filter.o 

NetPath: NetPath_Driver.o NetPath.o
	$(CCC) -o NetPath NetPath_Driver.o NetPath.o 

MsgManagement: MsgManagement_Driver.o MsgManagement.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o
	$(CCC) -o MsgManagement MsgManagement_Driver.o MsgManagement.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o

RunTimeOpts: RunTimeOpts_Driver.o RunTimeOpts.o TimeInternal.o
	$(CCC) -o RunTimeOpts RunTimeOpts_Driver.o RunTimeOpts.o TimeInternal.o 

msgTmp: msgTmp_Driver.o msgTmp.o MsgSync.o MsgFollowUp.o MsgDelayResp.o MsgManagement.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o 
	$(CCC) -o msgTmp msgTmp_Driver.o msgTmp.o MsgSync.o MsgFollowUp.o MsgDelayResp.o MsgManagement.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o

PtpClock: PtpClock_Driver.o PtpClock.o msgTmp.o MsgSync.o MsgFollowUp.o MsgDelayResp.o MsgManagement.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o TimeInternal.o MsgHeader.o IntervalTimer.o offset_from_master_filter.o one_way_delay_filter.o ForeignMasterRecord.o NetPath.o
	$(CCC) -o PtpClock PtpClock_Driver.o PtpClock.o msgTmp.o MsgSync.o MsgFollowUp.o MsgDelayResp.o MsgManagement.o MsgManagementPayload.o ClockIdentity.o DefaultData.o Current.o Parent.o Port.o GlobalTime.o Foreign.o TimeRepresentation.o TimeInternal.o MsgHeader.o IntervalTimer.o offset_from_master_filter.o one_way_delay_filter.o ForeignMasterRecord.o NetPath.o
MsgHeader_Driver.o: MsgHeader.h 

MsgHeader.o: MsgHeader.h 

TimeRepresentation_Driver.o: TimeRepresentation.h

TimeRepresentation.o: TimeRepresentation.h 

TimeInternal_Driver.o: TimeInternal.h 

TimeInternal.o: TimeInternal.h 

MsgFollowUp_Driver.o: MsgFollowUp.h TimeRepresentation.h 

MsgFollowUp.o: MsgFollowUp.h TimeRepresentation.h 

MsgDelayResp_Driver.o: MsgDelayResp.h TimeRepresentation.h 

MsgDelayResp.o: MsgDelayResp.h TimeRepresentation.h 

MsgSync_Driver.o: MsgSync.h

MsgSync.o: TimeRepresentation.h

IntervalTimer_Driver.o: IntervalTimer.h 

IntervalTimer.o: IntervalTimer.h 

ForeignMasterRecord_Driver.o: ForeignMasterRecord.h 

ForeignMasterRecord.o: MsgHeader.h MsgSync.h 

ClockIdentity_Driver.o: ClockIdentity.h

ClockIdentity.o: ClockIdentity.h

Current_Driver.o: Current.h TimeRepresentation.h 

Current.o: Current.h TimeRepresentation.h 

DefaultData_Driver.o: DefaultData.h

DefaultData.o: DefaultData.h

GlobalTime_Driver.o: GlobalTime.h TimeRepresentation.h 

GlobalTime.o: GlobalTime.h TimeRepresentation.h 

Parent_Driver.o: Parent.h 

Parent.o: Parent.h 

Port_Driver.o: Port.h 

Port.o: Port.h 

Foreign_Driver.o: Foreign.h 

Foreign.o: Foreign.h 

MsgManagementPayload_Driver.o: MsgManagementPayload.h 

MsgManagementPayload.o: MsgManagementPayload.h ClockIdentity.h DefaultData.h Current.h Parent.h Port.h GlobalTime.h Foreign.h

offset_from_master_filter_Driver.o: offset_from_master_filter.h

offset_from_master_filter.o: offset_from_master_filter.h

one_way_delay_filter_Driver.o: one_way_delay_filter.h

one_way_delay_filter.o: one_way_delay_filter.h

NetPath_Driver.o: NetPath.h

NetPath.o: NetPath.h

MsgManagement_Driver.o: MsgManagement.h 

MsgManagement.o: MsgManagement.h MsgManagementPayload.h ClockIdentity.h DefaultData.h Current.h Parent.h Port.h GlobalTime.h Foreign.h

RunTimeOpts_Driver.o: RunTimeOpts.h 

RunTimeOpts.o: RunTimeOpts.h TimeInternal.h

msgTmp_Driver.o: msgTmp.h

msgTmp.o: msgTmp.h MsgSync.h  MsgDelayReq.h MsgFollowUp.h MsgDelayResp.h MsgManagement.h MsgManagementPayload.h TimeRepresentation.h

PtpClock_Driver.o: PtpClock.h

PtpClock.o: TimeInternal.h MsgHeader.h IntervalTimer.h NetPath.h offset_from_master_filter.h one_way_delay_filter.h ForeignMasterRecord.h msgTmp.h

clean:
	rm -f *.o

real_clean:
	rm -f MsgHeader TimeRepresentation TimeInternal MsgFollowUp MsgDelayResp 
	rm -f MsgSync IntervalTimer ForeignMasterRecord ClockIdentity Current
	rm -f DefaultData GlobalTime Parent Port Foreign MsgManagementPayload
	rm -f offset_from_master_filter one_way_delay_filter NetPath
	rm -f MsgManagement RunTimeOpts PtpClock msgTmp
