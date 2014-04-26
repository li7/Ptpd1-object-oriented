/**
 * @file   arith.cc
 * @date   Tue Jul 20 16:12:51 2010
 * 
 * @brief  Time format conversion routines and additional math functions.
 * 
 * 
 */

#include "classes/ptpd.h"

/* from annex C of the spec */
UInteger32 
crc_algorithm(Octet * buf, Integer16 length)
{
	Integer16 i;
	UInteger8 data;
	UInteger32 polynomial = 0xedb88320, crc = 0xffffffff;

	while (length-- > 0) {
		data = *(UInteger8 *) (buf++);

		for (i = 0; i < 8; i++) {
			if ((crc ^ data) & 1) {
				crc = (crc >> 1);
				crc ^= polynomial;
			} else {
				crc = (crc >> 1);
			}
			data >>= 1;
		}
	}

	return crc ^ 0xffffffff;
}

UInteger32 
sum(Octet * buf, Integer16 length)
{
	UInteger32 sum = 0;

	while (length-- > 0)
		sum += *(UInteger8 *) (buf++);

	return sum;
}

void 
fromInternalTime(TimeInternal * internal, TimeRepresentation * external, Boolean halfEpoch)
{
	external->set_seconds(labs(internal->get_seconds()) + halfEpoch * INT_MAX);

	if (internal->get_seconds() < 0 || internal->get_nanoseconds() < 0) {
		external->set_nanoseconds(labs(internal->get_nanoseconds()) | ~INT_MAX);
	} else {
		external->set_nanoseconds(labs(internal->get_nanoseconds()));
	}

	DBGV("fromInternalTime: %10ds %11dns -> %10us %11dns\n",
	    internal.get_seconds(), internal.get_nanoseconds(),
	    external.get_seconds(), external.get_nanoseconds());

}

void 
toInternalTime(TimeInternal * internal, TimeRepresentation * external, Boolean * halfEpoch)
{
	*halfEpoch = external->get_seconds() / INT_MAX;

	if (external->get_nanoseconds() & ~INT_MAX) {
		internal->set_seconds(-(external->get_seconds() % INT_MAX));
		internal->set_nanoseconds(-(external->get_nanoseconds() & INT_MAX));
	} else {
		internal->set_seconds(external->get_seconds() % INT_MAX);
		internal->set_nanoseconds(external->get_nanoseconds());
	}

	DBGV("toInternalTime: %10ds %11dns <- %10us %11dns\n",
	    internal.get_seconds(), internal.get_nanoseconds(),
	    external.get_seconds(), external.get_nanoseconds());

}

void 
normalizeTime(TimeInternal * r)
{
	r->set_seconds(r->get_seconds() + r->get_nanoseconds() / 1000000000);
	r->set_nanoseconds(r->get_nanoseconds() - r->get_nanoseconds() / 1000000000 * 1000000000);

	if (r->get_seconds() > 0 && r->get_nanoseconds() < 0) {
		r->set_seconds(r->get_seconds() - 1);
		r->set_nanoseconds(r->get_nanoseconds() + 1000000000);
	} else if (r->get_seconds() < 0 && r->get_nanoseconds() > 0) {
		r->set_seconds(r->get_seconds() + 1);
		r->set_nanoseconds(r->get_nanoseconds() - 1000000000);
	}
}

void 
addTime(TimeInternal * r, TimeInternal * x, TimeInternal * y)
{
	r->set_seconds(x->get_seconds() + y->get_seconds());
	r->set_nanoseconds(x->get_nanoseconds() + y->get_nanoseconds());

	normalizeTime(r);
}

void 
subTime(TimeInternal * r, TimeInternal * x, TimeInternal * y)
{
	r->set_seconds(x->get_seconds() - y->get_seconds());
	r->set_nanoseconds(x->get_nanoseconds() - y->get_nanoseconds());

	normalizeTime(r);
}
