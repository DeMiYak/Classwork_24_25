 //Задача:
 //Есть два текстовых файла, в одном слова (1),
 //в другом текст (возможно, с ошибками) (2).
 //
 //Необходимо построить словарь для (2) на основе (1) и добавить
 //реализацию обработки близких по Левенштейну (расстояние = 1)
 //
 //Реализация программы по схеме:
 //Если встретилось совпадающее слово - добавляем его к соответствующему слову;
 //Если не встретилось - есть три варианта (выбирает пользователь):
 //1. Проигнорировать
 //2. Включить в словарь как отдельное слово
 //3. Найти замену по Левенштейну (что делать если замены не окажется?)


#include <iostream>
#include"TextParser.h"
#include"TextCorrector.h"

using namespace std;

int main() {
	string_view delim(",.;:<>'`\"()!?&#$%*-+[]{}/ 123456789");
	TextParser tp(delim);
	const string dictName("data//words_alpha.txt");
	const string textName("data//example.txt");
	vector<string> dictVector(tp.Parse(dictName));
	vector<string> text;
	try {
		text = tp.Parse(textName);
	}
	catch (const runtime_error& e) {
		cout << "Runtime error: " << e.what() << endl;
	}
	cout << "Dictionary size: " << dictVector.size() << endl;
	cout << "Text size: " << text.size() << endl;
	
	dictionary dictSet(dictVector.begin(), dictVector.end());
	TextCorrector tc(dictSet);

	try {
		tc.CorrectText(text);
	}
	catch (const exception& e) {
		cout << "Exception. Unable to identify error: " << e.what() << endl;
	}
	cout << endl << "Changed dictionary size: " << tc.GetDictionary().size() << endl;
	tc.PrintInfo();
	for (const string& word : text) {
		cout << word << '\t';
	}
	cout << endl;
	return 0;
}