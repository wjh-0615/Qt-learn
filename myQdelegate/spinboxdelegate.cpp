#include "spinboxdelegate.h"
# include <QSpinBox>

SpinBoxDelegate::SpinBoxDelegate(QObject* parent):QItemDelegate(parent)
{

}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //函数用来创造editor
    QSpinBox* editor = new QSpinBox(parent);    //这样editor会随着parent的析构而析构
    editor->setMinimum(0);
    editor->setMaximum(100);
    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //取到模型的数据，将编辑控件转化为spinbox类型，然后将数据显示在spinbox上，例如14显示不是0而是14了
    int value = index.model()->data(index,Qt::EditRole).toInt();    //获取模型，返回索引index对应item的数据
    //可以不可以设置为value = data(index,Qt::EditRole).toInt();     //不可以
    auto* spinbox = static_cast<QSpinBox*>(editor);
    spinbox->setValue(value);       //然后设置到spinbox中，即显示

}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //将spinbox修改的数值可以更新到模型的具体item中
    //先将editor转为spinbox
    auto* spinbox = static_cast<QSpinBox*>(editor);
    
    spinbox->interpretText();       //刷新spinbox
    //取到spinbox中的数值
    int value = spinbox->value();
    
    model->setData(index,value,Qt::EditRole);   //设置角色为editor，也就是可以修改
    
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //需要将spinbox代理在editor哪里显示设置好，不然只会在第一个格子显示
    editor->setGeometry(option.rect);       //显示矩形区域
}
