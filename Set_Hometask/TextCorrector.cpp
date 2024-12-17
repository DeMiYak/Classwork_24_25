#include "TextCorrector.h"

void TextCorrector::CorrectText(vector<string>& parsedText)
{
    ResetInfo();
    // Convert to lowercase
    transform(parsedText.begin(), parsedText.end(), parsedText.begin(),
        [](std::string& str) {
        transform(str.begin(), str.end(), str.begin(), [](char c) {return tolower(c);});
        return str;
    });

    for (size_t i = 0; i < parsedText.size(); i++) {
        string& word(parsedText[i]);
        if (!dict.contains(word)) {
            Correction(word);
        }
        else {
            info.contained++;
        }
    }
}

void TextCorrector::PrintInfo()
{
    cout << endl << "Characters Deleted:\t" << info.deletion << "\n";
    cout << "Characters Inserted:\t" << info.insertion << "\n";
    cout << "Characters Replaced:\t" << info.replace << "\n";
    cout << "New Words Emplaced:\t" << info.emplace << "\n";
    cout << "New Words Ignored:\t" << info.ignore << "\n";
    cout << "Words Successfully Contained:\t" << info.contained << endl;
}

void TextCorrector::ResetInfo()
{
    info.deletion = 0;
    info.insertion = 0;
    info.ignore = 0;
    info.emplace = 0;
    info.replace = 0;
    info.contained = 0;
}

void TextCorrector::Correction(string& correctable)
{
    int option;
    do {
        cout << endl << "Word " << correctable << " not found in dictionary.\nPlease, choose the option:\n"
            << "1. Ignore the word\n"
            << "2. Add the word to dictionary\n"
            << "3. Replace with similar word from dictionary" << endl;
        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (option)
        {
        case 1:
            info.ignore++;
            return;
        case 2:
            dict.emplace(correctable);
            info.emplace++;
            return;
        case 3:
            LevensteinReplace(correctable);
            return;
        default:
            break;
        }

    } while (true);
}

void TextCorrector::LevensteinReplace(string& correctable)
{
    const string word_base(correctable);
    string temp_word;
    // Deletions
    for (size_t i = 0; i < correctable.size(); i++) {
        temp_word = word_base;
        temp_word.erase(i, 1);
        if (dict.find(temp_word) != dict.end()) {
            cout << endl << "Deletion of letter \"" + word_base.substr(i, 1) +
                "\" at position " + to_string(i) + "\nOld word : "
                + correctable + "\tNew word: " + temp_word << endl;
            correctable = temp_word;
            info.deletion++;
            return;
        }
    }
    // Insertions
    for (std::size_t i = 0; i <= correctable.size(); ++i) {
        for (char c : alphabet) {
            temp_word = word_base;
            temp_word.insert(i, 1, c);
            if (dict.find(temp_word) != dict.end()) {
                cout << endl << "Insertion of letter \"" + string(1, c)
                    + "\" at position " + to_string(i) + "\nOld word: "
                    + correctable + "\tNew word: " + temp_word << endl;
                correctable = temp_word;
                info.insertion++;
                return;
            }
        }
    }
    // Replacements
    for (std::size_t i = 0; i < correctable.size(); i++) {
        for (char c : alphabet) {
            temp_word = word_base;
            temp_word[i] = c;
            if (dict.find(temp_word) != dict.end()) {
                cout << endl << "Replacement of letter \"" + word_base.substr(i, 1) + "\" with \""
                    + string(1, c) + "\" at position " + to_string(i) + "\nOld word: "
                    + correctable + "\tNew word: " + temp_word << endl;
                correctable = temp_word;
                info.replace++;
                return;
            }
        }
    }

    cout << endl << "No word of Levenstein distance 1 was found. Adding it to dictionary." << endl;
    dict.emplace(correctable);
    info.emplace++;
}
