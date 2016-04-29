#ifndef __TTEXT_H
#define __TTEXT_H

#include <stack>
#include <fstream>
#include "datacom.h"
#include "textlink.h"

class   TText;
typedef TText * PTText;

class TText : public TDataCom {
  protected:
    PTTextLink pFirst;      // указатель корня дерева
    PTTextLink pCurrent;    // указатель текущей строки
    stack<PTTextLink> Path; // стек траектории движения по тексту
                            // (звено pCurrent в стек не включается)
    // поля и методы реализации
    stack<PTTextLink> St;   // стек для итератора
    PTTextLink GetFirstAtom(PTTextLink pl); // поиск первого атома
    void PrintText (PTTextLink ptl);        // печать текста со звена ptl
    PTTextLink ReadText(ifstream &TxtFile); // чтение текста из файла TxtFile
	PTTextLink WriteText (ofstream &TxtFile, PTTextLink ptl);	//запись текста в файл
  public:
    TText(PTTextLink pl=NULL);
   ~TText() { pFirst = NULL; }
    PTText GetCopy();
    // навигация
    int GoFirstLink (void);  // переход к первой строке
    int GoDownLink  (void);  // переход к след. строке по Down
    int GoNextLink  (void);  // переход к след. строке по Next
    int GoPrevLink  (void);  // переход к пред. позиции в тексте
    // доступ
    string GetLine  (void);  // чтение текущей строки
    void SetLine (string s); // замена текущей строки
    // модификация
    void InsDownLine   (string s); // вставка строки в подуровень
    void InsDownSection(string s); // вставка раздела в подуровень
    void InsNextLine   (string s); // вставка строки в том же уровне
    void InsNextSection(string s); // вставка раздела в том же уровне
    void DelDownLine   (void);     // удаление строки в подуровене
    void DelDownSection(void);     // удаление раздела в подуровене
    void DelNextLine   (void);     // удаление строки в том же уровне
    void DelNextSection(void);     // удаление раздела в том же уровне
    // итератор
    int Reset      (void);         // установить на первую запись
    int IsTextEnded(void) const;   // таблица завершена ?
    int GoNext     (void);         // переход к следующей записи
    // Работа с файлами
    void Read (char *pFileName);   // ввод текста из файла
    void Write(char *pFileName);   // вывод текста в файл
    // Печать
    void Print(void);              // печать текста
};
#endif
// end of ttext.h
