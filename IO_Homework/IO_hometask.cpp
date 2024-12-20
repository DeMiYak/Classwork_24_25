/// Доделать I/O и Словарь

#include"Parser.h"
#include"stdexcept"
using namespace std;

void PrintDataframe(const dataframe& df) {
    const vector<string>& headers(df.first);
    const vector<vector<double>>& data(df.second);
    for (size_t i = 0; i < headers.size(); i++) {
        cout << headers[i] << setw(10) << "";
    }
    cout << endl;
    for (size_t j = 0; j < data.size(); j++) {
        for (size_t k = 0; k < data[0].size(); k++) {
            cout << data[j][k] << setw(10) << "";
        }
        cout << endl;
    }
}

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
        cout << "4. " << beg + "4" + fin << endl;
        cout << "5. " << "Exit" << endl;
        cin >> select;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        if (select == 5) {
            return 0;
        }
        stringstream filestream;
        filestream >> beg >> select >> fin;
        filename = filestream.str();
        cout << endl;
        Parser parse(filename);
        try {
            dataframe df = parse.Parse();
            PrintDataframe(df);
        }
        catch (const runtime_error& e) {
            cout << '\n' << "Runtime Error: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << '\n' << "Invalid Argument: " << e.what() << endl;
        }
        catch (const length_error& e) {
            cout << '\n' << "Length Error: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << '\n' << "Unable to identify error: " << e.what() << endl;
        }
    } while (true);
    return 0;
}