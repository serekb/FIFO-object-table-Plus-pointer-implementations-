#include <iostream>
#include "QFifo.h"
using namespace std;

int main()
{
    try {

    QFifo<QINFO*> q = QFifo<QINFO*>();

    //dodac 4 elementy do kolejki (wydrukowac kolejke)
    for(int i = 1; i <= 4; i++)
    {
        QINFO* p = new QINFO(i, i + 1, i + 2);
        q.FQEnqueue(p);
    }
    printf("kolejka pierwsza (4 elementy):\n");
    q.FQPrint();
    // usunac trzy elementy (wypisac info)
    printf("\nUsuniete elementy:\n");
    for(int i = 1; i <= 3; i++)
    {
        QINFO* p = q.FQDequeue();
        cout << *p;
        delete p;
    }
    //wypisac pozostala kolejke (1 element)
    printf("\nkolejka druga (1 element):\n");
    q.FQPrint();
    //dodac 2 elementy (wydrukowac kolejke)
    for(int i = 1; i <= 2; i++)
    {
        QINFO* p = new QINFO(i, i + 1, i + 2);
        q.FQEnqueue(p);         //!!!!
    }
    printf("\nkolejka trzecia(3 elementy) :\n");
    q.FQPrint();
    //wyczyscic kolejke
    q.FQClear();
    //dodac trzy elementy (wydrukowac kolejke)
    for(int i = 1; i <= 3; i++)
    {
        QINFO* p = new QINFO(i, i + 1, i + 2);
        q.FQEnqueue(p);
    }
    printf("\nkolejka czwarta (3 elementy):\n");
    q.FQPrint();
    //usunac jeden element (wypisac info) (wydrukowac kolejke)

    QINFO* p = q.FQDequeue();
    printf("\nUsuniety element\n");
    cout << *p;
    delete p;

    printf("\nkolejka piata (2 elementy):\n");
    q.FQPrint();
    //usunac ca³¹ kolejkê  
    //delete &q;
    }
    catch( FQueueException e )
    {
        cout << e.getReason() << endl;
    }
    return 0;
}

