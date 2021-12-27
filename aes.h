#ifndef AES_H
#define AES_H

#include <QObject>

class AES : public QObject
{
    Q_OBJECT
public:
    explicit AES(QObject *parent = nullptr);
        int getLeft4Bit(int num);
        int getRight4Bit(int num);
        int getNumFromSBox(int index);
        int getIntFromChar(char c);
        void convertToIntArray(char *str, int pa[4][4]);//字符串->状态矩阵
        int getWordFromStr(char *str);
        void splitIntToArray(int num, int array[4]);
        void leftLoop4int(int array[4], int step);
        int mergeArrayToInt(int array[4]);
        int T(int num, int round);
        void extendKey(char *key);
        void addRoundKey(int array[4][4], int round);
        void subBytes(int array[4][4]);
        void shiftRows(int array[4][4]);
//槽函数可以写在public下,返回值是void,需要申明和实现,可以有参数,可以发生重载
        void encryption(char *p,char *key);
        void deencryption(char *c,char *key);

        int GFMul2(int s);
        int GFMul3(int s);
        int GFMul4(int s);
        int GFMul8(int s);
        int GFMul9(int s);
        int GFMul11(int s);
        int GFMul12(int s);
        int GFMul13(int s);
        int GFMul14(int s);
        int GFMul(int n, int s);

        void mixColumns(int array[4][4]);
        void convertArrayToStr(int array[4][4], char *str);//状态矩阵->字符串
        int checkKeyLen(int len);
        int getNumFromS1Box(int index);
        void deSubBytes(int array[4][4]);
        void rightLoop4int(int array[4], int step);
        void deShiftRows(int array[4][4]);
        void deMixColumns(int array[4][4]);
        void addRoundTowArray(int aArray[4][4],int bArray[4][4]);//两个数组异或
        void getArrayFrom4W(int i, int array[4][4]);
        void strXor(char *a,char *b);
private:
    static const int SBox[16][16];
    static const int invSBox[16][16];
    static const int Rcon[10];
    static const int colM[4][4];
    static const int deColM[4][4];
    int w[44];
signals:
    /*自定义信号
返回值是void,只需要申明,不需要实现,可以有参数，可以有重载*/


};

#endif // AES_H
