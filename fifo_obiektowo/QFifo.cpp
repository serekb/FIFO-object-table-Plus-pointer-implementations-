#include "QFifo.h"
#include <iostream>

QFifo::QFifo()
{
    pHead = NULL;
    pTail = NULL;
}

QFifo::~QFifo()
{
    while(!FQEmpty())
        FQDel();
}
bool QFifo::FQEmpty() const
{
    return !(this->pHead);
}

bool QFifo::FQEnqueue( QINFO* x )
{
    //if(!q) return 0;
    FQItem* p = new(std::nothrow) FQItem(x);
    if(p==NULL)
    {
        throw FQueueException(FQUEUE_ALLOC_ERROR);
        return 0;
    }
    p->setInfo(x);
    p->setNext(NULL);
    if( !getHead() )
        setHead(p);
    else
        getTail()->setNext(p);
    setTail(p);
    return 1;
}
//zwraca 0 // insert new item at the end

QINFO* QFifo::FQDequeue()
{
    if(!FQEmpty())
    {
        QINFO* val = getHead()->getInfo();
        FQDel();
        return val;
    }
    throw FQueueException(FQUEUE_EMPTY_ERROR);
}
//zwraca int_min      // take out the first item

void QFifo::FQClear() // sprawdzam czy freemem NULL
{
    while(!FQEmpty())
        free( FQDequeue() );
}
ostream& operator << ( ostream& out, const QFifo& queue )
{
    FQItem* p = queue.getHead();
    while(p)
    {
        out << *(p->getInfo());
        p = p->getNext();
    }
    return out;
}
void QFifo::FQDel()// removes only first item
{
    if(FQEmpty())
        throw FQueueException(FQUEUE_EMPTY_ERROR);
    FQItem* p = getHead();
    setHead(p->getNext());
    if(!getHead())
        setTail(NULL);
    //delete p;
    free( p);
}
// removes only first item

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
//zrobic global.cpp
//nowy projekt w tym samym solution tabFifo
//w konstruktorze genreujemy kolejke jako tablice wskaznikow na informacje
//wskaznikow na qinfo z globala
//2 indeksy nHead i nTail moga byæ 0
//pole sprawdajace ile jest elementow w kolejce
//pole ile jest maksymalnie elementow w kolejce
// inkrementowanie indeksów bez badania warunku
