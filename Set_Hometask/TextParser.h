#pragma once
#include<iostream>
#include<iterator>
#include<string>
#include<vector>
#include<fstream>
#include<unordered_set>
#include<algorithm>

using namespace std;

/// <summary>
/// Класс для парсинга текста.
/// </summary>
class TextParser
{
public:
	TextParser(string_view delim) : delim(delim) {};
	vector<string> Parse(const string& filename, bool addDelimiters = false);
	void SetDelim(const string_view& _delim) { delim = _delim; }
	string_view GetDelim() const { return delim; }
private:
	bool IsInDelimiter(char c);
	string_view delim;
};



