

#ifndef MANPROPERTIESDELEGATE_H
#define MANPROPERTIESDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QLineEdit>
#include <QComboBox>


class ManuscriptPropertiesDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ManuscriptPropertiesDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
							 const QStyleOptionViewItem &option, 
							 const QModelIndex &index) const;

	~ManuscriptPropertiesDelegate(){}
};

#endif //MANPROPERTIESDELEGATE
