#pragma once
#include<fstream>
#include<iostream>
#include<iterator>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>

using namespace std;

typedef pair<vector<string>, vector<vector<double>>> dataframe;

class Parser
{
public:
    Parser(const string& filename, char delim = ';') : filename(filename), delim(delim) {};
    dataframe Parse();
    void SetFilename(const string& filename_) { filename = filename_; }
    void SetDelimiter(const char& delim_) { delim = delim_; }
    const string& GetFilename() const { return filename; }
    const char& GetDelimiter() const { return delim; }
private:
    void HeaderParsing(ifstream& in, vector<string>& headers);
    void DataParsing(ifstream& in, vector<vector<double>>& data);
    string filename;
    char delim;
};


