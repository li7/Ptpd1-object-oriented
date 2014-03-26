#ifndef NETPATH_H
#define NETPATH_H
#include "datatypes_dep.h"
#include "constants.h"
#include <iostream>

using namespace std;

class NetPath{

public:

	/*************Constructor************/
	 NetPath();

	/****************accessors***********/
	Integer32 get_eventSock() const;
	Integer32 get_generalSock() const;
	Integer32 get_multicastAddr() const;
	Integer32 get_unicastAddr() const;

	/****************mutators***********/
	void set_eventSock(Integer32 es);
	void set_generalSock(Integer32 gs);
	void set_multicastAddr(Integer32 ma);
	void set_unicastAddr(Integer32 ua);

        friend ostream& operator<<(ostream& s, const NetPath& it);


private:
	Integer32 eventSock;
	Integer32 generalSock;
	Integer32 multicastAddr;
	Integer32 unicastAddr;
};

ostream& operator<<(ostream& s, const NetPath& it);

#endif
