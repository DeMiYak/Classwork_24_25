#include "Parser.h"

/// ����������� ������ ���������������:
/// 
/// ��� ������� ��������:
/// 1. �������� �� ��, ��� � ������ ���������� �������� ���������� �� ���������� ��������.
/// 2. � ������ ���������� ����� ���������, � ����� ������ / ������� ���� ������.
/// 3. ���� �� ���� ������ ������ ����� � ������ ����� ��������.
/// 
/// ������� ������� try... catch ����� �� Parser.cpp � ��������� ������� std::exception � ������ 44 ������ � IO_hometask.cpp
/// �� ����� �� ������ throw ������ try... catch ����.


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
