#ifndef MODE_H
#define MODE_H

#include <QObject>
#include"aes.h"

class Mode : public QObject
{
    Q_OBJECT
public:
            explicit Mode(QObject *parent = nullptr);
            int ECB(char *p,char *key);
            void deECB(char *c,char *key,int plen);

            int CBC(char *p,char *key);
            void deCBC(char *c,char *key,int plen);

            int CTR(char *p,char *key);
            void deCTR(char *c,char *key,int len);

            void padding(char *in,int &len);
        private:
            AES aes;

signals:

};

#endif // MODE_H
