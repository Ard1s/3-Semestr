#pragma once
#include<string>
using namespace std;


class tries
{
    bool value;    
    tries* pointers[26];   

public:
    tries()
    {
        
        value = 0;
        for (int i = 0; i < 26; i++)
            pointers[i] = NULL;
    }

   
    void add(string s);

   
    bool searchtries(string word, int i);

    
    void deletetries();

};


class dictionary
{
public:
    const char* dict;
    tries* root;    
    dictionary(const char* file)
    {
        dict = file;
        root = NULL;
    }

    
    bool load();

    
    void unload();

    
    bool check(string word);
};
