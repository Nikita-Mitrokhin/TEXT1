#ifndef __TEXTLINK_H
#define __TEXTLINK_H

#include <malloc.h>
#include <string.h>
#include "texters.h"
#include "datvalue.h"

#define TextLineLength  20
#define MemSize         20

class   TText;
class   TTextLink;
typedef TTextLink * PTTextLink;
typedef char TStr[TextLineLength];

class TTextMem {
  PTTextLink pFirst; // указатели на первое звено
  PTTextLink pLast;  // указатели на последнее звено
  PTTextLink pFree;  // указатели на первое свободное звено
  friend class TTextLink;
};
typedef TTextMem * PTTextMem;

class TTextLink : public TDatValue {
  protected:
    TStr Str;
    PTTextLink pNext, pDown;
    // система управления памятью
    static TTextMem MemHeader;
  public:
    static void InitMemSystem (int size=MemSize); // инииализация памяти
    static void PrintFreeLink (void);             // печать свободных звеньев
    void * operator new (size_t size);            // выделение звена
    void operator delete (void *pM);              // освобождение звена
    static void MemCleaner (TText &txt, int &count);    // сборка мусора
  public:
    TTextLink ( TStr s=NULL, PTTextLink pn=NULL, PTTextLink pd=NULL ) {
      pNext = pn; pDown = pd;
      if ( s != NULL ) strcpy(Str,s); else Str[0]='\0';
    }
   ~TTextLink() {}
    int IsAtom() { return pDown == NULL;  } // проверка атомарности звена
    PTTextLink  GetNext() { return pNext; }
    PTTextLink  GetDown() { return pDown; }
    TDatValue * GetCopy() { return new TTextLink(Str,pNext,pDown); }
  protected:
    virtual void Print(ostream &os) { os << Str; }
  friend class TText;
};
#endif
// end of textlink.h
