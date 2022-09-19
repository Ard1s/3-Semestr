#include <iostream>
#include "dictionary.h"
#include <fstream>
#include <cstdlib>
#include <conio.h>
#define DICTIONARY "dictionary.txt"    

using namespace std;

void checkfile()
{
    system("cls");

   

    if (!d.load())
    {
        cout << "could not load dictionary";
        return;
    }


    char text[80];  

    cout << "Enter the name of file ";
    cin >> text;

    fstream f;
    f.open(text, ios::in);

    if (!f.is_open())
    {
        cout << "could not open file";
        d.unload();
        return;
    }

    cout << "MISSPELLED WORDS: ";

    string word;
    f >> word;

    while (!f.eof())
    {
       
        bool misspelled = !d.check(word);
        if (misspelled)
            cout << word << endl;
        f >> word;
    }

    f.close();
    _getch();
}


void writefile()
{
    system("cls");
    char filename[80]; 


    fstream f;
    char flag = 'y';

  
    do
    {
        flag = 'y';
        cout << "save as filename(spaces not allowed):\t";
        cin >> filename;

        f.open(filename, ios::in);
        if (f.is_open())
        {
            cout << "File already exists\nDo you want to replace it?(y/n)\t";
            cin >> flag;
            f.close();
        }
    } while (flag == 'n');

    f.open(filename, ios::out);
    if (!f.is_open())
    {
        cout << "could not open file";
        return;
    }
    cout << "Enter text, type EXITTYPING and press enter to end file\n";

   
    string word;
    cin >> word;
    while (word.compare("EXITTYPING"))
    {
        f << word << " ";
        cin >> word;
    }
    f.close();
    cout << "File saved!";
    _getch();
}


void addword()
{
    system("cls");
    cout << "Enter the word you wish to add\n";
    string word;
    cin >> word;

    ofstream f;
    f.open(DICTIONARY, ios::app);
    if (!f.is_open())
        cout << "could not open" << DICTIONARY;
    f << word << "\n";

    cout << "Added!";
    _getch();
}

int main()
{
   
    while (1)
    {
        system("cls");
        cout << "Enter your choice\n";
        cout << "1. Check a file\n2. Write a file\n3. Add word to dictionary\n4. Exit\n";

        char  choice;

        choice = _getch();
        switch (choice)
        {
        case '1':
            checkfile();
            break;
        case '2':
            writefile();
            break;
        case '3':
            addword();
            break;
        case '4':
            return 0;
        }
    }

    return 0;
}
