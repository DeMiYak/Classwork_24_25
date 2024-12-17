#include "TextParser.h"

vector<string> TextParser::Parse(const string& filename)
{
	vector<string> parsedData;
	ifstream in(filename);
	if (!in.is_open()) {
		throw runtime_error("Can't find the file: " + filename);
	}
	string va;
	while (getline(in, va)) {
		string_view sv(va);
		string_view::iterator left(sv.begin());
		string_view::iterator end(sv.end());
		while (left != end) {
			string_view::iterator right(find_if(left, end, [this](char c) {return IsInDelimiter(c);}));
			if (left != right) {
				parsedData.push_back(string(left, right));
			}
			if (right == end) {
				left = right;
			}
			else {
				left = find_if(right, end, [this](char c) {return !IsInDelimiter(c);});
			}
		}
	}
	return parsedData;
}

bool TextParser::IsInDelimiter(char c)
{
	return delim.find(c) != string_view::npos;
}
