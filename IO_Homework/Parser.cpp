#include "Parser.h"

dataframe Parser::Parse()
{
    ifstream in(filename);
    try {
        if (!in.is_open()) {
            throw runtime_error("File not found: " + filename);
        }
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
        return dataframe();
    }
    vector<string> headers;
    vector<vector<double>> data;

    HeaderParsing(in, headers);
    DataParsing(in, data);

    cout << endl;

    return make_pair(headers, data);
}

void Parser::HeaderParsing(ifstream& in, vector<string>& headers)
{
    string vs;
    getline(in, vs);
    istringstream iss(vs);
    while (getline(iss, vs, delim)) {
        try {
            if (vs == "") {
                //vs = "col" + to_string(count);
                throw invalid_argument("Column name unidentified in file: " + filename);
            }
        }
        catch (const invalid_argument& e) {
            cout << '\n' << e.what() << endl;
            return;
        }
        headers.push_back(vs);
        cout << vs << ' ';
    }
    cout << endl;
}

void Parser::DataParsing(ifstream& in, vector<vector<double>>& data)
{
    string vs;
    int count = 0;
    while (getline(in, vs)) {
        vector<double> values;
        istringstream iss(vs);
        double val;
        try {
            while (iss >> val) {
                cout << val << ' ';
                values.push_back(val);
                if (iss.peek() == delim) {
                    iss.ignore();
                }
            }
            if (!iss.eof() && iss.fail()) {
                throw invalid_argument("Failed to read the data from file. Type is not double: " + filename);
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << '\n';
            return;
        }
        cout << endl;
        data.push_back(values);
    }
}
