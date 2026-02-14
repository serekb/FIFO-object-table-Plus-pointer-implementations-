#include "Global.h"
QInfo::QInfo(int key, int n1, int n2)
{
    this->pTab = new int[2];
    this->key = key;
    this->pTab[0] = n1;
    this->pTab[1] = n2;
}
ostream& operator << (ostream& out, const QINFO& inf)
{
    out << "Klucz= " << inf.key << endl << "pierwszy element tablicy= " << inf.pTab[0] << endl <<
        "drugi element tablicy= " << inf.pTab[1] << endl;
    return out;
}