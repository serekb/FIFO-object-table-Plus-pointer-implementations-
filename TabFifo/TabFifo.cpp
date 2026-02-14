#include <iostream>
#include "TFifo.h"

int main()
{
    try {
    TFifo<QINFO*> q = TFifo<QINFO*>(4);

        //dodac 4 elementy do kolejki (wydrukowac kolejke)
        for(int i = 1; i <= 4; i++)
        {
            QINFO* p = new QINFO(i, i + 1, i + 2);
            q.TFEnqueue(p);
        }
        printf("kolejka pierwsza (4 elementy):\n");
        q.TFPrint();
        QINFO* p = new QINFO(1, 1 + 1, 1 + 2);
        //q.TFEnqueue(p); // tu spoziewam sie bledu
        // usunac trzy elementy (wypisac info)
        printf("\nUsuniete elementy:\n");
        for(int i = 1; i <= 3; i++)
        {
            QINFO* p = q.TFDequeue();
            cout << *p;
            delete p;
        }
        //dodac 2 elementy (wydrukowac kolejke)
        for(int i = 1; i <= 2; i++)
        {
            QINFO* p = new QINFO(i, i + 1, i + 2);
            q.TFEnqueue(p);        
        }
        printf("\nkolejka trzecia(3 elementy) :\n");
        q.TFPrint();
        //wyczyscic kolejke
        q.TFClear();
        //dodac trzy elementy (wydrukowac kolejke)
        for(int i = 1; i <= 3; i++)
        {
            QINFO* p = new QINFO(i, i + 1, i + 2);
            q.TFEnqueue(p);
        }
        printf("\nkolejka czwarta (3 elementy):\n");
        q.TFPrint();
        //usunac jeden element (wypisac info) (wydrukowac kolejke)

        QINFO* p1 = q.TFDequeue();
        printf("\nUsuniety element\n");
        cout << *p1;
        delete p;
        printf("\nkolejka piata (2 elementy):\n");
        q.TFPrint();
    }
    catch(TFException e)
    {
        cout << e.getReason() << endl;
    }
    return 0;
}
/*
class TFItem
{
private:
    QINFO* pInfo;
    TFItem* pNext;
public:
    TFItem(QINFO* pInfo = NULL);
    virtual ~TFItem();
    QINFO* getInfo() const;
    TFItem* getNext() const;
    void setInfo(QINFO* pInfo);
    void setNext(TFItem* pNext);

    friend class TFifo;
};   //FIFO Queue Item
inline TFItem::~TFItem()
{

}
inline QINFO* TFItem::getInfo() const
{
    return pInfo;
}
inline TFItem* TFItem::getNext() const
{
    return pNext;
}
inline void TFItem::setInfo(QINFO* pInfo)
{
    this->pInfo = pInfo;
}
inline void TFItem::setNext(TFItem* pNext)
{
    this->pNext = pNext;
}
TFItem::TFItem(QINFO* pInfo)
{
    setInfo(pInfo);
    pNext = NULL;
}*/