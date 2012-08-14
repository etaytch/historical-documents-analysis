#include "operationdo.h"

OperationDO::OperationDO()
{
	_operationType=QString("");
	_thershold=0;
}

OperationDO::OperationDO(QString type)
{
	_operationType=type;
	_thershold=0;
}

OperationDO::OperationDO(const OperationDO &o)
{
	_operationType=o._operationType;
	_thershold=o._thershold;
}


void OperationDO::setOperationType(QString type)
{
	_operationType = type;
}

void OperationDO::setThershold(float thershold)
{
	_thershold = thershold;
}

QString OperationDO::getOperationType() const
{
	return _operationType;
}

float OperationDO::getThershold() const
{
	return _thershold;
}

OperationDO::~OperationDO()
{

}
