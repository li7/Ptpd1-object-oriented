#include "NetPath.h"
#include <iostream>

using namespace std;

/*****************Constructor****************/
NetPath::NetPath()
{
}

/*****************accessors***************/
Integer32 NetPath::get_eventSock() const
{return eventSock;}

Integer32 NetPath::get_generalSock() const
{return generalSock;}

Integer32 NetPath::get_multicastAddr() const
{return multicastAddr;}

Integer32 NetPath::get_unicastAddr() const
{return unicastAddr;}

/****************mutators******************/
void NetPath::set_eventSock(Integer32 es)
{eventSock = es;}

void NetPath::set_generalSock(Integer32 gs)
{generalSock = gs;}

void NetPath::set_multicastAddr(Integer32 ma)
{multicastAddr = ma;}

void NetPath::set_unicastAddr(Integer32 ua)
{unicastAddr = ua;}

ostream& operator<<(ostream& s, const NetPath& it)
{
        cout << "eventSock : " << it.eventSock << endl;
        cout << "generalSock : " << it.generalSock << endl;
        cout << "multicastAddr : " << it.multicastAddr << endl;
        cout << "unicastAddr : " << it.unicastAddr << endl;

        return s;
}

