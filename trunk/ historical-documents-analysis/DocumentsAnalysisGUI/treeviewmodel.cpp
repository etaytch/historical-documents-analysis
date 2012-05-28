#include "treeviewmodel.h"
#include <QFileInfo.h>
TreeViewModel::TreeViewModel(ProjectDoc& pd, QObject *parent)
	:QAbstractItemModel(parent)
{
	_project=pd;
	QVector<QVariant> rootData;
	rootData << _project.getName();
	_rootItem = new TreeItem(rootData);
	setupModel(_rootItem);
}

int TreeViewModel::columnCount(const QModelIndex &parent) const
{
    return _rootItem->columnCount();
}

int TreeViewModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool TreeViewModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = _rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeViewModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;
    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, _rootItem->columnCount());
    endInsertRows();
    return success;
}

bool TreeViewModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;
    beginRemoveColumns(parent, position, position + columns - 1);
    success = _rootItem->removeColumns(position, columns);
    endRemoveColumns();
    if (_rootItem->columnCount() == 0)
        removeRows(0, rowCount());
    return success;
}

bool TreeViewModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;
    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();
    return success;
}

QVariant TreeViewModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);
    return QVariant();
}

QVariant TreeViewModel::data(const QModelIndex &index, int role) const
{

	if (!index.isValid())
		return QVariant();

	TreeItem *item = getItem(index);
	if (role == Qt::DisplayRole)
	{
		if (qVariantCanConvert<PageDoc> (item->data(index.column())))
		{
			PageDoc pd = qVariantValue<PageDoc>(item->data(index.column()));
			return QFileInfo(QString(pd.getPage()->getName().c_str())).fileName();
		}
		/*else if (qVariantCanConvert<ManuscriptDoc> (item->data(index.column())))
		{
			ManuscriptDoc md = qVariantValue<ManuscriptDoc>(item->data(index.column()));

		}*/
		return item->data(index.column());
	}
	if (role == Qt::UserRole)
	{
		return item->data(index.column());
	}

	return QVariant();	
}

bool TreeViewModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role != Qt::EditRole)
        return false;
    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);
    return result;
}

bool TreeViewModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;
    bool result = _rootItem->setData(section, value);
    if (result)
        emit headerDataChanged(orientation, section, section);
    return result;
}

Qt::ItemFlags TreeViewModel::flags(const QModelIndex & index) const
{
	 if (!index.isValid())
		return 0;
	return	Qt::ItemIsSelectable
			| Qt::ItemIsEnabled
			| Qt::ItemIsUserCheckable;
}

QModelIndex TreeViewModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();
    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();
    if (parentItem == _rootItem)
        return QModelIndex();
    return createIndex(parentItem->childNumber(), 0, parentItem);
}

QModelIndex TreeViewModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    TreeItem *parentItem = getItem(parent);
    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

TreeItem *TreeViewModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return _rootItem;
}

void TreeViewModel::setupModel(TreeItem *parent) 
{
	QVector<TreeItem*> Parents;
	QMap<QString,QString>::iterator manPathIter;

	parent->insertChildren(parent->childCount(), _project.getManuscriptCount(), 1);
	int manCount = 0;

	for(manPathIter=_project.getPaths().begin();
		manPathIter!= _project.getPaths().end();
		manPathIter++)
	{
		QString manName = manPathIter.key();
		parent->child(manCount)->setData(0,manName);
		Parents.append(parent->child(manCount));
		manCount++;
	}

	foreach(TreeItem* treeitem,Parents)
	{
		QString manName = qVariantValue<QString>(treeitem->data(0));
		ManuscriptDoc man = _project.getManuscriptAt(manName);
		vector<Page*>::iterator pageIter;
		int pageCount = 0;
		treeitem->insertChildren(treeitem->childCount(), man.getPages().size(), 1);
		for(pageIter = man.getPages().begin(); pageIter!= man.getPages().end(); pageIter++)
		{
			treeitem->child(pageCount)->setData(0,QVariant::fromValue(PageDoc(*pageIter,manName,treeitem,0)));				
			setUpPages(*pageIter,manName,treeitem->child(pageCount));
			pageCount++;
		}
	}
}

void TreeViewModel::setUpPages (Page* page ,QString manName ,TreeItem* treeitem)
{
	if (qVariantCanConvert<PageDoc> (treeitem->data(0)))
	{
		PageDoc pd = qVariantValue<PageDoc>(treeitem->data(0));
		if (pd.getPage()->getPages().size()>0)
		{
			int pageCount = 0;
			treeitem->insertChildren(treeitem->childCount(), page->getPages().size(), 1);
			vector<Page*>::iterator pageIter;
			for(pageIter = page->getPages().begin(); pageIter!= page->getPages().end(); pageIter++)
			{
				treeitem->child(pageCount)->setData(0,QVariant::fromValue(PageDoc(*pageIter,manName,treeitem,0)));
				setUpPages(*pageIter,manName,treeitem->child(pageCount));
				pageCount++;
			}
		}
	}
}


TreeViewModel::~TreeViewModel()
{
	delete _rootItem;	
}