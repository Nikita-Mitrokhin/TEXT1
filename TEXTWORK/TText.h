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
    PTTextLink pFirst;      // ��������� ����� ������
    PTTextLink pCurrent;    // ��������� ������� ������
    stack<PTTextLink> Path; // ���� ���������� �������� �� ������
                            // (����� pCurrent � ���� �� ����������)
    // ���� � ������ ����������
    stack<PTTextLink> St;   // ���� ��� ���������
    PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
    void PrintText (PTTextLink ptl);        // ������ ������ �� ����� ptl
    PTTextLink ReadText(ifstream &TxtFile); // ������ ������ �� ����� TxtFile
	PTTextLink WriteText (ofstream &TxtFile, PTTextLink ptl);	//������ ������ � ����
  public:
    TText(PTTextLink pl=NULL);
   ~TText() { pFirst = NULL; }
    PTText GetCopy();
    // ���������
    int GoFirstLink (void);  // ������� � ������ ������
    int GoDownLink  (void);  // ������� � ����. ������ �� Down
    int GoNextLink  (void);  // ������� � ����. ������ �� Next
    int GoPrevLink  (void);  // ������� � ����. ������� � ������
    // ������
    string GetLine  (void);  // ������ ������� ������
    void SetLine (string s); // ������ ������� ������
    // �����������
    void InsDownLine   (string s); // ������� ������ � ����������
    void InsDownSection(string s); // ������� ������� � ����������
    void InsNextLine   (string s); // ������� ������ � ��� �� ������
    void InsNextSection(string s); // ������� ������� � ��� �� ������
    void DelDownLine   (void);     // �������� ������ � ����������
    void DelDownSection(void);     // �������� ������� � ����������
    void DelNextLine   (void);     // �������� ������ � ��� �� ������
    void DelNextSection(void);     // �������� ������� � ��� �� ������
    // ��������
    int Reset      (void);         // ���������� �� ������ ������
    int IsTextEnded(void) const;   // ������� ��������� ?
    int GoNext     (void);         // ������� � ��������� ������
    // ������ � �������
    void Read (char *pFileName);   // ���� ������ �� �����
    void Write(char *pFileName);   // ����� ������ � ����
    // ������
    void Print(void);              // ������ ������
};
#endif
// end of ttext.h
