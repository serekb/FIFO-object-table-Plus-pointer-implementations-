#pragma once
#include "Global.h" // dostarczany przez uzytkownika tej kolejki
#include <iostream>
#define FQUEUE_ALLOC_ERROR 0x01
#define FQUEUE_EMPTY_ERROR 0x02
#define FQUEUE_OVERFLOW 0x04
#define FQUEUE_OTHER_ERROR 0xFF
template<class T> class QFifo;
template<class T> class FQItem;
class FQueueException
{
public:
    FQueueException(int errCode = FQUEUE_OTHER_ERROR) { mErrCode = errCode; }
    const char* getReason();
private:
    int mErrCode;
};
inline const char* FQueueException::getReason()
{
    switch(mErrCode)
    {
    case FQUEUE_ALLOC_ERROR: return "ERROR: allocating memory error\n";
    case FQUEUE_EMPTY_ERROR: return "ERROR: improper Fifo queue size\n";
    case FQUEUE_OVERFLOW: return "ERROR: Fifo queue full\n";
    default: return "other ERROR\n";
    }
}
template<class T> class FQItem
{
private:
    T pInfo;
    FQItem<T>* pNext;
public:
    FQItem<T>( T pInfo = NULL );
    virtual ~FQItem<T>();
    T getInfo() const;
    FQItem<T>* getNext() const;
    void setInfo( T pInfo );
    void setNext( FQItem<T>* pNext );

    friend class Qfifo;
};   //FIFO Queue Item
template<class T> FQItem<T>::FQItem<T>( T pInfo )
{
    this->pInfo = pInfo;
    pNext = NULL;
}
template<class T> FQItem<T>::~FQItem<T>()
{

}
template<class T> T FQItem<T>::getInfo() const
{
    return pInfo;
}
template<class T> FQItem<T>* FQItem<T>::getNext() const
{
    return pNext;
}
template<class T> void FQItem<T>::setInfo(T pInfo)
{
    this->pInfo = pInfo;
}
template<class T> void FQItem<T>::setNext(FQItem<T>* pNext)
{
    this->pNext = pNext;
}
template<class T> class QFifo
{
private:
    FQItem<T>* pHead;  // ptr to the first queue item
    FQItem<T>* pTail;  // ptr to the last queue item  /// typ kolejkowy
    void FQDel();
public:
    QFifo<T>(); // queue initiating  (NULL - fail)
    virtual ~QFifo();
    FQItem<T>* getTail() const;
    void setTail(FQItem<T>* pTail);
    FQItem<T>* getHead() const;
    void setHead(FQItem<T>* pHead);


    bool     FQEmpty() const;          // if FIFO empty returned 1 else 0
    bool     FQEnqueue(T x); // insert new item at the end //zwraca 0
    T FQDequeue();        // take out the first item    //zwraca int_min  
    void    FQClear();          // clears the queue
    void FQPrint();

};
template<class T> FQItem<T>* QFifo<T>::getTail() const
{
    return pTail;
}
template<class T> void QFifo<T>::setTail(FQItem<T>* pTail)
{
    this->pTail = pTail;
}
template<class T> FQItem<T>* QFifo<T>::getHead() const
{
    return pHead;
}
template<class T> void QFifo<T>::setHead(FQItem<T>* pHead)
{
    this->pHead = pHead;
}
template<class T> QFifo<T>::QFifo<T>()
{
    pHead = NULL;
    pTail = NULL;
}

template<class T> QFifo<T>::~QFifo()
{
    while(!FQEmpty())
        FQDel();
}
template<class T> bool QFifo<T>::FQEmpty() const
{
    return !(this->pHead);
}

template<class T> bool QFifo<T>::FQEnqueue(T x)
{
    //if(!q) return 0;
    FQItem<T>* p = new(std::nothrow) FQItem<T>(x);
    if(p == NULL)
    {
        throw FQueueException(FQUEUE_ALLOC_ERROR);
        return 0;
    }
    p->setInfo(x);
    p->setNext(NULL);
    if(!getHead())
        setHead(p);
    else
        getTail()->setNext(p);
    setTail(p);
    return 1;
}
//zwraca 0 // insert new item at the end

template<class T> T QFifo<T>::FQDequeue()
{
    if(!FQEmpty())
    {
        T val = getHead()->getInfo();
        FQDel();
        return val;
    }
    throw FQueueException(FQUEUE_EMPTY_ERROR);
}
//zwraca int_min      // take out the first item

template<class T> void QFifo<T>::FQClear() // sprawdzam czy freemem NULL
{
    while(!FQEmpty())
        delete FQDequeue();
}
template<class T> void QFifo<T>::FQDel()// removes only first item
{
    if(FQEmpty())
        throw FQueueException(FQUEUE_EMPTY_ERROR);
    FQItem<T>* p = getHead();
    setHead(p->getNext());
    if(!getHead())
        setTail(NULL);
    delete p;
    //free(p);
}
// removes only first item
template <class T> void QFifo<T>::FQPrint()
{
    FQItem<T>* p = getHead();
    while(p)
    {
        cout << *(p->getInfo());
        p = p->getNext();
    }
}




