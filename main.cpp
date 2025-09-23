#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <getopt.h>
#include <cctype>

int main(int argc, char *argv[]) {
    char* filename = nullptr;
    char* word = nullptr;
    
    int opt;
    while((opt = getopt(argc, argv, "f:w:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'w':
                word = optarg;
                break;
            default:
                std::cout << "Usage:" << argv[0] << " -f <filename> -w <word>" << std::endl;
                return 1;
        }
    }
    
    if (!filename || !word) {
        std::cout << "Usage:" << argv[0] << " -f <filename> -w <word>" << std::endl;
        return 1;
    }
    
    std::ifstream myfile;
    myfile.open(filename, std::ios::binary | std::ios::ate);
    if (!myfile.is_open()) {
        std::cout << "Can't read a file" << std::endl;
        return 1;
    }

    int size = myfile.tellg();
    char* textFile = new char[size+1];

    myfile.seekg(0);
    myfile.read(textFile, size);
    textFile[size] = '\0';

    int left = 0;
    int right;

    for(int i = 0; i<size; i++){
        if(textFile[i] == ' ' || textFile[i] == '\n' || textFile[i] == '\0'){
            bool needToPrint = true;
            right = i-1;

            for(int w = 0; w < strlen(word); w++){
                bool isInTextWord = false;
                for(int j = left; j<=right; j++){
                    if(tolower(word[w]) == tolower(textFile[j])){
                        isInTextWord = true;
                    }
                }
                if(!isInTextWord){
                    needToPrint = false;
                    break;
                }
            }
            if(needToPrint){
                for(int j = left; j<=right; j++){
                    std::cout << textFile[j];
                }
                if(textFile[i] != '\0'){
                    std::cout << " ";
                }
            }
            left = i+1;
        } 
    }
    delete[] textFile;
    return 0;
}