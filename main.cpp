#include <cstring>
#include <fstream>
#include <iostream>


bool check_word(char* word, char* word_for_check) {

    for(int i = 0; i < strlen(word_for_check); i++) {
        bool is_found = false;
        for(int j = 0; j < strlen(word); j++) {
            if(word_for_check[i] == word[j]) {
                is_found = true;
                break;
            }
        }
        if(!is_found) {
            return false;
        }
    }
    return true;
}

int check_all_words(char* word, char* PATH, bool need_to_print){

    std::ifstream myfile;
    myfile.open(PATH);

    char files_word[33];
    char current_ch;
    int index = 0;
    int count = 0;

    if(!myfile.is_open()) {
        std::cerr << "Can't read a file" << std::endl;
        return -1;
    }

    while(myfile.get(current_ch)) {
        if(current_ch == ' ' || current_ch == '\n' || current_ch == '\0') {
            if(index > 0) {
                files_word[index] = '\0';
                if(check_word(files_word, word)) {
                    count++;
                    if(need_to_print){
                       std::cout << count <<". " << files_word << std::endl; 
                    }
                    
                }
                index = 0; 
            }
        } 
        else {
            if(index < 32){
                files_word[index++] = current_ch;
            }
        }
    }
    myfile.close();
    return count;
}

int find_words_count(char* word, char* PATH, bool need_to_print = 1) {
    if(need_to_print){
        std::cout << "##############" << std::endl;
    }
    int count = check_all_words(word, PATH, need_to_print);
    if(need_to_print){
        std::cout << "##############" << std::endl;
    }
    return count;
}

int main(int argc, char *argv[]) {
    char* word = nullptr;
    char* filename = nullptr;
    
    if(argc < 5) {
        std::cerr << argv[0] << " -f <file_name> -w <word_to_find>" << std::endl;
        return 1;
    }
    
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-w") == 0) {
            if(i + 1 < argc) {
                word = argv[i + 1];
                i++;
            } else {
                std::cerr << "Error: Missing value for -w flag" << std::endl;
                return 1;
            }
        } 
        else if(strcmp(argv[i], "-f") == 0) {
            if(i + 1 < argc) {
                filename = argv[i + 1];
                i++;
            } else {
                std::cerr << "Error: Missing value for -f flag" << std::endl;
                return 1;
            }
        }
        else {
            std::cerr << "Warning: Unknown argument " << argv[i] << std::endl;
        }
    }

    std::cout << "word: " << word << " | " << "file: "<< filename << std::endl;
    int result = find_words_count(word, filename, 1);
    
    if(result >= 0) {
        std::cout << "Number of words with '" << argv[2] << "' string: " << result << std::endl;
    }
    
    return 0;
}