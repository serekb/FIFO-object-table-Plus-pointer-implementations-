#pragma once
#include "Global.h"
#include <iostream>
#define TFIFO_ALLOC_ERROR 0x01
#define TFIFO_EMPTY_ERROR 0x02
#define TFIFO_OVERFLOW 0x04
#define TFIFO_WRONG_SIZE 0x05
#define TFIFO_OTHER_ERROR 0xFF
template<class T> class TFifo;
template<class T> class TFItem;
class TFException
{
public:
    TFException(int errCode = TFIFO_OTHER_ERROR) { mErrCode = errCode; }
    const char* getReason();
private:
    int mErrCode;
};
inline const char* TFException::getReason()
{
    switch(mErrCode)
    {
    case TFIFO_ALLOC_ERROR: return "ERROR: allocating memory error\n";
    case TFIFO_EMPTY_ERROR: return "ERROR: improper tabFifo queue size\n";
    case TFIFO_OVERFLOW: return "ERROR: Fifo queue full\n";
    case TFIFO_WRONG_SIZE: return "ERROR: WRONG SIZE\n";
    default: return "other ERROR\n";
    }
}

template<class T> class TFifo
{
private:
    T* pTFqueue;
    int nHead; 
    int nTail;
    int nNoElem;
    int nMaxElem;
    void TFDel();
public:
    TFifo<T>(int nMaxElem); // queue initiating  (NULL - fail)
    virtual ~TFifo();
    int getTail() const;
    void setTail(int pTail);
    int getHead() const;
    void setHead(int pHead);
    int getMaxElem() const;
    void setMaxElem( int max );
    int getNoElem() const;
    void setNoElem(int num);

    bool     TFEmpty() const;          // if FIFO empty returned 1 else 0
    bool     TFEnqueue(T x); // insert new item at the end //zwraca 0
    T TFDequeue();        // take out the first item    //zwraca int_min  
    void    TFClear();          // clears the queue
    void TFPrint();

};
template<class T> int TFifo<T>::getTail() const
{
    return nTail;
}
template<class T> void TFifo<T>::setTail( int nTail )
{
    this->nTail = nTail;
}
template<class T> int TFifo<T>::getHead() const
{
    return nHead;
}
template<class T> void TFifo<T>::setHead( int nHead )
{
    this->nHead = nHead;
}
template<class T> int TFifo<T>::getMaxElem() const
{
    return nMaxElem;
}
template<class T> void TFifo<T>::setMaxElem( int max )
{
    this->nMaxElem = max;
}
template<class T> int TFifo<T>::getNoElem() const
{
    return nNoElem;
}
template<class T> void TFifo<T>::setNoElem(int num)
{
    this->nNoElem = num;
}
template<class T> TFifo<T>::TFifo(int nMaxElem)
{
    if(nMaxElem < 1)
        throw TFException( TFIFO_WRONG_SIZE);
    this->nHead = NULL;
    this->nTail = NULL;
    this->nMaxElem = nMaxElem;
    this->nNoElem = 0;
    this->pTFqueue = new T [nMaxElem];
}
template<class T> TFifo<T>::~TFifo()
{
    TFClear();
    //delete[] pTFqueue;
}
template<class T> bool TFifo<T>::TFEmpty() const
{
    return (nNoElem == 0);
}
// if FIFO empty returned 1 else 0

template<class T> bool TFifo<T>::TFEnqueue(T x)
{
    if( !x )
        throw TFException( TFIFO_ALLOC_ERROR );
    if( nNoElem == nMaxElem )
    {
        throw TFException( TFIFO_OVERFLOW );
    }
    pTFqueue[nTail] = x;
    nTail = (nTail + 1) % nMaxElem;
    nNoElem++;
}
//zwraca 0 // insert new item at the end

template<class T> T TFifo<T>::TFDequeue() // jeszcze nie dziala dobrze
{
    if(!TFEmpty())
    {
        T val = pTFqueue[nHead];
        TFDel();
        return val;
    }
    throw TFException(TFIFO_EMPTY_ERROR);
}
//zwraca int_min      // take out the first item

template<class T> void TFifo<T>::TFClear() // sprawdzam czy freemem NULL
{
    while(!TFEmpty())
    {
        T pInfo = TFDequeue();
        delete pInfo;
    }
}

template<class T> void TFifo<T>::TFDel()// removes only first item
{
    if( TFEmpty() )
        throw TFException( TFIFO_EMPTY_ERROR );
    pTFqueue[nHead] = nullptr;
    nNoElem--;
    nHead = (nHead + 1) % nMaxElem;
}
template<class T> void TFifo<T>::TFPrint()
{
    if( TFEmpty() )
        throw TFException( TFIFO_EMPTY_ERROR );
    int n = nHead;
    for(int i = 0; i < nNoElem; i++)
    {
        cout << *(pTFqueue[n]);
        n = (n + 1) % nMaxElem;
    }
}


