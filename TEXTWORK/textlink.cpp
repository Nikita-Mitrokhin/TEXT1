#include "stdafx.h"
#include <conio.h>
#include "textlink.h"
#include "ttext.h"

void TTextLink :: InitMemSystem (int size) { // инииализация памяти
  char Line[100];
  MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink)*size];
  MemHeader.pFree  = MemHeader.pFirst;
  MemHeader.pLast  = MemHeader.pFirst + (size-1);
  PTTextLink pLink = MemHeader.pFirst;
  for ( int i=0; i< size-1; i++, pLink++ ) { // размерка памяти
    pLink->pNext = pLink+1;
  }
  pLink->pNext = NULL;
}

void TTextLink :: PrintFreeLink (void) { // печать свободных звеньев
  PTTextLink pLink = MemHeader.pFree;
  cout << "List of free links" << endl;
  for ( ; pLink != NULL; pLink = pLink->pNext )
    cout << pLink->Str << endl;
}

void * TTextLink :: operator new (size_t size) { // выделение звена
  PTTextLink pLink = MemHeader.pFree;
  if ( MemHeader.pFree != NULL ) MemHeader.pFree = pLink->pNext;
  return pLink;
}

void TTextLink :: operator delete (void *pM) { // освобождение звена

	  PTTextLink pLink = (PTTextLink)pM;
 pLink->pNext=MemHeader.pFree;
 MemHeader.pFree=pLink;
}

void TTextLink :: MemCleaner (TText &txt, int &count)
{
	string st, st1;
	count = 0;
	for ( txt.Reset(); !txt.IsTextEnded(); txt.GoNext() )
	{
		if (st.find("&&&") != 0)
		{
			st = txt.GetLine();
			st1 = "&&&";
			st1 += txt.GetLine();
			txt.SetLine(st1);
		}
	} // for 
	PTTextLink pLink = MemHeader.pFree;
	for (  ; pLink != NULL; pLink = pLink->pNext)
	{
		strcpy_s(pLink->Str, "&&&");
	}
	pLink = MemHeader.pFirst;
	for (; pLink <= MemHeader.pLast; pLink++)
	{
		if ( strstr(pLink->Str,"&&&") != NULL )
		{
			strcpy_s(pLink->Str, pLink->Str+3);
		}
		else 
		{ 
			delete pLink; count++; 
		}
	} 
}
