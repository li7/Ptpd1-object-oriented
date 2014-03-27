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

bmc_Driver.o: classes/ptpd.h classes/RunTimeOpts.h classes/PtpClock.h classes/MsgSync.h classes/MsgHeader.h classes/ForeignMasterRecord.h classes/TimeInternal.h classes/msgTmp.h

bmc.o: classes/ptpd.h classes/RunTimeOpts.h classes/PtpClock.h classes/MsgSync.h classes/MsgHeader.h classes/ForeignMasterRecord.h classes/TimeInternal.h classes/msgTmp.h

clean:
	rm -f *.o
	rm -f classes/*.o

real_clean: clean
	rm -f arith bmc

