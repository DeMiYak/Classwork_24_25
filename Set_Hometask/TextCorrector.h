#pragma once
#include"TextParser.h"
#include<cctype>
#include<sstream>

using namespace std;

typedef unordered_set<string> Dictionary;

class TextCorrector 
{
public:
	TextCorrector(Dictionary dict, string_view delim) : dict(dict), delim(delim) {};
	void CorrectText(vector<string>& parsedText);
	void SetDictionary(Dictionary _dict) { dict = _dict; }
	Dictionary GetDictionary() const { return dict; }
	void SetDelim(const string_view& _delim) { delim = _delim; }
	string_view GetDelim() const { return delim; }
	void PrintInfo();
private:
	void ResetInfo();
	void Correction(string& correctable);
	void LevensteinReplace(string& correctable);
	bool IsInDelimiter(const string& word) const;
	const string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string_view delim;
	Dictionary dict;
	struct {
		size_t deletion = 0;
		size_t insertion = 0;
		size_t replace = 0;
		size_t emplace = 0;
		size_t ignore = 0;
		size_t contained = 0;
	}info;
};

