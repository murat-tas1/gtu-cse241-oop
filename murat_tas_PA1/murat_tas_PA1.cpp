#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>
using namespace std;
const int length_of_the_alphabet = 256; /*maximum length of the alpabet according to ascı 2^8*/

int is_number(const char str[]){ /*check whether entered string is number*/
    int i;
    int len = strlen(str);
    for(i = 0; i < len; ++i){
        if(!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}
int read_file(char alphabet[],int &index){ /*get the chars from the alphabet.txt to alphabet[]*/
    int i,flag;                            /*index means number of alphabet chars as an output parameter*/
    char ch;
    ifstream inputStream;  /*create a ifstream object*/
    inputStream.open("alphabet.txt"); /*open file to read*/
    if(inputStream){           /*if file is opened*/
        while(inputStream >> ch){         /*read the file char by char* untill EOF*/
            flag = 1;
            for(i = 0; i < index; ++i){ /*check whether there is repeating number..at first index starts 0*/
                if(alphabet[i] == ch){
                flag = 0;
                break; /*repeating letter*/
                }
            } /*if flag stays as a 1 then there is no repeating numbers*/
            if(flag == 1 && ch !=' ' && ch != ',' && ch != '\n' && ch != '\t'){ /*ignoring these*/
            alphabet[index] = ch;
            ++index;
            }
        }
        inputStream.close(); /*close the file*/
        return 1; /*reading file is succesfull*/
    }
    else
    return 0; /*reading file failed*/
}
void generate_secret_word(char secret_word[],int word_size,const char alphabet[],int alphabet_size){
    int i = 0,j,rand_num,flag; /*secret word means the word which will be cretaed randomly*/
    while(i < word_size){ /*generate a random word size is gonna be entered_size in termianl and no repeating*/
        flag = 1;
        rand_num = rand() % alphabet_size; /*stay in alphabet border*/
        for(j = 0; j<i; ++j){ /*check whether there is repetion*/
            if(secret_word[j] == alphabet[rand_num]){
                flag = 0;
                break;
            }   
        }
        if(flag == 1){ /*if flag stays as a 1 then there is no repeating numbers*/
        secret_word[i] = alphabet[rand_num];
        ++i;
        }
}
}
void print_alphabet(const char alphabet[],int alphabet_size){ /*print the alphabet on the console*/
    int i;
    cout <<"[";
    for(i = 0; i < alphabet_size - 1; ++i)
    cout <<alphabet[i]<<",";
    cout << alphabet[alphabet_size - 1] <<"]"<<endl;
}
     /* Counts how many characters match in exact positions (Cexact) */
int find_first_count(const char secret_word[],const string entered_word,int word_size){
    int i,count = 0; /*word size is the size of entered word eg:-r 12 12 is word size here*/
    for(i = 0; i < word_size; ++i){
        if(secret_word[i] == entered_word[i])
        ++count; 
    }
    return count;
}
 /* Counts how many valid characters are present but in the wrong positions (Cmisplaced)*/
int find_second_count(const char secret_word[],const string entered_word,int word_size){
    int i,j,count = 0;
    for(i = 0; i < word_size; ++i){
        for(j = 0; j < word_size;++j){
            if(secret_word[i] == entered_word[j] && i != j)
            ++count;
        }
    }
    return count;
}
/* Checks if entered_word is valid:
   1) No repeated characters within the word.
   2) Every character exists in alphabet.
   Returns 1 if valid, 0 otherwise. */
int check_valid_word(const char alphabet[],const string entered_word,int word_size,int alphabet_size){
    int check = 1;
    int i,j;
    for(i = 0; i < word_size - 1; ++i){ /*check repeating numbers*/
        for(j = i + 1;  j < word_size;++j){
            if(entered_word[i] == entered_word[j]){
                check = 0;
                return check;
            }
        }
    }
    for(i = 0; i < word_size; ++i){ /*check every character exists in alphabet  */
        check = 0;
        for(j = 0; j < alphabet_size; ++j){
            if(entered_word[i] == alphabet[j]){
                check = 1; /*if there is a number in alphabet which matching  char of entered word set check 1*/
                break; /*set check one and break and continue the other char of entered word*/
            }
        }
        if(check == 0){
        return check; /*the letter which does not belong to alphabet*/
        }
    }
    return check;

}
int main(int argc,char *argv[]){ /*these are command line arguments*/
    if (argc !=3 ) {     /*If number of command-line args is not 3 => input error*/
        cout << "INPUT ERROR" << endl;
        return 0;
    }
    srand(time(0)); /* Initialize random seed once*/
    char alphabet[length_of_the_alphabet],ch;
    char secret_word[length_of_the_alphabet];
    int index = 0; /* Holds how many chars have been loaded into alphabet array*/
    int entered_num,size,c_exact ,c_misplaced; /* entered_num is user-provided length,size is alphabet length*/
    int iteration = 0; /* Keeps track of how many guesses were made*/
    string word; /*string object it will store the user's guess*/

    if(strcmp(argv[1],"-r") ==0){ /* Check first argument: -r or -u */
       if(!is_number(argv[2])){ /*Check if argv[2] is a valid positive integer*/
        cout <<"INPUT ERROR\n";
        return 1;
       }
       entered_num = stoi(argv[2]);
       int status = read_file(alphabet,index); /*read the alphabet file*/
       size = index; /*size means the size of alphabet[]*/
       if(entered_num > size || entered_num <= 0){ /*If the requested length is out of valid range*/
        cout <<"INPUT ERROR\n";
        return 1;
        }
       if(status == 0){ /*Check if file reading failed*/
        cout <<"FILE OPENING ERROR!!!\n";
        return 1;
    }
       else{ /*if file reading is succesfull*/
        size = index;  /*this is right now alphabet size filled array*/
        print_alphabet(alphabet,size);
        generate_secret_word(secret_word,entered_num,alphabet,size);/*Generate the random secret word*/
        while(iteration < 100){ /*Start taking guesses from user*/
            cin >>word;
            int check = check_valid_word(alphabet,word,entered_num,size);
            int len = word.size();
            if(check == 0 || len != entered_num){ /*If not valid or length mismatch print input error*/
                cout <<"INPUT ERROR\n";
                return 1;
            }
            ++iteration;
            /*Compute exact and misplaced counts*/
            c_exact = find_first_count(secret_word,word,entered_num);
            c_misplaced = find_second_count(secret_word,word,entered_num);
            if(c_exact ==entered_num){ /* If user found the secret*/
                cout <<"FOUND "<<iteration<<endl;
                return 1;
            }
            /* Otherwise, print the hint*/
            cout <<c_exact<<" "<<c_misplaced<<endl;
        }
        if(iteration == 100){ /* If user cannot find in 100 tries*/
            cout <<"FAILED"<<endl;
            return 1;
        }
       }

    }
    else if(strcmp(argv[1],"-u") ==0){ /*by user proviede secret word -u secret word*/
        int status = read_file(alphabet,index);
        if(status == 0){
            cout <<"FILE OPENING ERROR!!!\n";
            return 1;
        }
        size = index;  /*size means the size of alphabet[]*/
        int len = strlen(argv[2]); /*len means the size of secret word*/
        string secret_word(argv[2]); /*string constructor to convert char array to a string object*/
        /*Check if by user-provided secret is valid*/
       int check =  check_valid_word(alphabet,secret_word,len,size);
       if(check == 0 || len > size){
        cout <<"INPUT ERROR"<<endl;
        return 1;
       }
       print_alphabet(alphabet,size);
        /*Start taking guesses*/
       while(iteration < 100){
           cin >>word;
           int check = check_valid_word(alphabet,word,len,size);
           int word_len = word.size();
           /* If guess is invalid or length mismatch*/
           if(check == 0 || len !=word_len){
               cout <<"INPUT ERROR\n";
               return 1;
           }
           ++iteration;
           /*Calculate exact and misplaced counts*/
           c_exact = find_first_count(argv[2],word,len);
           c_misplaced = find_second_count(argv[2],word,len);
           if(c_exact ==len){ /* If guessed perfectly*/
               cout <<"FOUND "<<iteration<<endl;
               return 1;
           } /*oherwise print the hint*/
           cout <<c_exact<<" "<<c_misplaced<<endl;
       }
       if(iteration == 100){ /*If user cannot find in 100 tries*/
           cout <<"FAILED"<<endl;
           return 1;
       }
      }
      else{ /*If neither -r nor -u*/
        cout << "INPUT ERROR"<<endl;
        return 1;
      }
      return 0;
    }