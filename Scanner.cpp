#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

typedef enum{
    ReservedWord,LibraryName,Comment,Identifier,Constant,Operator,Comparator,Bracket,FormatSpecifier,Pointer,Address,Punctuation,PrintedToken
} TOKENCLASS;

typedef struct Token{
    TOKENCLASS tokenClass;
    map<string,int> word;
} TOKEN;

class Scanner{
public:
    bool init(const char[]);
    void getToken();
private:
    void initToken();
    int isLetter(char);
    int isDigit(char);
    int isWhiteSpace(char);
    void printLine(int);
    void jumpSpace();
    int moveChar();
    

    fstream FILEIN,FILEOUT;
    vector<vector<char>> text;
    TOKEN token[13];
    int n_char = 0 , t_char = 0;
    int n_line = 0 , t_line = 0; 
    char c=' ';

};

bool Scanner::init(const char fn[]){
    FILEIN.open(fn,ios::in);
    if(!FILEIN) return false;

    string line;

    while(getline(FILEIN,line)){
        vector<char> c;
        for(int i = 0 ; i < line.length() ; i++)
            c.push_back(line[i]);
        text.push_back(c);
    }
    t_line = text.size();
    FILEIN.close();
    initToken();

    return true;
}

void Scanner::initToken(){
    //ReservedWord,LibraryName,Comment,Identifier,Constant,Operator,Comparator,Bracket,FormatSpecifier,Pointer,Address,Punctuation,PrintedToken
    token[0].tokenClass = ReservedWord;
    token[1].tokenClass = LibraryName;
    token[2].tokenClass = Comment;
    token[3].tokenClass = Identifier;
    token[4].tokenClass = Constant;
    token[5].tokenClass = Operator;
    token[6].tokenClass = Comparator;
    token[7].tokenClass = Bracket;
    token[8].tokenClass = FormatSpecifier;
    token[9].tokenClass = Pointer;
    token[10].tokenClass = Address;
    token[11].tokenClass = Punctuation;
    token[12].tokenClass = PrintedToken;   
}

int Scanner::isLetter(char ch){
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

int Scanner::isDigit(char ch){
    return (ch >= '0' && ch <= '9');
}

int Scanner::isWhiteSpace(char ch){
    return (ch == ' ' || ch == '\t' || ch == '\n');
}

void Scanner::printLine(int n_line){
    for(auto i : text[n_line])
        cout<<i;
    cout<<"\n";
}

void Scanner::jumpSpace(){

    while(text[n_line].size() == 0 && (n_line < t_line && n_char < t_char)){
        
        n_line++;
        n_char = 0;
        t_char = text[n_line].size();
        //log
        cout<<"[func] jumpSpace-jump:\t";
        cout<<"line:\t"<<n_line<<"\tpos:\t"<<n_char<<"\n";
        cout<<"t_line:\t"<<t_line<<"\tt_char:\t"<<t_char<<"\n";
    }
}

int Scanner::moveChar(){
    
    jumpSpace();

    if(n_char < t_char)
        n_char++;
    else if(n_line < t_line){
        
        n_line++;
        n_char = 0;
        t_char = text[n_line].size();
        //log
        cout<<"[func] moveChar-new line:\t";
        cout<<"line:\t"<<n_line<<"\tpos:\t"<<n_char<<"\n";
        cout<<"t_line:\t"<<t_line<<"\tt_char:\t"<<t_char<<"\n";

        jumpSpace();

    }
    return 0;
}

void Scanner::getToken(){

    t_char = text[n_line].size();
    string buff;
    int state = 0; 
    bool foundToken = false;
    bool foundLibrary = false;

    while( (n_line < t_line || (n_char < t_char ))){
        foundToken = false;
        c = text[n_line][n_char];
        //log
        cout<<"[func] getToken-out:\t";
        cout<<"line:\t"<<n_line<<"\tpos:\t"<<n_char<<"\tchar:\t"<<c<<"\tstate: "<<state<<"\t";
        cout<<"t_line:\t"<<t_line<<"\tt_char:\t"<<t_char<<"\n";
        
        while(!foundToken){ // && (n_line < t_line && n_char < t_char)
            c = text[n_line][n_char];
            //log
            cout<<"[func] getToken-in:\t";
            cout<<"line:\t"<<n_line<<"\tpos:\t"<<n_char<<"\tchar:\t"<<c<<"\tstate: "<<state<<"\t";
            cout<<"t_line:\t"<<t_line<<"\tt_char:\t"<<t_char<<"\n";

            switch(state){
                case 0:
                    if(isLetter(c)) state = 1;
                    else if(isDigit(c)) state = 2;
                    else if(c == '+') state = 3;
                    else if(c == '-') state = 4;
                    else if(c == '*') state = 5;
                    else if(c == '/') state = 6;
                    else if(c == '%') state = 7;
                    else if(c == '^') state = 8;
                    else if(c == '&') state = 9;
                    else if(c == '|') state = 10;
                    else if(c == '=') state = 11;
                    else if(c == '<') state = 12;
                    else if(c == '>') state = 13;
                    else if(c == '!') state = 14;
                    else if(c == '(') state = 15;
                    else if(c == ')') state = 16;
                    else if(c == '[') state = 17;
                    else if(c == ']') state = 18;
                    else if(c == '{') state = 19;
                    else if(c == '}') state = 20;
                    else if(c == ',') state = 21;
                    else if(c == ';') state = 22;
                    else if(c == ':') state = 23;
                    else if(c == '#') state = 24;
                    else if(c == '\\') state = 25;
                    else if(c == '\'') state = 26;
                    else if(c == '\"') state = 27;
                    else if(c == '.') state = 28;    //小數點
                    else if(isWhiteSpace(c)) state = 29;
                    else{
                        if(n_line < t_line && n_char < t_char){
                            cout<<"[Error] Unrecongized Token found at line: ";
                            printLine(n_line);
                        }
                            
                        n_line++;
                        t_char = text[n_line].size();
                        n_char = 0;
                        state =0;
                        foundToken = true;
                    }
                    break;
                case 1:
                    if(isLetter(c) || isDigit(c)){
                        buff.push_back(c);
                        //log
                        cout<<"(state 1) buff-if: \t"<<buff<<"\n";
                        state = 1;
                        moveChar();
                    }
                    else{
                        //log
                        cout<<"(state 1) buff-else: \t"<<buff<<"\n";

                        regex RW_include("[iI][nN][cC][lL][uU][dD][eE]");
                        if(regex_match(buff,RW_include)){
                            token[0].word["include"]++;
                            state = 0;
                            foundLibrary = true;
                            foundToken = true;
                            buff = "";
                            //log
                            cout<<"RW - include\t"<<token[0].word["include"]<<"\n";                           
                            break;
                        }

                        regex RW_main("[mM][aA][iI][nN]");
                        if(regex_match(buff,RW_main)){
                            token[0].word["main"]++;
                            state = 0;
                            foundToken = true;
                            buff = "";
                            //log
                            cout<<"RW - main\t"<<token[0].word["main"]<<"\n";
                            break;
                        }
                    }
                    break;
                case 12:
                    while(foundLibrary){
                        buff.push_back(c);
                        //log
                        cout<<"(state 12) buff-library: \t"<<buff<<"\n";
                    }
            }
        }
    }
}


int main(int argc,char* argv[]){

    if(argc < 2){
        cout<<"[Error] It's lack of the input file.\n";
        return 2;
    }

    Scanner s;
    if(!s.init(argv[1])){
        cout<<"[Error] "<<argv[1]<<" can't be opened.\n";
        return 2;
    }

    s.getToken();
    return 0;
}