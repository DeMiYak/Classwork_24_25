/// Задача:
/// Дан tab (или comma) separated file.
/// В первой строке - раздёлённые табуляцией названия строк.
/// Дальше данные - вещественные числа, разделённые табуляциями и
/// переносами строк.
/// 
/// Требуется разобрать исходный файл, вывести содержимое разбора
/// на экран. В случае ошибки при парсинге - кинуть исключение и
/// показать, в чём проблема.
/// 
/// Подсказка: хранить название можно с помощью vector<string>,
/// данные - vector<vector<double>>
/// 
/// Дедлайн - конец семестра (через месяц)
/// 


#include"Parser.h"
#include"stdexcept"
using namespace std;

int main()
{
    string filename;
    string beg = "data//data";
    int select;
    string fin = ".csv";
    do {
        cout << "Select one of the following files: " << endl;
        cout << "1. " << beg + "1" + fin << endl;
        cout << "2. " << beg + "2" + fin << endl;
        cout << "3. " << beg + "3" + fin << endl;
        cout << "4. " << "Exit" << endl;
        cin >> select;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        if (select == 4) {
            return 0;
        }
        filename = beg + to_string(select) + fin;
        cout << endl;
        Parser parse(filename);
        dataframe df = parse.Parse();
    } while (true);
    return 0;
}