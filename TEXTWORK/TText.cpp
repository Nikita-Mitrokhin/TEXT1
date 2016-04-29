#include "stdafx.h"
#define BufLength 80
#include <conio.h>
#include <string>

#include "ttext.h"
using namespace std;

static char StrBuf[BufLength + 1]; // буфер для ввода строк
static int  TextLevel;           // номер текущего уровня текста

TText::TText(PTTextLink pl) {
	if (pl == NULL) pl = new TTextLink();
	pFirst = pl;
}

// навигация
int TText::GoFirstLink(void) { // переход к первой строке
	while (!Path.empty()) Path.pop(); // очистка стека
	pCurrent = pFirst;
	if (pCurrent == NULL) SetRetCode(TextError); else SetRetCode(TextOK);
	return RetCode;

}

int TText::GoDownLink(void) { // переход к след. строке по Down
	SetRetCode(TextError);
	if (pCurrent != NULL)
	if (pCurrent->pDown != NULL) {
		Path.push(pCurrent);
		pCurrent = pCurrent->pDown;
		SetRetCode(TextOK);
	}
	return RetCode;
}

int TText::GoNextLink(void) { // переход к след. строке по Next

	SetRetCode(TextError);
	if (pCurrent != NULL)
	if (pCurrent->pNext != NULL) {
		Path.push(pCurrent);
		pCurrent = pCurrent->pNext;
		SetRetCode(TextOK);
	}
	return RetCode;

}



int TText::GoPrevLink(void) { // переход к пред. позиции в тексте
	if (Path.empty()) SetRetCode(TextNoPrev);
	else {
		pCurrent = Path.top(); Path.pop();
		SetRetCode(TextOK);
	}
	return RetCode;
}

// доступ
string TText::GetLine(void) { // чтение текущей строки
	if (pCurrent == NULL) return string("");
	else return string(pCurrent->Str);
}

void TText::SetLine(string s) { // замена текущей строки
	if (pCurrent == NULL) SetRetCode(TextError);
	else strncpy(pCurrent->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = '\0';
}

// модификация
void TText::InsDownLine(string s) { // вставка строки в подуровень
	if (pCurrent == NULL) SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", pd, NULL);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0'; // установка, если s длиннее Str
		pCurrent->pDown = pl;             // установка указателя на новую строку
		SetRetCode(TextOK);
	}
}

void TText::InsDownSection(string s) { // вставка раздела в подуровень
	if (pCurrent == NULL) SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", NULL, pd);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0'; // установка, если s длиннее Str
		pCurrent->pDown = pl;             // установка указателя на новую строку
		SetRetCode(TextOK);
	}
}

void TText::InsNextLine(string s) { // вставка строки в том же уровне


	if (pCurrent == NULL)
	{
		SetRetCode(TextError);
	}
	else
	{
		PTTextLink pd = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", pd, NULL);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOK);
	}
}

void TText::InsNextSection(string s) { // вставка раздела в том же уровне

	if (pCurrent == NULL)
	{
		SetRetCode(TextError);
	}
	else
	{
		PTTextLink pd = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", NULL, pd);
		strncpy_s(pl->Str, s.c_str(), TextLineLength + 1);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOK);
	}


}

void TText::DelDownLine(void) { // удаление строки в подуровне
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pDown != NULL) {
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == NULL) pCurrent->pDown = pl2; // только для атома
	}
}

void TText::DelDownSection(void) { // удаление раздела в подуровене
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pDown != NULL) {
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
}

void TText::DelNextLine(void) { // удаление строки в том же уровне
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pNext != NULL) {
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == NULL)
		{
			pCurrent->pNext = pl2;
		}
	}
}

void TText::DelNextSection(void) { // удаление раздела в том же уровне
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pNext != NULL) {
		PTTextLink pl1 = pCurrent->pNext;// pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pNext = pl2;
	}

}

// итератор
int TText::Reset(void) { // установить на первую запись
	while (!St.empty()) St.pop(); // очистка стека
	// текущая строка в стеке не хранится
	// исключение - первая строка текста, которая на дне стека
	pCurrent = pFirst;
	if (pCurrent != NULL) {
		St.push(pCurrent);
		if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
		if (pCurrent->pDown != NULL) St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::IsTextEnded(void) const { // таблица завершена ?
	return !St.size();
}

int TText::GoNext(void) { // переход к следующей записи
	if (!IsTextEnded()) {
		pCurrent = St.top(); St.pop(); // если после выборки стек пуст, значит
		if (pCurrent != pFirst) {    // первая строка текста уже была обработана
			if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
			if (pCurrent->pDown != NULL) St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

// копирование текста
PTTextLink TText::GetFirstAtom(PTTextLink pl) { // поиск первого атома
	PTTextLink tmp = pl;
	while (!tmp->IsAtom()) {
		St.push(tmp); tmp = tmp->GetDown();
	}
	return tmp;
}

PTText TText::GetCopy() { // копирование текста
	PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;
	if (pFirst != NULL) {
		while (!St.empty()) St.pop(); // очистка стека
		while (1) {
			if (pl != NULL) {  // переход к первому атому
				pl = GetFirstAtom(pl); St.push(pl);
				pl = pl->GetDown();
			}
			else if (St.empty()) break;
			else {
				pl1 = St.top(); St.pop();
				if (strstr(pl1->Str, "Copy") == NULL) { // первый этап создания копии
					// создание копии - pDown на уже скопированный подуровень

					pl2 = new TTextLink("Copy", pl1, cpl);   // pNext на оригинал
					St.push(pl2);
					pl = pl1->GetNext();
					cpl = NULL;


				}
				else { // второй этап создания копии

					pl2 = pl1->GetNext();
					strcpy(pl1->Str, pl2->Str);
					pl1->pNext = cpl;
					cpl = pl1;

				}
			}
		}
	}
	return new TText(cpl);
}

// печать текста
void TText::Print() {
	TextLevel = 0;
	PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl)
{
	if (ptl != NULL)
	{
		for (int i = 0; i < TextLevel; i++)
		{
			cout << " ";
		}
		cout << ptl->Str << endl;
		TextLevel++; PrintText(ptl->GetDown());
		TextLevel--; PrintText(ptl->GetNext());
	}
}


// чтение текста из файла
void TText::Read(char *pFileName) {
	ifstream TxtFile(pFileName);
	TextLevel = 0;
	if (TxtFile != NULL) pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(ifstream &TxtFile) {
	PTTextLink pHead, ptl;
	pHead = ptl = new TTextLink();
	while (TxtFile.eof() == 0) {
		TxtFile.getline(StrBuf, BufLength, '\n');
		if (StrBuf[0] == '}') { TextLevel--; break; }
		else if (StrBuf[0] == '{') { // рекурсия
			TextLevel++; ptl->pDown = ReadText(TxtFile);
		}
		else {  // присоединение следующей строки
			ptl->pNext = new TTextLink(StrBuf, NULL, NULL);
			ptl = ptl->pNext;
		}
	}
	ptl = pHead;
	if (pHead->pDown == NULL) { // удаление первой строки, если нет подуровня
		pHead = pHead->pNext; delete ptl;
	}
	return pHead;
}

void TText::Write(char *pFileName)
{
	ofstream TxtFile(pFileName);
	TextLevel = 0;


	pFirst = WriteText(TxtFile, pFirst);

}


PTTextLink TText::WriteText(ofstream &TxtFile, PTTextLink ptl)
{
	if (ptl != NULL)
	{
		TxtFile << "{\n";
		TxtFile << ptl->Str << '\n';
		if (ptl->GetDown() != NULL)
		{
			TextLevel++;
			WriteText(TxtFile, ptl->GetDown());
		}
		TextLevel--;
		TxtFile << "}\n";
		WriteText(TxtFile, ptl->GetNext());
	}
	return ptl;
}