#ifndef OPERATIONDO_H
#define OPERATIONDO_H

#include <QObject>
#include <QMetaType>
#include <QModelIndex>


class OperationDO : public QObject 
{
	Q_OBJECT
	
public:
	OperationDO();
	OperationDO(QString type);
	OperationDO(const OperationDO &o);  
	~OperationDO();

	void setOperationType(QString type);	
	void setThershold(float thershold);
	
	QString getOperationType() const;	
	float getThershold() const;
	virtual QVariant data(const QModelIndex &index, int role) const = 0;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role) = 0;
	virtual int rowCount(const QModelIndex &parent) const = 0;
	virtual int columnCount(const QModelIndex &parent) const = 0;
	
protected:
	QString _operationType;
	float _thershold;
};

Q_DECLARE_METATYPE(OperationDO*);


#endif // OperationDO_H
