CCC = g++
CCFLAGS = -ansi

airth: arith_Driver.o arith.o classes/TimeInternal.o classes/TimeRepresentation.o
	$(CCC) -o arith arith_Driver.o arith.o classes/TimeInternal.o classes/TimeRepresentation.o

bmc: bmc_Driver.o bmc.o classes/RunTimeOpts.o classes/PtpClock.o classes/MsgSync.o classes/MsgHeader.o classes/ForeignMasterRecord.o classes/TimeInternal.o classes/msgTmp.o
	$(CCC) -o bmc bmc_Driver.o bmc.o classes/RunTimeOpts.o classes/PtpClock.o classes/MsgSync.o classes/MsgHeader.o classes/ForeignMasterRecord.o classes/TimeInternal.o classes/msgTmp.o

arith_Driver.o: classes/ptpd.h classes/TimeInternal.h classes/TimeRepresentation.h

arith.o: classes/ptpd.h classes/TimeInternal.h classes/TimeRepresentation.h

classes/TimeInternal.o: classes/TimeInternal.h 

classes/TimeRepresentation.o: classes/TimeRepresentation.h

bmc_Driver.o: classes/ptpd.h classes/RunTimeOpts.h classes/PtpClock.h classes/MsgSync.h classes/MsgHeader.h classes/ForeignMasterRecord.h classes/msgTmp.h

bmc.o: classes/ptpd.h classes/RunTimeOpts.h classes/PtpClock.h classes/MsgSync.h classes/MsgHeader.h classes/ForeignMasterRecord.h classes/msgTmp.h

classes/RunTimeOpts.o: classes/RunTimeOpts.h classes/TimeInternal.h

classes/PtpClock.o: classes/PtpClock.h classes/msgTmp.h classes/MsgSync.h classes/MsgFollowUp.h classes/MsgDelayResp.h classes/MsgManagement.h classes/MsgManagementPayload.h classes/ClockIdentity.h classes/DefaultData.h classes/Current.h classes/Parent.h classes/GlobalTime.h classes/Foreign.h classes/TimeRepresentation.h classes/TimeInternal.h classes/MsgHeader.h classes/IntervalTimer.h classes/offset_from_master_filter.h classes/one_way_delay_filter.h classes/ForeignMasterRecord.h classes/NetPath.h

classes/MsgSync.o: classes/MsgSync.h classes/TimeRepresentation.h

classes/MsgHeader.o: classes/MsgHeader.h classes/TimeRepresentation.h

classes/ForeignMasterRecord.o: classes/MsgSync.h classes/MsgHeader.h

classes/TimeInternal.o: classes/TimeInternal.h

clean:
	rm -f *.o
	rm -f classes/*.o

real_clean: clean
	rm -f arith

