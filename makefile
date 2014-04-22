CCC = g++
CCFLAGS = -ansi

airth: arith_Driver.o arith.o classes/TimeInternal.o classes/TimeRepresentation.o
	$(CCC) -o arith arith_Driver.o arith.o classes/TimeInternal.o classes/TimeRepresentation.o

timer: timer_Driver.o timer.o classes/IntervalTimer.o 
	$(CCC) -o timer timer_Driver.o timer.o classes/IntervalTimer.o 

arith_Driver.o: classes/TimeInternal.h classes/TimeRepresentation.h

arith.o: classes/ptpd.h 

classes/TimeInternal.o: classes/TimeInternal.h 

classes/TimeRepresentation.o: classes/TimeRepresentation.h

timer_driver.o: classes/IntervalTimer.h

timer.o: classes/ptpd.h

classes/IntervalTimer.o: classes/IntervalTimer.h

clean:
	rm -f *.o
	rm -f classes/*.o

real_clean: clean
	rm -f arith timer bmc msg net probe servo sys startup

