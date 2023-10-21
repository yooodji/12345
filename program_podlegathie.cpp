#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <string.h>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <chrono>
#include <Windows.h>
#include <vector>

using namespace std;

string open_file(ifstream& in_p_t);//функция для открытия файла и проверки корректности введенного названия
string out_sentence(ofstream& out_prog_text);//функция для открытия файла на вывод и проверка корректности введеного названия

//struct sentence
//{
//	string date;
//	sentence* ptr;
//};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	system("chcp 1251 >> null");
	cout << "Данная программа разработана Анастасией Боровик и  Путинцевым Иваном, студентами группы М-7О-406С-20 и предназначена для нахождения подлежащего в тексте " << endl << endl;
	ifstream in_prog_text;//поток на вывод информации из файла с текстом 
	ofstream out_prog_text;//поток на вывод полученной информации в файл 
	string text = open_file(in_prog_text);//переменная содержащая название файла с текстом 
	if (text == "Выход")
	{
		return 0;
	}
	string out_text = out_sentence(out_prog_text);
	if (out_text == "Выход")
	{
		return 0;
	}
	string buff_word;
	vector <string> sentence;
	while (!in_prog_text.eof())//пока не конец файла 
	{
		
		bool flag = false;
		int i = 1;
		while (!flag) // пока элемент слова не разделитель 
		{
			if (i == 1)
			{
				in_prog_text >> buff_word;
			}
			if ((buff_word[i] == '.') or (buff_word[i] == '!') or (buff_word[i] == '?'))//TO DO РАЗДЕЛИТЕЛЬ ИСКАТЬ С КОНЦА 
			{
				flag = true;
				++i;//для знака разделителя предложений
			}
			if (i == buff_word.size())
			{
				sentence.push_back(buff_word);
				buff_word = "";
				i = 1;//так как рассматриваем новое слово
			}
			else
			{
				++i;
			}
			
		}
		

		//вызов функции анализатора

		//for (int i = 0; i < sentence.size();++i)
		//{
		//	out_prog_text << sentence.at(i);
		//	cout << sentence.at(i);
		//}
		for (int i = 0; i < sentence.size();++i)
		{
			out_prog_text << sentence[i];
			cout << sentence[i];
		}
		sentence.clear();
		/*for (string sentc : sentence)
		{
			out_prog_text << sentc;
			cout << sentc;
		}*/

	
	}
	in_prog_text.close();
	out_prog_text.close();
	return 0; 
}




string open_file(ifstream& in_p_t)//функция для открытия файла и проверки корректности введенного названия
{
	bool flag = false;
	string m_2;
	cout << "Для выхода из программы введите слово: Выход" << endl;
	while (!flag)
	{
		int flag_m_2 = 0;//если файл открыт корректно, то меняем параметр на 1
		cout << "Введите имя существующего файла, содержащего подходящую по смыслу программы информацию. Расширение '.txt' добавляется автоматически" << endl;
		getline(cin, m_2);
		if (m_2 == "Выход")//для выхода из программы
		{
			return m_2;
		}
		m_2 += ".txt";
		cout << m_2 << endl;

		in_p_t.open(m_2);

		if (in_p_t.is_open())
		{
			cout << "Файл с таким именем существует и готов к работе!" << endl;
			flag_m_2 = 1;
		}
		else
		{
			cout << "Введенное имя не совпадает ни с одним названием из существующих файлов в папке с программой. Введите корректное имя!" << endl;
		}

		if (flag_m_2 == 1)//название файла должно быть корректным
		{
			flag = true;
		}
		cout << endl << endl;
	}

	return m_2;
}


string out_sentence(ofstream& out_prog_text)
{
	bool flag = false;
	string name_new_file;
	cout << "Введите имя новый файл" << endl;
	cout << "К введенному имени, автоматически добавляется расширение '.txt'. Введите только основное имя файла!" << endl;
	cout << "Для выхода в меню введите слово: Выход" << endl;
	while (!flag)
	{
		int flag_m_2 = 0;
		getline(cin, name_new_file);
		if (name_new_file == "Выход")//для выхода из программы
		{
			return name_new_file;
		}
		name_new_file += ".txt";
		cout << name_new_file << endl;
		out_prog_text.open(name_new_file);
		if (out_prog_text.is_open())
		{
			cout << "Название файла создано: " << name_new_file << endl;
		}
		bool flag_1 = false;
		char choose;
		cout << "Вы соглысны с данным название файла?" << "  1 -  Да" << "  2 -  Нет" << endl;//на случай если человек захочет новый файл ввести
		choose = _getch();
		while (!flag_1)
		{
			switch (choose)
			{
			case '1':
			{
				flag_1 = true;
				flag = true;
				break;
			}
			case '2':
			{
				flag_1 = true;
				cout << "Введите название файла завново!" << endl; // в случае если пользователь решил что ошибься
				break;
			}
			default:
				cout << "Введено не корректное число! Попробуйте еще раз: ";
				choose = _getch();
				cout << endl;
				break;
			}
		}
	}
}



