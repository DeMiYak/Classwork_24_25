#include "Parser.h"

/// Комментарии Никиты Константиновича:
/// 
/// Три великих поправки:
/// 1. Проверка на то, что в строке количество значений отличается от количества столбцов.
/// 2. В тексте исключения нужно запомнить, в какой строке / столбце была ошибка.
/// 3. Хотя бы одна ошибка должна вести к отмене всего парсинга.
/// 
/// Давайте вынесем try... catch блоки из Parser.cpp и попробуем поймать std::exception в районе 44 строки в IO_hometask.cpp
/// Не нужно на каждый throw делать try... catch блок.


dataframe Parser::Parse()
{
    ifstream in(filename);
    if (!in.is_open()) {
        throw runtime_error("File not found: " + filename);
    }
    vector<string> headers;
    vector<vector<double>> data;
    errorIndex = { 1, 1 };
    headerSize = 0;
    HeaderParsing(in, headers);
    DataParsing(in, data);
    return make_pair(headers, data);
}

void Parser::HeaderParsing(ifstream& in, vector<string>& headers)
{
    string vs;
    getline(in, vs);
    istringstream iss(vs);
    stringstream errorStream;
    while (getline(iss, vs, delim)) {
        if (vs == "") {
            headers.clear();
            errorStream << "Column name is empty in file: " << filename << "\nError occurred at row "
                << errorIndex.first << " column " << errorIndex.second;
            throw invalid_argument(errorStream.str());
        }  
        errorIndex.second++;
        headers.push_back(vs);
    }
    errorIndex.first++;
    errorIndex.second = 1;
    headerSize = headers.size();
}

void Parser::DataParsing(ifstream& in, vector<vector<double>>& data)
{
    string vs;
    stringstream errorStream;
    while (getline(in, vs)) {
        int count = 0;
        vector<double> values;
        istringstream iss(vs);
        double val;
        while (iss >> val) {
            count++;
            values.push_back(val);
            if (iss.peek() == delim) {
                iss.ignore();
            }
            if (count > headerSize) {
                break;
            }
            errorIndex.second++;
        }
        if (!iss.eof() && iss.fail()) {
            data.clear();
            errorStream << "Failed to read the data from file: " << filename << "\nError occurred at row "
                << errorIndex.first << " column " << errorIndex.second;
            throw invalid_argument(errorStream.str());
        }
        if (count != headerSize) {
            data.clear();
            errorStream << "Error: incoherent header and data column sizes. Header "
                << headerSize << " columns and Data " << count << " columns"
                << "\nError occurred at row "
                << errorIndex.first << " column " << errorIndex.second;
            throw length_error(errorStream.str());
        }
        errorIndex.first++;
        errorIndex.second = 1;
        data.push_back(values);
    }
}
