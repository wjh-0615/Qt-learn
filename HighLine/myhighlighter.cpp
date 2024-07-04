#include "myhighlighter.h"
#include <QTextCharFormat>
#include <QFont>
#include <QString>
#include <QRegExp>
MyHighlighter::MyHighlighter(QObject *parent):QSyntaxHighlighter (parent)
{

}

MyHighlighter::~MyHighlighter()
{

}

void MyHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myFormat;
    myFormat.setFont(QFont(("微软雅黑"),13,QFont::Bold,true));
    myFormat.setForeground(Qt::green);  //设置字体颜色
    //匹配char
    QString pattern = "\\bchar\\b";     //正则表达式匹配模式
    //char单独出现就匹配，\b表示至少有一个不是\w(：字母数字和下划线),也就是说\b是一个单词的结尾后的空格,\\b是单词边界

    //创建正则表达式
    QRegExp express(pattern);
    //从索引0的位置开始匹配
    int index = text.indexOf(express);  //返回正则表达式的第一次匹配索引，找不到就返回-1
    while (index>0) {
        int matchLen = express.matchedLength();     //匹配到的字符串长度
        //对匹配的字符串设置高亮
        setFormat(index, matchLen, myFormat);       //开始索引，长度，和字符格式
        index = text.indexOf(express, index+matchLen);      //从之后位置继续开始，直到找不到会返回-1
    }

}
