#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QObject>
class MyHighlighter:public QSyntaxHighlighter
{
     Q_OBJECT
public:
    MyHighlighter();
    explicit MyHighlighter(QObject* parent = 0);
    ~MyHighlighter();
protected:
    //重写实现高亮构造
    void highlightBlock(const QString& text);
};

#endif // MYHIGHLIGHTER_H
