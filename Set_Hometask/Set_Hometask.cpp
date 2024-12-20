#include <iostream>
#include"TextParser.h"
#include"TextCorrector.h"

using namespace std;

int main() {
	string_view delim(",.;:<>''``\"()!?&#$%*-+[]{}/\n 123456789");
	TextParser tp(delim);
	const string dictName("data//words_alpha.txt");
	const string textName("data//example.txt");
	vector<string> dictVector(tp.Parse(dictName));
	vector<string> text;
	try {
		text = tp.Parse(textName, true);
	}
	catch (const runtime_error& e) {
		cout << "Runtime error: " << e.what() << endl;
	}
	cout << "Dictionary size: " << dictVector.size() << endl;
	cout << "Text size: " << text.size() << endl;
	
	Dictionary dictSet(dictVector.begin(), dictVector.end());
	TextCorrector tc(dictSet, delim);

	try {
		tc.CorrectText(text);
	}
	catch (const exception& e) {
		cout << "Exception. Unable to identify error: " << e.what() << endl;
	}
	cout << endl << "Changed dictionary size: " << tc.GetDictionary().size() << endl;
	tc.PrintInfo();
	/*for (const string& word : text) {
		cout << word << '\t';
	}*/
	cout << endl;
	return 0;
}