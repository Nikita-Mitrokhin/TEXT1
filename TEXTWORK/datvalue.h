#ifndef __DATVALUE_H
#define __DATVALUE_H

#include <iostream>
using namespace std;
class TDatValue 
{
public:
	virtual TDatValue * GetCopy() =0;
	~TDatValue() 
	{}

};
typedef TDatValue *PTDatValue;
#endif
