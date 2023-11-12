#include <iostream>
#include <string>
#include <fstream>
//#include <cstring>
//#include <string.h>
//#include <sstream>
#include <conio.h>
#include <iomanip>
//#include <chrono>
#include <Windows.h>
#include <vector>

using namespace std;

vector <string> isc_podl;//найденные в текущем предложении подлежащие
int count_output = 0;//счетчик всех предложений

string open_file(ifstream& in_p_t);//функция для открытия файла и проверки корректности введенного названия
string out_sentence(ofstream& out_prog_text);//функция для открытия файла на вывод и проверка корректности введеного названия
bool mestoimenia(vector <string>& piece_of_sentence);
bool imena(string first_word);
bool find_skazyemoe(vector <string>& piece_of_sentence);
bool side_of_podl(vector <string>& piece_of_sentence,int poz_skaz);//poz_skaz позиция рассматриваемого сказцемого выраженного глаголом 
void analysis(vector <string>& piece_of_sentence);
bool Capitalized_word(vector <string>& piece_of_sentence);

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
	int counter = 0;
	while (!in_prog_text.eof())//пока не конец файла 
	{
		++counter;
		bool flag = false;
		int i = 1;
		while (!flag) // пока элемент слова не разделитель 
		{
			in_prog_text >> buff_word;
			if ((buff_word[buff_word.size() - 1] == '.') or (buff_word[buff_word.size() - 1] == '!') or (buff_word[buff_word.size() - 1] == '?'))
			{
				flag = true;
				sentence.push_back(buff_word);
			}
			else
			{
				sentence.push_back(buff_word);
				buff_word = "";
			}
		}
		
		int counter = 0;
		string new_word;
		vector <string> piece_of_sentence;
		bool No_commas = false;//флаг если нет запятой
		while (counter < sentence.size())//разбиение предложения на подпредложения
		{
			new_word = sentence[counter];//для работы со string
			piece_of_sentence.push_back(new_word);
			if (new_word[new_word.length() - 1] == ',' or new_word[new_word.length() - 1] == '.' or new_word[new_word.size() - 1] == '!' or new_word[new_word.size() - 1] == '?')
			{
				No_commas = true;
				analysis(piece_of_sentence);//вызываем функцию анализатора
				piece_of_sentence.clear();
			}
			++counter;
		}
		//if (No_commas == false)
		//{
		//	analysis(piece_of_sentence);//вызываем функцию анализатора
		//}
		
		
		cout << "Найденые подлежащие: ";
		out_prog_text << "Найденые подлежащие: ";
		for (int i = 0; i < isc_podl.size(); ++i)
		{
			out_prog_text << isc_podl[i];
			cout << isc_podl[i];
			out_prog_text << " ";
			cout << " ";
		}
		if (isc_podl.size() == 0)
		{
			cout << "Подлежащее не найдено";
			out_prog_text << "Подлежащее не найдено";
		}
		
		out_prog_text << " || Искомое предложение: ";
		out_prog_text << counter << ") ";
		cout << " || Искомое предложение: ";
		cout << counter << ") ";
		for (int i = 0; i < sentence.size();++i)
		{
			out_prog_text << sentence[i];
			cout << sentence[i];
			out_prog_text << " ";
			cout << " ";
		}
		out_prog_text << endl;
		cout << endl;
		sentence.clear();
		isc_podl.clear();
	
	}
	in_prog_text.close();
	out_prog_text.close();
	return 0; 
}


void analysis(vector <string>& piece_of_sentence)
{
	bool flag_spec = false;
	char break_point = 0;//номер аналзируемого признака
	while (!flag_spec)
	{

		++break_point;
		switch (break_point)
		{
		case 1: flag_spec = mestoimenia(piece_of_sentence);
			break;
		case 2: flag_spec = Capitalized_word(piece_of_sentence);//imena(piece_of_sentence)
			break;
		case 3: flag_spec = find_skazyemoe(piece_of_sentence);
			break;
		case 4: flag_spec = true;//что бы выйти
			break;
		}
	}
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


bool mestoimenia(vector <string>& piece_of_sentence)
{
	
	ifstream mestoim;
	mestoim.open("местоимения.txt");
	string mesto;//здесь будет хранится местоимение взятое из файла
	if (!mestoim.is_open())
	{
		cout << "Файл местоимений не открыт" << endl;
	}

	while (!mestoim.eof())
	{
		mestoim >> mesto;
		for (int i = 0; i < piece_of_sentence.size(); ++i)
		{
			if (i == piece_of_sentence.size() - 1)
			{
				string last_word = piece_of_sentence[i];
				last_word.erase(last_word.end() - 1);
				if (last_word == mesto)//                                        ДУМАЮ МОЖНО ЛУЧШЕ НАПИСАТЬ
				{
					isc_podl.push_back(mesto);
					return  true;
				}
			}
			if (piece_of_sentence[i] == mesto)
			{
				isc_podl.push_back(mesto);
				return  true;
			}

		}
	}
	mestoim.close();
	return false;
}

bool imena(string first_word)
{
	ifstream imena;
	imena.open("имена.txt");
	string im;
	if (!imena.is_open())
	{
		cout << "Файл имён не открыт" << endl;
	}
	while (!imena.eof())                                                                
	{
		if (first_word[first_word.length() - 1] == '.' or first_word[first_word.length() - 1] == '!' or first_word[first_word.length() - 1] == '?')
		{
			first_word.erase(first_word.end() - 1);
		}
		imena >> im;
		if (first_word == im)
		{
			return true;
		}
	}
	imena.close();
	return false;
}


bool Capitalized_word(vector <string>& piece_of_sentence)
{
	int i = 0;//счетчик элементов вектора
	bool capital_first = false;
	while (i < piece_of_sentence.size())
	{
		if (i == 0)
		{
			string first_word = piece_of_sentence[i];
			capital_first = imena(first_word);
			if (capital_first == true)
			{
				isc_podl.push_back(first_word);
				return true;
			}
		}
		else
		{
			string anyword = piece_of_sentence[i];
			if (anyword[0] > 'А' and anyword[0] < 'Я')
			{
				isc_podl.push_back(anyword);
				return true;
			}
		}
		++i;
		
	}

	return capital_first;
}

bool find_skazyemoe(vector <string>& piece_of_sentence)
{
	ifstream skaz;
	skaz.open("окончание глаголов.txt");
	string ending;//здесь будет хранится окончание взятое из файла
	if (!skaz.is_open())
	{
		cout << "Файл местоимений не открыт" << endl;
	}
	int i = 0;
	bool ska = false;
	char brakepoint = 0;
	int j = 0;
	string current_word;
	string ending_word_from;
	while (!skaz.eof() or ska == true)
	{
		int j = 0;
		skaz >> ending;
		int size_endig = ending.size();
		bool word_less_ending = false;// слово меньше окончания 
		while (j < piece_of_sentence.size())
		{
			current_word = piece_of_sentence[j];
			if (j == piece_of_sentence.size() - 1)
			{
				current_word.erase(current_word.end() - 1);
			}
			if (current_word.size() <= ending.size())
			{
				++j;
			}
			else
			{
				ending_word_from = current_word.substr(current_word.size() - size_endig, size_endig);//кладем в переменную строку с окончанием текущео слова
				if (ending == ending_word_from)
				{
					ska = side_of_podl(piece_of_sentence, j);//возвращаем true если нашли подлежащее
					if (ska == true)
					{
						return true;
					}
					//вызываем функцию в которой будем искать с какой стороны находится подлежащее слева или справа сначала смотрим нет ли точки или не конец предлежния слева или справа, а мб и вообще с двух сторон запятые. вызывая, проверку наличия предлога и в случае если его нет проверяем существительное слева и справа.					}
				}
				++j;
			}
		}
	}
	skaz.close();
	return ska;
}

bool side_of_podl(vector <string>& piece_of_sentence, int poz_skaz)
{
	if (piece_of_sentence.size() <= 1)//если в векторе одно слово
	{
		return false;
	}
	if (poz_skaz == 0)
	{
		isc_podl.push_back(piece_of_sentence[poz_skaz + 1]);//если это начало предложения, то тогда второе слово подлежащее
		return true;
	}
	if (poz_skaz == piece_of_sentence.size() - 1)
	{
		isc_podl.push_back(piece_of_sentence[poz_skaz - 1]);//если это начало предложения, то тогда второе слово подлежащее
		return true;
	}
	else
	{
		ifstream predlog;
		predlog.open("предлоги.txt");
		string predlog_f_f;//здесь будет хранится  предлог из файла
		if (!predlog.is_open()) {cout << "Файл местоимений не открыт" << endl;}
		while (!predlog.eof())
		{
			int j = 0;
			predlog >> predlog_f_f;
			while (j < piece_of_sentence.size())
			{
				if (predlog_f_f == piece_of_sentence[j])//добавить типо расстояние до нашего сказуемного равное или меньшее 0
				{
					if (j < poz_skaz)
					{
						isc_podl.push_back(piece_of_sentence[poz_skaz + 1]);

						return true;
					}
					if (j > poz_skaz)
					{
						isc_podl.push_back(piece_of_sentence[poz_skaz - 1]);
						return true;
					}
				}
				++j;
			}
		}
		
	}
	                                                                 //проверить существительное в случае чего 
	return false;
}



//switch (size_endig)
		//{
		//case 2:
		//	while (j < piece_of_sentence.size())
		//	{
		//		current_word = piece_of_sentence[j];
		//		if (current_word.size() <= ending.size())
		//		{
		//			++j;
		//		}
		//		else
		//		{
		//			ending_word_from = current_word.substr(current_word.size() - 2, 2);//кладем в переменную строку с окончанием текущео слова
		//			if (ending == ending_word_from)
		//			{
		//				ska = side_of_podl(piece_of_sentence, j);//возвращаем true если нашли подлежащее
		//				//вызываем функцию в которой будем искать с какой стороны находится подлежащее слева или справа сначала смотрим нет ли точки или не конец предлежния слева или справа, а мб и вообще с двух сторон запятые. вызывая, проверку наличия предлога и в случае если его нет проверяем существительное слева и справа.					}
		//			}
		//			++j;
		//		}
		//		 	
		//	}
		//	break;
		//case 3:
		//	while (j < piece_of_sentence.size())
		//	{
		//		current_word = piece_of_sentence[j];
		//		if (current_word.size() <= ending.size()){++j;}
		//		else
		//		{
		//			ending_word_from = current_word.substr(current_word.size() - 3, 2);//кладем в переменную строку с окончанием текущео слова
		//			if (ending == ending_word_from)
		//			{
		//				ska = side_of_podl(piece_of_sentence, j);//возвращаем true если нашли подлежащее
		//				//вызываем функцию в которой будем искать с какой стороны находится подлежащее слева или справа сначала смотрим нет ли точки или не конец предлежния слева или справа, а мб и вообще с двух сторон запятые. вызывая, проверку наличия предлога и в случае если его нет проверяем существительное слева и справа.					}
		//			}
		//			++j;
		//		}

		//	}
		//	break;
		//case 4:
		//	while (j < piece_of_sentence.size())
		//	{
		//		current_word = piece_of_sentence[j];
		//		if (current_word.size() <= ending.size())
		//		{
		//			++j;
		//		}
		//		else
		//		{
		//			ending_word_from = current_word.substr(current_word.size() - 4, 2);//кладем в переменную строку с окончанием текущео слова
		//			if (ending == ending_word_from)
		//			{
		//				ska = side_of_podl(piece_of_sentence, j);//возвращаем true если нашли подлежащее
		//				//вызываем функцию в которой будем искать с какой стороны находится подлежащее слева или справа сначала смотрим нет ли точки или не конец предлежния слева или справа, а мб и вообще с двух сторон запятые. вызывая, проверку наличия предлога и в случае если его нет проверяем существительное слева и справа.					}
		//			}
		//			++j;
		//		}

		//	}
		//	break;
		//}