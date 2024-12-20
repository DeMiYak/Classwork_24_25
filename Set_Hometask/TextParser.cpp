#include "TextParser.h"

vector<string> TextParser::Parse(const string& filename, bool addDelimiters)
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
				if (addDelimiters) {
					/*parsedData.push_back(string(left, left+1));
					left = find_if(++right, end, [this](char c) {return c != ' ';});*/	
					parsedData.push_back(string(right, left));
				}
			}
		}
		if (addDelimiters) {
			parsedData.push_back("\n");
		}
		
	}
	return parsedData;
}

//pair<string, bool> TextParser::SingularParse()
//{
//	if (!parseStream.is_open()) {
//		throw runtime_error("Don't have the stream in TextParser class.");
//	}
//	string va;
//	parseStream >> va;
//}
//
//pair<string, bool> TextParser::SingularParse(const string& filename)
//{
//	parseStream = ifstream(filename);
//	if (!parseStream.is_open()) {
//		throw runtime_error("Can't find the file: " + filename);
//	}
//	return SingularParse();
//}

bool TextParser::IsInDelimiter(char c)
{
	return delim.find(c) != string_view::npos;
}
