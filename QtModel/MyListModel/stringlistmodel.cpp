#include "stringlistmodel.h"


StringListModel::StringListModel(const QStringList & strings,
                                 QObject* parent):
    QAbstractListModel(parent), stringList(strings)
{

}

int StringListModel::rowCount(const QModelIndex& parent ) const{
    return stringList.count();
}

QVariant StringListModel::data(const QModelIndex& index, int role) const{   //获取Index处的数据

    if(!index.isValid()){       //如果数据不有效
        return QVariant();
    }

    if(index.row() >= stringList.size()){   //判断index对应的行号是否有问题
        return QVariant();
    }

    if(role == Qt::DisplayRole || role == Qt::EditRole){    //如果角色是展示和可编辑的
        return stringList.at(index.row());      //返回列表中对应位置的值（数据）
    }else{
        return QVariant();
    }
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation,int role) const{
    //这个是用来展示数据的头部，调用是在View渲染的时候会自动调用

    if(role != Qt::DisplayRole){    //如果角色不是要展示的类型
        return QVariant();
    }

    if(orientation == Qt::Horizontal){      //如果是水平的
        return QString("Column %1").arg(section);   //展示列的第几部分，类似于第几列
    }else{
        return QString("Row %1").arg(section);
    }
}

Qt::ItemFlags  StringListModel::flags(const QModelIndex& index) const{  //用来描述项目的属性，是可编辑的还是可选的之类的属性
    //索引无效可以接受放入操作
    if(!index.isValid())
         return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;

    //索引有效，可以接受拖拽和放入操作
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable        //返回基类的flag并且让他可以编辑
            | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

bool StringListModel::setData(const QModelIndex& index,const QVariant &value, int role ){

    //当编辑的时候，view就会自动调用，把对应的index和value的值就会设置进去

    if(index.isValid() && role == Qt::EditRole){

        stringList.replace(index.row(), value.toString());      //取到Index目前的行，替换成value的值

        emit dataChanged(index, index);     //通知view去渲染左上角到右下角的view，这里是只index这一行
        return true;
    }

    return false;
}

bool StringListModel::insertRows(int position, int rows,const QModelIndex & index ){
    beginInsertRows(QModelIndex(), position, position + rows -1);   //插入行前需要这个，哪个索引下修改，开始位置，插入到第几行

    for(int row = 0; row < rows; ++ row){       //插入
        stringList.insert(position + row, QString::number(row));  //插入位置，插入的字符
    }
    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int position, int rows,const QModelIndex & index ){

    beginRemoveRows(QModelIndex(), position, position+ rows-1);     //删除前也需要，告诉view要修改了

    for(int row=0; row < rows; ++ row){
        stringList.removeAt(position);      //移除
    }
    endRemoveRows();
    return true;
}

//拖放时导出的类型
QStringList StringListModel:: mimeTypes() const{
    QStringList types;
    //自定义类型
    types << "application/zack.list";
    return types;
}

//将拖放的数据放入mimedata中
QMimeData *StringListModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData * mimeData = new QMimeData();
    QByteArray encodeData;      //字节数组
    QDataStream stream(&encodeData, QIODevice::WriteOnly);  //初始化一个数据流对象，关联到字节数组，设置为只写模式，将stream写入encodeData

    foreach(const QModelIndex& index, indexes){
        if(index.isValid()){
            QString text = data(index, Qt::DisplayRole).toString();     //从模型中获取index处的displayRole数据
            stream << text;     //将文本数据放入到数据流中
        }
    }

    //将数据放入到QMimeData中
    mimeData->setData("application/zack.list", encodeData);
    return mimeData;

}

bool StringListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    //如果放入的动作是ignoreaction
    if(action == Qt::IgnoreAction){
        return true;
    }
    //如果数据的格式不是指定的格式，那么返回false
    if(!data->hasFormat("application/zack.list")){
        return false;
    }

    //因为这里是列表， 只用一列， 所以列大于0时返回false
    if(column > 0){
        return false;
    }

    //设置开始插入行
    int beginRow;
    if(row != -1){
        beginRow = row;
    }else if(parent.isValid()){
        beginRow = parent.row();    //如果row是-1且父节点有效，代表起始行是parent的行号
    }else {
        beginRow = rowCount(QModelIndex());     //如果都无效，那就是当前层是最顶层，设模型末尾为开始行数
    }

    //将数据从QMimeData 中读取出来， 然后插入到模型中
    QByteArray encodeData = data->data("application/zack.list");

    QDataStream stream(&encodeData, QIODevice::ReadOnly);   //stream流，只读

    QStringList newItems;       //统计插入的数据
    //统计插入的行数(要插入几行)
    int rows = 0;
    while(!stream.atEnd()){
        QString text;
        stream >> text;
        newItems << text;
        ++ rows;
    }
    //插入指定行数
    insertRows(beginRow, rows, QModelIndex());
    //批量修改行数数据
    foreach(const QString& text, newItems){
        QModelIndex idx = index(beginRow, 0, QModelIndex());    //获取行和第0列的项的索引
        setData(idx,text);
        beginRow++;
    }

    return true;
}

Qt::DropActions StringListModel::supportedDropActions() const
{
    //设置支持放入动作,允许copy和move
    return Qt::CopyAction | Qt::MoveAction;
}
