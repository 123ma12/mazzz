#ifndef ARRAY_H
#define ARRAY_H


class Array
{
public:
    Array();
    Array(int row ,int col,int boomNum);
    ~Array();
    int getcol();
    int getrow();
    int getboomNum();
    int getredFlagNum();
    int gettimeNum();
    void minusredFlagNum();
    void addredFlagNum();
    void addtimeNum();
    int **p;
private:
    int row,col,boomNum;
    int timeNum,redFlagNum;
};

#endif // ARRAY_H
