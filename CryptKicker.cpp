#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

string dict_words[1000];
string words[1000];

set<string> dict_words_set;

int word_lengths[1000];
int dict_word_lengths[1000];
int dict_word_count, word_count;
int ascii_base = 97;

bool is_decryptable;
char temp_map[26];

char word_to_dict[26], dict_to_word[26];

void create_dict(char dict[26]){
    for(int i = 0; i < 26; i++)
        dict[i] = 0;
}

void copy_dict(char base[26], char copy[26]){
    for(int i = 0; i < 26; i++)
        copy[i] = base[i];

}

void print_response(bool is_decrypted){
    for(int i = 0; i < word_count; i++) {
        if(i)  //word space
            cout<<' ';
        for(int j = 0; j < word_lengths[i]; j++){
            if(is_decrypted)
                cout<<word_to_dict[words[i][j]-ascii_base];
            else
                cout<<'*';
        }
    }
    cout<<endl;
}

int check_mapping_flag(int level){
    int flag = 1;
    for(int i = 0; i < word_lengths[level]; i++) {
        if(word_to_dict[words[level][i]-ascii_base] == 0)
            flag = 0;
        else 
            temp_map[i] = word_to_dict[words[level][i]-ascii_base];
    }
    temp_map[word_lengths[level]] = '\0';
    
    if(flag == 1){
        if(dict_words_set.find(temp_map) == dict_words_set.end())
            return flag;
        else
             flag = 2;
    }
    return flag; 
}


void check_by_word_level(int level) {
    if(is_decryptable)  
        return;
    bool is_right_map;
    int mapping_flag = 1;

    if(level == word_count) {
        is_decryptable = true;
        print_response(is_decryptable);
        return;
    }

    mapping_flag = check_mapping_flag(level);
    
    if(mapping_flag == 1)
        return;
    else if(mapping_flag == 2)
        check_by_word_level(level+1);

    else {
        char word_to_dict_backup[26], dict_to_word_backup[26];
        for(int i = 0; i < dict_word_count; i++) {
            if(word_lengths[level] != dict_word_lengths[i])
                continue;

            copy_dict(word_to_dict, word_to_dict_backup);
            copy_dict(dict_to_word, dict_to_word_backup);
            is_right_map = true;
            //mapping letters of word to dict and
            //mapping letters of dict to word
            for(int letter = 0; letter < dict_word_lengths[i]; letter++) {
                if(word_to_dict[words[level][letter]-ascii_base] == 0) {
                    if(dict_to_word[dict_words[i][letter]-ascii_base])
                        is_right_map = false;
                    word_to_dict[words[level][letter]-ascii_base] = dict_words[i][letter];
                    dict_to_word[dict_words[i][letter]-ascii_base] = words[level][letter];
                } 
                else {
                    if(word_to_dict[words[level][letter]-ascii_base] != dict_words[i][letter]) {
                        is_right_map = false;
                        break;
                    }
                }
            }
            if(is_right_map)
                check_by_word_level(level+1);
            copy_dict(word_to_dict_backup, word_to_dict);
            copy_dict(dict_to_word_backup, dict_to_word);
            
            if(is_decryptable)
                return;
        }
    }
}
int main() {

    cin>>dict_word_count;
    string line;

    for(int i = 0; i < dict_word_count; i++) {
        cin>> dict_words[i];
        dict_word_lengths[i] = dict_words[i].length();
        dict_words_set.insert(dict_words[i]);
    }

    while(getchar() != '\n');
    getline(cin, line);
    while(line != "") {
        word_count = 0;
        is_decryptable = false;
        create_dict(word_to_dict);
        create_dict(dict_to_word);

        stringstream sentence;
        string word;

        sentence<<line;

        while(sentence >> word){
            words[word_count] = word;
            word_lengths[word_count++] = word.length();
        }
        
        check_by_word_level(0);

        if(!is_decryptable) {
            print_response(is_decryptable);
        }
        getline(cin, line);
    }
    return 0;
}
