#include "classes/ptpd.h"
#include "classes/TimeInternal.h"
#include "classes/TimeRepresentation.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	TimeInternal *internal;
	TimeRepresentation *external;
	Boolean halfEpoch;

	halfEpoch = true;
	
	fromInternalTime(internal, external, halfEpoch);
}

