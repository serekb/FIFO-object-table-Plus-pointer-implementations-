#pragma once
#include <iostream>
using namespace std;
#define QINFO QInfo
class QInfo
{
private:
    int key;
    int* pTab;
public:
    QInfo( int key = 0, int n1=1, int n2=2 );
    friend ostream& operator << (ostream& out, const QINFO& inf );
};
//konstruktor  i we/wy tuttaj
//tablica 2 elem i klucz




