#include "stdafx.h"
#include <iostream>
#include <conio.h>
#pragma hdrstop
#include "ttext.h"
#pragma argsused 
#include <clocale>
#include <string>

using namespace std;


string input()
{
	std::string str2, str1, res;
	std::cin >> str1;
	std::getline(std::cin, str2);
	return str1 + str2;
}
TTextMem TTextLink::MemHeader;
int main(int argc,char* argv[])
{TTextLink::InitMemSystem();
	setlocale(LC_CTYPE, "Rus");
	char *file_name = "text_result.txt";		/* used for write */
	const int size_str = TextLineLength;		/* length of our strings */
	int number = -1;				/* value of user command */
		//
	TText text;						// �����
	
	text.Reset();

	while (number != 0)
	{	
		number = -1;
		cout << "1 - �������� ������" << endl;
		cout << "2 - �������� ������ ������" << endl;
		cout << "3 - �������� ������" << endl;
		cout << "4 - �������� ������ ������" << endl << endl;

		cout << "5 - ������� ������" << endl;
		cout << "6 - ������� ������ ������" << endl;
		cout << "7 - ������� ������" << endl;
		cout << "8 - ������� ������ ������" << endl << endl;

		cout << "9 - ������� ����" << endl;
		cout << "10 - ������� ����" << endl;
		cout << "11 - ������� � ������" << endl;
		cout << "12 - �����" << endl << endl;

		cout << "13 - ������ �� �����" << endl;
		cout << "14 - �������� � ����" << endl;
		cout << "15 - ������" << endl;
		cout << "16 - ������� ������" << endl << endl;

		cout << "0 - �����" << endl;
		
		while ((number < 0) || (number > 16))
		{
			if (cin >> number) {}
			else { cout << "It is not number. Repeat input!\n"; cin.clear(); number = -1; }
		}


		switch (number)
		{
			case 0:
			{
				break;
			}
			
			case 1:
			{
				system("cls");
				cout << "������� �������� �������:" << endl;
				text.InsNextSection(input());
				text.GoNextLink();
				break;
			}

			case 2: 
			{
				system ("cls");
				cout << "������� �������� �������:"<<endl;
				text.InsDownSection( input() );
				text.GoDownLink();
				system("pause");
				break;
			}
			
			case 3:
			{
				system("cls");
				cout << "������� ������:" << endl;
				text.InsNextLine(input());
				text.GoNextLink();
				break;
			}

			case 4:
			{
				system ("cls");
				std::cout << "������� ������: ";
				text.InsDownLine( input() );
				text.GoDownLink();
				break;
			 }
			
			case 5:
			{
				text.DelDownSection(); 
				break;
			}
			
			case 6:
			{
				text.DelNextSection(); 
				break;
			}
		
			case 7:
			{
				text.DelDownLine(); 
				break;
			}
		
			case 8: 
			{
				text.DelNextLine(); 
				break;
			}
		
			case 9:
			{
				text.GoDownLink();
				break;
			}
		
			case 10:
			{
				text.GoNextLink(); 
				break;
			}
		
			case 11:
			{
				text.GoFirstLink();
				break;
			}
		
			case 12:
			{
				text.GoPrevLink(); 
				break;
			}
		
			case 13:
			{
				system ("cls");
				text.GoFirstLink();
				text.Read(file_name);
				text.GoFirstLink();
				cout << "���� ��������"<<endl;
				system("pause");
				break;
			}
		
			case 14:
			{
				system("cls");
				text.Write(file_name);
				cout << "���� �������" << endl;
				system("pause");
				break;
			}

			case 15:
			{	
				text.Print();
				system("pause");
				break;
			}
					
			case 16:
			{
				system ("cls");
				int count;
				TTextLink :: MemCleaner(text,count);
				cout << "�������: " << count << endl;
				system("pause");
				break;
			

		}	
	}
}	
	return 0;
}