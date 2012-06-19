#include <QtGui>
#include "manuscriptpropertiesdelegate.h"


ManuscriptPropertiesDelegate::ManuscriptPropertiesDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

QWidget *ManuscriptPropertiesDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &option,
	const QModelIndex &index ) const
{
	int row = index.row();
	int col = index.column();

	if  (col  == 0)
	{
		return QItemDelegate::createEditor(parent,option,index);
	}

	else if (col==1)
	{
		QString str =  (index.model()->data(index, Qt::DisplayRole)).toString();
		QLineEdit* editor = new QLineEdit(str,parent);
		return editor;
	}
	else
	{
		return QItemDelegate::createEditor(parent,option,index);
	}
}

void ManuscriptPropertiesDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	int row = index.row();
	int col = index.column();

	if  (col == 0)
	{
		return QItemDelegate::setEditorData(editor,index);
	}
	else if  (col== 1)
	{
		QString str =  (index.model()->data(index, Qt::DisplayRole)).toString();
		QLineEdit *e = static_cast<QLineEdit*>(editor);
		e->setText(str);			
	}
	else
	{
		return QItemDelegate::setEditorData(editor,index);
	}

}

void ManuscriptPropertiesDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	int row = index.row();
	int col = index.column();

	if  (col == 0)
	{
		return QItemDelegate::setModelData(editor,model,index);
	}
	else if  (col == 1)
	{
		QLineEdit *e = static_cast<QLineEdit*>(editor);
		QString value = e->text();
		model->setData(index, value, Qt::EditRole);
	}
	else
	{
		return QItemDelegate::setModelData(editor, model,index);
	}
}

void ManuscriptPropertiesDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}

