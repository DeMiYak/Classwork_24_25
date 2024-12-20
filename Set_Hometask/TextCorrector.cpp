#include "TextCorrector.h"

enum LEVENSTEIN{DEL = 0, INS = 1, REP = 2};

void TextCorrector::CorrectText(vector<string>& parsedText)
{
    ResetInfo();
    ofstream os("data//output.txt");
    // Convert to lowercase
    transform(parsedText.begin(), parsedText.end(), parsedText.begin(),
        [](std::string& str) {
        transform(str.begin(), str.end(), str.begin(), [](char c) {return tolower(c);});
        return str;
    });

    for (size_t i = 0; i < parsedText.size(); i++) {
        string& word(parsedText[i]);
        // Обработать случай с спецсимволами. 
        if (!IsInDelimiter(word) && !dict.contains(word)) {
            Correction(word);
        }
        else {
            info.contained++;
        }
        os << word;
    }
    os.close();
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
    vector<pair<string, LEVENSTEIN>> options;
    // Deletions
    for (size_t i = 0; i < correctable.size(); i++) {
        temp_word = word_base;
        temp_word.erase(i, 1);
        if (dict.find(temp_word) != dict.end()) {
            options.push_back(make_pair(temp_word, DEL));
        }
    }
    // Insertions
    for (std::size_t i = 0; i <= correctable.size(); ++i) {
        for (char c : alphabet) {
            temp_word = word_base;
            temp_word.insert(i, 1, c);
            if (dict.find(temp_word) != dict.end()) {
                options.push_back(make_pair(temp_word, INS));
            }
        }
    }
    // Replacements
    for (std::size_t i = 0; i < correctable.size(); i++) {
        for (char c : alphabet) {
            temp_word = word_base;
            temp_word[i] = c;
            if (dict.find(temp_word) != dict.end()) {
                options.push_back(make_pair(temp_word, REP));
            }
        }
    }

    size_t optionSize(options.size());
    int num = -1;
    if (!options.empty()) {
        do {
            cout << endl << "Selection of words of Levenstein distance 1: ";
            for (size_t i = 0; i < optionSize; ++i) {
                cout << "(" << options[i].first << ", " << i << ")\t";
            }
            cout << endl << "To choose, enter the number next to word in ()." << endl;
            cin >> num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (num < 0 || optionSize <= num);

        cout << endl << "Selection of words of Levenstein distance 1: ";
        for (size_t i = 0; i < options.size(); ++i) {
            cout << "(" << options[i].first << ", " << i << ")\t";
        }
    }

    if (!options.empty()) {
        stringstream optionstream;
        string new_word = options[num].first;
        switch (options[num].second)
        {
            case DEL:
                optionstream << endl << "Levenstein Deletion\nOld word : "
                    << correctable << "\tNew word: " << new_word << endl;
                ++info.deletion;
                break;
            case INS:
                optionstream << endl << "Levenstein Insertion\nOld word : "
                    << correctable << "\tNew word: " << new_word << endl;
                ++info.insertion;
                break;
            case REP:
                optionstream << endl << "Levenstein Replace\nOld word : "
                    << correctable << "\tNew word: " << new_word << endl;
                ++info.replace;
                break;
            default:
                break;
        }
        correctable = new_word;
        cout << optionstream.str();
    }
    else {
        cout << endl << "No word of Levenstein distance 1 was found. Adding it to dictionary." << endl;
        dict.emplace(correctable);
        info.emplace++;
    }
}

bool TextCorrector::IsInDelimiter(const string& word) const
{
    if (word.empty()) {
        return true;
    }
    for (char c : word) {
        if (delim.find(c) != string_view::npos) {
            return true;
        }
    }
    return false;
}
