#pragma once
#include"TextParser.h"
#include<cctype>

using namespace std;

typedef unordered_set<string> dictionary;

class TextCorrector
{
public:
	TextCorrector(dictionary dict) : dict(dict) {};
	void CorrectText(vector<string>& parsedText);
	void SetDictionary(dictionary _dict) { dict = _dict; }
	dictionary GetDictionary() const { return dict; }
	void PrintInfo();
private:
	void ResetInfo();
	void Correction(string& correctable);
	void LevensteinReplace(string& correctable);
	const string alphabet = "abcdefghijklmnopqrstuvwxyz";
	dictionary dict;
	struct {
		size_t deletion = 0;
		size_t insertion = 0;
		size_t replace = 0;
		size_t emplace = 0;
		size_t ignore = 0;
		size_t contained = 0;
	}info;
};

