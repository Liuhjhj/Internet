#ifndef BASE64_H
#define BASE64_H

#include <QObject>
#include <stdio.h>
#include <string.h>
#include <assert.h>
using namespace std;

class base64 : public QObject
{
    Q_OBJECT

public:
    string encode(char *data);

signals:

};

#endif // BASE64_H
