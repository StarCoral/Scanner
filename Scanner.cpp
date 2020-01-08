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
    bool outputFile(const char []);
    void getToken();
    void printText();
private:
    void initToken();
    int isLetter(char);
    int isDigit(char);
    int isWhiteSpace(char);
    void printLine(int);
    void jumpSpace();
    int moveChar();
    void moveNextLine();
    int countToken();
    int countTokenClass(int);

    fstream FILEIN,FILEOUT;
    vector<vector<char>> text;
    TOKEN token[13];
    
    int n_char = 0 , t_char = 0;
    int n_line = 0 , t_line = 0; 
    char c=' ';
    int STOP = 0;
    int t_token = 0;
};

bool Scanner::init(const char fn[]){
    FILEIN.open(fn,ios::in);
    if(!FILEIN) return false;

    string line;

    while(getline(FILEIN,line)){
        vector<char> c;
        c.push_back(' ');
        for(int i = 0 ; i < line.length() ; i++)
            c.push_back(line[i]);
        c.push_back(' ');
        text.push_back(c);
    }
    t_line = text.size();
    //text[t_line-1].push_back(' ');
    FILEIN.close();
    initToken();

    return true;
}

int Scanner::countToken(){
    for(int i =0 ; i < 13 ;i++){
        for(auto &j : token[i].word){
            t_token +=j.second;
        }
    }
    return t_token;
}

int Scanner::countTokenClass(int c){
    int num = 0;
    for(auto &i : token[c].word){
        num+= i.second;
    }
    return num;
}

bool Scanner::outputFile(const char fn[]){
    FILEOUT.open(fn,ios::out);
    if(!FILEOUT) return false;

    for(int i = 0 ; i < t_line ; i++){
        for(int j = 1 ; j < text[i].size();j++)
            FILEOUT << text[i][j];
        FILEOUT<<"\n";
    }
    FILEOUT<<"\n\n------------------------\n\n";
    FILEOUT<<"\nTotal: "<<countToken()<<" tokens\n";
    
    int num;
    
    if(countTokenClass(0) > 0)
    {
        FILEOUT<<"\n\nReserved word: "<<countTokenClass(0)<<"\n";
        
        num = token[0].word["include"];
        if(num > 0){
            FILEOUT<<"include\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["main"];
        if(num > 0){
            FILEOUT<<"main\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["char"];
        if(num > 0){
            FILEOUT<<"char\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["int"];
        if(num > 0){
            FILEOUT<<"int\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["float"];
        if(num > 0){
            FILEOUT<<"float\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["if"];
        if(num > 0){
            FILEOUT<<"if\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["else"];
        if(num > 0){
            FILEOUT<<"else\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["elseif"];
        if(num > 0){
            FILEOUT<<"elseif\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["for"];
        if(num > 0){
            FILEOUT<<"for\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["while"];
        if(num > 0){
            FILEOUT<<"while\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["do"];
        if(num > 0){
            FILEOUT<<"do\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["return"];
        if(num > 0){
            FILEOUT<<"return\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["switch"];
        if(num > 0){
            FILEOUT<<"switch\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["case"];
        if(num > 0){
            FILEOUT<<"case\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["printf"];
        if(num > 0){
            FILEOUT<<"printf\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[0].word["scanf"];
        if(num > 0){
            FILEOUT<<"scanf\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
    }
    
    if(countTokenClass(1) > 0)
    {
        FILEOUT<<"\n\nLibrary name: "<<countTokenClass(1)<<"\n";
        for(auto &i: token[1].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(2) > 0)
    {
        FILEOUT<<"\n\nComment: "<<countTokenClass(2)<<"\n";
        for(auto &i: token[2].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(3) > 0)
    {
        FILEOUT<<"\n\nIdentifier: "<<countTokenClass(3)<<"\n";
        for(auto &i: token[3].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(4) > 0)
    {
        FILEOUT<<"\n\nConstant: "<<countTokenClass(4)<<"\n";
        for(auto &i: token[4].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(5) > 0)
    {
        FILEOUT<<"\n\nOperator: "<<countTokenClass(5)<<"\n";
        
        num = token[5].word["+"];
        if(num > 0){
            FILEOUT<<"+\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["-"];
        if(num > 0){
            FILEOUT<<"-\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["*"];
        if(num > 0){
            FILEOUT<<"*\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["/"];
        if(num > 0){
            FILEOUT<<"/\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["%"];
        if(num > 0){
            FILEOUT<<"%\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["^"];
        if(num > 0){
            FILEOUT<<"^\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["++"];
        if(num > 0){
            FILEOUT<<"++\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["--"];
        if(num > 0){
            FILEOUT<<"--\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["&"];
        if(num > 0){
            FILEOUT<<"&\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["|"];
        if(num > 0){
            FILEOUT<<"|\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }
        num = token[5].word["="];
        if(num > 0){
            FILEOUT<<"=\t";
            if(num > 1)
                FILEOUT<<"(x"<<num<<")";
            FILEOUT<<"\n";
        }

    }
    if(countTokenClass(6) > 0)
    {
        FILEOUT<<"\n\nComparator: "<<countTokenClass(6)<<"\n";
        for(auto &i: token[6].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(7) > 0)
    {
        FILEOUT<<"\n\nBracket: "<<countTokenClass(7)<<"\n";
        for(auto &i: token[7].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(8) > 0)
    {
        FILEOUT<<"\n\nFormat specifier: "<<countTokenClass(8)<<"\n";
        for(auto &i: token[8].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(9) > 0)
    {
        FILEOUT<<"\n\nPointer: "<<countTokenClass(9)<<"\n";
        for(auto &i: token[9].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(10) > 0)
    {
        FILEOUT<<"\n\nAddress: "<<countTokenClass(10)<<"\n";
        for(auto &i: token[10].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(11) > 0)
    {
        FILEOUT<<"\n\nPunctuation: "<<countTokenClass(11)<<"\n";
        for(auto &i: token[11].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }
    if(countTokenClass(12) > 0)
    {
        FILEOUT<<"\n\nPrinted token: "<<countTokenClass(12)<<"\n";
        for(auto &i: token[12].word){
            num = i.second;
            if(num > 0){
                FILEOUT<<i.first<<"\t";
                if(num > 1)
                    FILEOUT<<"(x"<<num<<")";
                FILEOUT<<"\n";
            }
        }
    }

    FILEOUT.close();
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

void Scanner::printText(){
    cout<<"------------------------\n";
    for(int i = 0 ; i < t_line ; i++){
        //vector<char> temp = text[i];
        cout<<i<<": ";
        for(int j = 0 ; j < text[i].size();j++)
            cout<<text[i][j];
        cout<<"\n";
    }
    cout<<"------------------------\n";
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
        c=' ';
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
    if(n_line < t_line && n_char>=t_char ){
        
        n_line++;
        n_char = 0;
        t_char = text[n_line].size();
        //log
        cout<<"[func] moveChar-new line:\t";
        cout<<"line:\t"<<n_line<<"\tpos:\t"<<n_char<<"\t";
        cout<<"t_line:\t"<<t_line<<"\tt_char:\t"<<t_char<<"\n";
        jumpSpace();

    }
    c = ' ';
    if((n_char>=t_char && n_line>=t_line) || n_line>=t_line){
        cout<<"[func] moveChar-STOP:\n";
        return 1;
    }
    return 0;
}

void Scanner::moveNextLine(){
    jumpSpace();
    if(n_line<t_line){
        n_line++;
        n_char = 0;
        t_char = text[n_line].size();
        c = ' ';
    }
}

void Scanner::getToken(){

    t_char = text[n_line].size();
    string buff;
    int state = 0; 
    bool foundToken = false;
    bool foundLibrary = false;
    bool foundType = false;
    bool foundPrintf = false;
    int varLine = -1;
    int printfCount = 0;
    int pointCount = 0;
    int COUNT =0;
    while( (n_line < t_line && n_char < t_char )){
        foundToken = false;
        c = text[n_line][n_char];
        //log
        cout<<"[func] getToken-out:\t";
        cout<<"line:\t"<<n_line<<"\tt_char:\t"<<t_char<<"\tpos:\t"<<n_char<<"\tchar:\t"<<c<<"\tstate: "<<state<<"\t";
        cout<<"\tt_line:\t"<<t_line<<"\n";
        
        while(!foundToken ){ // && (n_char<=t_char-1 && n_line<t_line-1)
           
            
            if(n_line < t_line && n_char < t_char )
                c = text[n_line][n_char];
            else
            {   cout<<"COUNT?\t"<<COUNT<<"\n";
                c = ' ';
                COUNT++;
                if(COUNT>1) //foundToken=true;
                    return ;
            }
                
            //log
            cout<<"[func] getToken-in:\t";
            cout<<"line:\t"<<n_line<<"\tt_char:\t"<<t_char<<"\tpos:\t"<<n_char<<"\tchar:\t"<<c<<"\tstate: "<<state<<"\t";
            cout<<"\tt_line:\t"<<t_line<<"\n";

            switch(state){
                if(varLine != n_line)
                        foundType = false;
                case 0:
                    if(isLetter(c) && !foundPrintf) state = 1;
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
                    else if(foundPrintf) state = 30;
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
                    if(varLine != n_line)
                        foundType = false;
                    cout<<"varLine:"<<varLine<<"\n";
                    if((isLetter(c) || isDigit(c) || c == '_') && STOP < 1){
                        buff.push_back(c);
                        //log
                        cout<<"(state 1) buff-if: \t"<<buff<<"\n";
                        state = 1;
                        STOP = moveChar();
                        cout<<"STOP: "<<STOP<<"\n";
                    }
                    else{
                        //log
                        cout<<"(state 1) buff-else: \t"<<buff<<"\n";
                        cout<<"FOUNDTYPE: "<<foundType<<"\t var_line: "<<varLine<<"\n";

                        smatch m;
                        //ssub_match sm;
                        int pos;

                        regex RW_include("[iI][nN][cC][lL][uU][dD][eE]");
                        while(regex_search(buff,m,RW_include)){
                            for(auto &match : m){
                                //sm = match;
                                pos = m.position();
                                token[0].word["include"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                
                                state = 0;
                                foundLibrary = true;
                                foundToken = true;
                                //buff = "";
                                //log
                                cout<<"RW - include\t"<<token[0].word["include"]<<"\n";
                                cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_printf("[pP][rR][iI][nN][tT][fF]");
                        while(regex_search(buff,m,RW_printf)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["printf"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                foundPrintf = true;
                                varLine = n_line;
                                //log
                                 cout<<"RW - printf\t"<<token[0].word["printf"]<<"\n";
                                 cout<<"varLine: "<<varLine<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_main("[mM][aA][iI][nN]");
                        while(regex_search(buff,m,RW_main)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["main"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                 //log
                                 cout<<"RW - main\t"<<token[0].word["main"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_char("[cC][hH][aA][rR]");
                        while(regex_search(buff,m,RW_char)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["char"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                foundType = true;
                                varLine = n_line;
                                 //log
                                 cout<<"RW - char\t"<<token[0].word["char"]<<"\n";
                                 cout<<"varLine: "<<varLine<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_int("[iI][nN][tT]");
                        while(regex_search(buff,m,RW_int)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["int"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                foundType = true;
                                varLine = n_line;
                                 //log
                                 cout<<"RW - int\t"<<token[0].word["int"]<<"\n";
                                 cout<<"varLine: "<<varLine<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_float("[fF][lL][oO][aA][tT]");
                        while(regex_search(buff,m,RW_float)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["float"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                foundType = true;
                                varLine = n_line;
                                 //log
                                 cout<<"RW - float\t"<<token[0].word["float"]<<"\n";
                                 cout<<"varLine: "<<varLine<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_elseif("[eE][lL][sS][eE][iI][fF]");
                        while(regex_search(buff,m,RW_elseif)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["elseif"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - elseif\t"<<token[0].word["elseif"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_if("[iI][fF]");
                        while(regex_search(buff,m,RW_if)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["if"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - if\t"<<token[0].word["if"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_else("[eE][lL][sS][eE]");
                        while(regex_search(buff,m,RW_else)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["else"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - else\t"<<token[0].word["else"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_for("[fF][oO][rR]");
                        while(regex_search(buff,m,RW_for)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["for"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - for\t"<<token[0].word["for"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_while("[wW][hH][iI][lL][eE]");
                        while(regex_search(buff,m,RW_while)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["while"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - while\t"<<token[0].word["while"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_do("[dD][oO]");
                        while(regex_search(buff,m,RW_do)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["do"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - do\t"<<token[0].word["do"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_return("[rR][eE][tT][uU][rR][nN]");
                        while(regex_search(buff,m,RW_return)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["return"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - return\t"<<token[0].word["return"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_switch("[sS][wW][iI][tT][cC][hH]");
                        while(regex_search(buff,m,RW_switch)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["switch"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - switch\t"<<token[0].word["switch"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_case("[cC][aA][sS][eE]");
                        while(regex_search(buff,m,RW_case)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["case"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - case\t"<<token[0].word["case"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }
                        regex RW_scanf("[sS][cC][aA][nN][fF]");
                        while(regex_search(buff,m,RW_scanf)){
                            for(auto &match : m){
                                pos = m.position();
                                token[0].word["scanf"]++;
                                buff = buff.substr(0,pos)+buff.substr(pos+m.length());
                                state = 0;
                                foundToken = true;
                                //log
                                 cout<<"RW - scanf\t"<<token[0].word["scanf"]<<"\n";
                                 cout<<"BUFF\t"<<buff<<"\n";
                            }
                        }

                        if(foundType){
                            if(c == '_'){
                                buff.push_back(c);
                                //log
                                cout<<"(Found type) buff: "<<buff<<"\n";
                                state = 1;
                                STOP = moveChar();
                                break;
                            }
                            regex IDEN("^[a-zA-Z]\\w*_*");
                            if(regex_match(buff,IDEN)){
                                token[3].word[buff]++;
                                state = 0;
                                if(varLine != n_line)
                                    foundType = false;
                                foundToken = true;
                                cout<<"Ident - "<<buff<<": "<<token[3].word[buff]<<"\n";
                            }  
                            regex AD("^&[a-zA-Z]\\w*_*");
                            if(regex_match(buff,AD)){
                                token[10].word[buff]++;
                                state = 0;
                                if(varLine != n_line)
                                    foundType = false;
                                foundToken = true;
                                cout<<"AD - "<<buff<<": "<<token[10].word[buff]<<"\n";
                            }  
                            regex POINT("^\\*[a-zA-Z]\\w*_*");
                            if(regex_match(buff,POINT)){
                                token[9].word[buff]++;
                                state = 0;
                                if(varLine != n_line)
                                    foundType = false;
                                foundToken = true;
                                cout<<"Point - "<<buff<<": "<<token[9].word[buff]<<"\n";
                            } 
                            buff = "";
                            break; 
                        }
                        
                        if(token[3].word[buff]>0){
                            token[3].word[buff]++;
                            cout<<buff<<" : "<<token[3].word[buff]<<"\n";
                            state = 0;
                            buff = "";
                            
                            break;
                        }
                        
                        else if(buff.size()>0 ){ //&& token[3].word[buff]<=0 && (n_line < t_line &&  n_char >= 0 && n_char < t_char)
                            cout<<"[Error] line "<<n_line<<" : "<<buff<<" is Unrecognized. \n";
                            foundToken = true;
                            moveNextLine();
                            buff = ""; //
                            state =0;
                        }
                        if(STOP<0)
                            STOP = moveChar();
                        if(varLine != n_line)
                            foundType = false;
                    }
                    break;
                case 2:
                {
                    cout<<"<state 2> BUFF: "<<buff<<"\n";
                    if((isDigit(c)) && STOP < 1){
                        buff.push_back(c);
                        state = 2;
                        STOP = moveChar();
                        //c = text[n_line][n_char];
                        //log
                        cout<<"(state 2)judge the constant- buff: \t"<<buff<<"\n";
                        cout<<"STOP: "<<STOP<<"\n";
                    }
                    else if(c == '.' && STOP <1 && printfCount <1){
                        state = 28;
                        pointCount ++;
                        break;
                    }
                    else{
                        pointCount = 0;
                        //log
                        cout<<"(state 2)judge the constant- else: \t"<<buff<<"\n";
                        token[4].word[buff]++;
                        foundToken = true;
                        state = 0;
                        //STOP = moveChar();
                        //log
                        cout<<"Constant "<<buff<<":\t"<<token[4].word[buff]<<"\n";
                        buff="";
                    }
                    break;
                }
                case 3:
                {
                    int curLine = n_line , curChar = n_char;
                    int curTchar = t_char;
    
                    foundToken = true;
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];
                    if(tem == '+'){
                        buff.push_back(tem);
                    }
                    else{
                        n_line = curLine;
                        n_char = curChar;
                        t_char = curTchar;
                    }
                    STOP = moveChar();
                    state = 0;
                    token[5].word[buff]++;
                    //log
                    cout<<"line:\t"<<n_line<<"\tt_char:\t"<<t_char<<"\tpos:\t"<<n_char<<"\tchar:\t"<<c<<"\tstate: "<<state<<"\t";
                    cout<<"\tt_line:\t"<<t_line<<"\n";
                    cout<<"(state 3)judge plus- buff: \t"<<buff<<"\n";
                    cout<<"Operator "<<buff<<":\t"<<token[5].word[buff]<<"\n";
                    cout<<"STOP: "<<STOP<<"\n";

                    buff="";
                    break;
                }
                case 4:
                {
                    int curLine = n_line , curChar = n_char;
                    int curTchar = t_char;
                
                    foundToken = true;
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];
                    if(tem == '-'){
                        buff.push_back(tem);
                    }
                    else if(isDigit(tem)){
                        state = 2;
                        break;
                    }
                    else{
                        n_line = curLine;
                        n_char = curChar;
                        t_char = curTchar;
                    }
                    STOP = moveChar();
                    state = 0;
                    token[5].word[buff]++;
                    //log
                    cout<<"line:\t"<<n_line<<"\tt_char:\t"<<t_char<<"\tpos:\t"<<n_char<<"\tchar:\t"<<c<<"\tstate: "<<state<<"\t";
                    cout<<"\tt_line:\t"<<t_line<<"\n";
                    cout<<"(state 3)judge plus- buff: \t"<<buff<<"\n";
                    cout<<"Operator "<<buff<<":\t"<<token[5].word[buff]<<"\n";
                    cout<<"STOP: "<<STOP<<"\n";

                    buff="";
                
                    break;
                }
                case 5:
                {
                    //log
                    cout<<"state 5 (*)\t-foundtype:\t"<<foundType<<"\n";
                    
                    //int curLine = n_line , curChar = n_char;
                    //int curTchar = t_char;
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];
                    
                    if(foundType && isLetter(tem)){
                        
                        state = 1;
                        //STOP=moveChar();
                        break;
                    }
                    int count = 0;
                    string tempBuff = "*";
                    int i;
                    for(i = n_char ; i < t_char  ; i++ ){
                        bool a = (isLetter(tem) ), b = (isDigit(tem)) , c = (tem == '_');
                        cout<<"isLetter "<< a <<"\t"<<"isDigit "<< b <<"\t"<<"is_ "<<c<<"\n";
                        tem = text[n_line][i];
                        cout<<"tem??"<<tem<<".......\n";
                        if( ((isLetter(tem)) || isDigit(tem) || tem == '_' ))
                        {
                             tempBuff.push_back(tem);
                             count++;
                             cout<<"count:"<<count<<"\n";
                        }
                           
                        cout<<"tempBuff : "<<tempBuff<<"\n";
                    }
                    
                    cout<<"POINT(tempBuff)-"<<tempBuff<<":"<<token[9].word[tempBuff]<<"\n";
                    if(token[9].word[tempBuff] > 0){
                        token[9].word[tempBuff]++;
                        cout<<"POINT -"<<tempBuff<<":"<<token[9].word[tempBuff]<<"\n";
                        foundToken = true;
                        buff = "";
                        tempBuff = "";
                        cout<<"n_char:"<<n_char<<"\n";
                        n_char +=count ;
                        cout<<"n_char(aft):"<<n_char<<"\n";
                       // STOP = moveChar();
                        state = 0;
                        break;
                    }
                    //n_line = curLine;
                    //n_char = curChar;
                    //t_char = curTchar;
                    token[5].word["*"]++;
                    cout<<"* :"<<token[5].word["*"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    //STOP=moveChar(); 
                    break;
                }
                case 6:
                {
                    //log
                    cout<<"state 6 (/)-\n";
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];

                    if(tem == '/'){
                        for(int i = n_char ; i < t_char ; i++){
                            c = text[n_line][i];
                            buff.push_back(c);
                        }
                        cout<<"Comment(//): "<<buff<<"\n";
                        token[2].word[buff]++;
                        moveNextLine();
                    }
                    else if(tem == '*'){
                        c = text[n_line][n_char];
                        buff.push_back(c);
                        
                        while(!(c == '*' && text[n_line][n_char+1] == '/') && STOP<1){
                            STOP=moveChar();
                            c = text[n_line][n_char];
                            buff.push_back(c);
                        }
                        //log
                        cout<<"Comment(/**/)-out1: "<<buff<<"\n";
                        cout<<"line:\t"<<n_line<<"\tt_char:\t"<<t_char<<"\tpos:\t"<<n_char<<"\tchar:\t"<<c<<"\tstate: "<<state<<"\t";
                        cout<<"\tt_line:\t"<<t_line<<"\n";
                        STOP=moveChar();
                        c = text[n_line][n_char];
                        buff.push_back(c);
                        
                        token[2].word[buff]++;
                        cout<<"Comment(/**/): "<<buff<<"\t:\t"<<token[2].word[buff]<<"\n";
                    }
                    else{
                        token[5].word["/"]++;
                        cout<<"/ :"<<token[5].word["/"]<<"\n";
                    }
                    STOP=moveChar();
                    foundToken = true;
                    buff ="";
                    state = 0;
                    break;
                }
                case 7:
                {
                    //log
                    cout<<"state 7(%) - \n";
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];

                    if(tem == 'd' || tem == 'f' || tem == 'c')
                    {
                        buff.push_back(tem);
                        token[8].word[buff]++;
                        cout<<buff<<": "<<token[8].word[buff]<<"\n";
                        STOP = moveChar();
                    }
                    else
                    {
                        token[5].word["%"]++;
                        cout<<"% :"<<token[5].word["%"]<<"\n";
                    }
                    foundToken = true;
                    buff = "";
                    state = 0;
                    break;

                }
                case 8:
                {
                    //log
                    cout<<"state 8(^) - ";
                    token[5].word["^"]++;
                    cout<<token[5].word["^"]<<"\n";
                    STOP = moveChar();
                    buff = "";
                    state = 0;
                    foundToken = true; 
                    break;
                }
                case 9:
                {
                    if(varLine != n_line)
                        foundType = false;
                    //log
                    cout<<"state 9(&) - ";
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];
                    if(foundType && isLetter(tem)){
                        state = 1;
                        break;
                    }

                    int count = 0 , i;
                    string tempBuff = "&";
                    for(i = n_char ; i < t_char  && (isLetter(tem) || isDigit(tem) || tem == '_'); i++){
                        tem = text[n_line][i];
                        if(isLetter(tem) || isDigit(tem) || tem == '_'){
                            tempBuff.push_back(tem);
                            count++;
                            cout<<"count:"<<count<<"\n";
                        }
                        cout<<"tempBuff : "<<tempBuff<<"\n";
                    }
                    cout<<"Address(tempBuff)-"<<tempBuff<<":"<<token[10].word[tempBuff]<<"\n";
                    if(token[10].word[tempBuff] > 0){
                        token[10].word[tempBuff]++;
                        cout<<"Address-"<<tempBuff<<":"<<token[10].word[tempBuff]<<"\n";
                        foundToken = true;
                        buff = "";
                        tempBuff = "";
                        cout<<"n_char:"<<n_char<<"\n";
                        n_char +=count ;
                        cout<<"n_char(aft):"<<n_char<<"\n";
                       // STOP = moveChar();
                        state = 0;
                        break;
                    }
                    token[5].word["&"]++;
                    cout<<token[5].word["&"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    break;
                }
                case 10:
                {
                    //log
                    cout<<"state 10 (|) - ";
                    token[5].word["|"]++;
                    cout<<token[5].word["|"]<<"\n";
                    STOP = moveChar();
                    buff = "";
                    state = 0;
                    foundToken = true; 
                    break;
                }
                case 11:
                {
                    //log
                    cout<<"state 11 (=): \t";
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];

                    if(tem == '='){
                        token[6].word["=="]++;
                        cout<<"== : "<<token[6].word["=="]<<"\n";
                        STOP = moveChar();
                    }
                    else{
                        token[5].word["="]++;
                        cout<<token[5].word["="]<<"\n";
                    }
                    
                    buff = "";
                    state = 0;
                    foundToken = true; 
                    break;
                }
                case 12:
                {
                    while(foundLibrary){
                        buff.push_back(c);
                        //log
                        cout<<"(state 12) buff-library: \t"<<buff<<"\n";
                        STOP = moveChar();
                        c = text[n_line][n_char];
                        
                        if(c == '>'){
                            buff.push_back(c);
                            regex LN("<\\w+.h>");
                            if(regex_match(buff,LN)){
                                token[1].word[buff]++;
                                foundLibrary = false;
                                foundToken = true;
                                //log
                                cout<<"LN - "<<buff<<"\n";
                                STOP = moveChar(); 
                                state = 0;
                                buff = "";
                                break;
                            }
                        }
                    }
                    if(foundToken == true)
                        break;
                    //log
                    cout<<"state 12(<): ";
                    buff.push_back(c);
                    STOP = moveChar(); 
                    char tem = text[n_line][n_char];

                    if(tem == '='){
                        token[6].word["<="]++;
                        cout<<"<= : "<<token[6].word["<="]<<"\n";
                        STOP = moveChar();
                    }
                    else{
                        token[6].word["<"]++;
                        cout<<"< : "<<token[6].word["<"]<<"\n";
                    }
                    state = 0;
                    buff = "";
                    foundToken = true;
                    break;
                }
                case 13:
                {
                    cout<<"state 13(>): \n";
                    buff.push_back(c);
                    STOP = moveChar(); 
                    char tem = text[n_line][n_char];

                    if(tem == '='){
                        token[6].word[">="]++;
                        cout<<">= : "<<token[6].word[">="]<<"\n";
                        STOP = moveChar();
                    }
                    else{
                        token[6].word[">"]++;
                        cout<<"> : "<<token[6].word[">"]<<"\n";
                    }
                    state = 0;
                    buff = "";
                    foundToken = true;
                    break;
                }
                case 14:
                {
                    cout<<"state 14(!): \n";
                    buff.push_back(c);
                    STOP = moveChar(); 
                    char tem = text[n_line][n_char];
                    if(tem == '='){
                        token[6].word["!="]++;
                        cout<<"!= : "<<token[6].word["!="]<<"\n";
                        STOP = moveChar();
                        buff = "";
                        foundToken = true; 
                    }
                    else if(buff.size()>0 ){ //&& token[3].word[buff]<=0 && (n_line < t_line &&  n_char >= 0 && n_char < t_char)
                            cout<<"[Error] line "<<n_line<<" : "<<buff<<" is Unrecognized. \n";
                            foundToken = true;
                            moveNextLine();
                            buff = ""; //
                    }
                    state = 0;
                    break;
                }
                case 15:
                {
                    buff.push_back(c);
                    char tem = ' ';
                    string tempBuff ="";
                    int i;
                    for(i =  n_char ; i < t_char && tem != ')' ; i++){
                        tem = text[n_line][i];
                        tempBuff.push_back(tem);
                        cout<<"tempBuff : "<<tempBuff<<"\n";
                    }//^[(][\\s+]*[+-][\\s+]*[0-9]+[.]?[0-9]*[\\s+]*[)]$
                    regex CONST_Parentheses("[^[(][\\s+]*[+-][\\s+]*[0-9]+[.]?[0-9]*[\\s+]*[)]$]|[^[(][\\s+]*[+-][\\s+]*[0-9]*[.]?[0-9]+[\\s+]*[)]$]");
                    if(regex_match(tempBuff,CONST_Parentheses)){
                        token[4].word[tempBuff]++;
                        foundToken = true;
                        cout<<"CONST_Parentheses -"<<tempBuff<<": "<<token[4].word[tempBuff]<<"\n";
                        buff = "";
                        tempBuff = "";
                        n_char = i-1;
                        STOP = moveChar();
                        state = 0;
                        foundToken = true;
                        break;
                    }
                    token[7].word["("]++;
                    cout<<"( :"<<token[7].word["("]<<"\n";
                    STOP = moveChar();
                    buff = "";
                    foundToken = true;
                    state = 0 ; 
                    break;
                }
                case 16:
                {
                    token[7].word[")"]++;
                    cout<<") :"<<token[7].word[")"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                }
                case 17:
                {
                    token[7].word["["]++;
                    cout<<"[ :"<<token[7].word["["]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                }
                case 18:
                {
                    token[7].word["]"]++;
                    cout<<"] :"<<token[7].word["]"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                }
                case 19:
                    token[7].word["{"]++;
                    cout<<"{ :"<<token[7].word["{"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                case 20:
                    token[7].word["}"]++;
                    cout<<"} :"<<token[7].word["}"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                case 21:
                    token[11].word[","]++;
                    cout<<", :"<<token[11].word[","]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                case 22:
                    token[11].word[";"]++;
                    cout<<"; :"<<token[11].word[";"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                case 23:
                    token[11].word[":"]++;
                    cout<<": :"<<token[11].word[":"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                case 24:
                    token[11].word["#"]++;
                    cout<<"# :"<<token[11].word["#"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                case 25:
                {
                    buff.push_back(c);
                    STOP = moveChar();
                    char tem = text[n_line][n_char];
                    cout<<"state 25 : \n";
                    if(tem == 'a' || tem == 'v' || tem == '0' || tem == '\''|| tem == 'n' || tem == 't' || tem == 'r' || tem == '\\' || tem == '\'' || tem == 'b' || tem == 'f'){
                        buff.push_back(tem);
                        token[8].word[buff]++;
                        STOP = moveChar();
                        cout<<buff<<" "<<token[8].word[buff]<<"\n";
                    }
                    else if(buff.size()>0 ){ //&& token[3].word[buff]<=0 && (n_line < t_line &&  n_char >= 0 && n_char < t_char)
                        cout<<"[Error] line "<<n_line<<" : "<<buff<<" is Unrecognized. \n";
                        moveNextLine();
                    }
                    foundToken = true;
                    buff = ""; //
                    state =0;
                    break;
                }
                case 26:
                    cout<<"state 26 : \n";
                    token[11].word["'"]++;
                    cout<<"' :"<<token[11].word["'"]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                case 27:
                {
                    if(foundPrintf){
                        printfCount++;
                        if(printfCount==2)
                            foundPrintf = false;
                    }
                    cout<<"state 27(\") : \n";
                    token[11].word["\""]++;
                    cout<<"\" :"<<token[11].word["\""]<<"\n";
                    state = 0;
                    buff = "";
                    foundToken = true;
                    STOP = moveChar(); 
                    break;
                }
                case 28:
                {
                    int curLine = n_line , curChar = n_char;
                    int curTchar = t_char;

                    buff.push_back(c);
                    cout<<"<state 28> BUFF: "<<buff<<"\n";
                    STOP = moveChar();
                    char tem = text[n_line][n_char];
                    if(isDigit(tem)|| (tem ==' ' && pointCount <= 1))
                    {
                        state = 2;
                        break;
                    }
                    else{ //if(pointCount>1 && buff.size()>0){
                        
                        cout<<"[Error] line "<<n_line<<" : "<<buff<<" is Unrecognized. \n";
                        foundToken = true;
                        n_line = curLine;
                        n_char = curChar;
                        t_char = curTchar;
                        moveNextLine();
                        buff = ""; //
                        state = 0 ;
                        break;
                    }
                }
                case 29:
                    cout<<"space \n";
                    STOP = moveChar(); 
                    foundToken = true;
                    state = 0;
                    break;
                case 30:
                {
                    if(varLine != n_line)
                        foundPrintf = false;
                    //log 
                    cout<<"state 30: ";
                    buff.push_back(c);
                    char tem = '@';
                    //string tempBuff ="";
                    if(varLine != n_line)
                        foundPrintf = false;
                    if(foundPrintf){
                        while((tem != ' ' && tem !='"' && tem !=',' && tem != '%' && tem != ')') && STOP <1)
                        {
                            STOP = moveChar();
                            tem = text[n_line][n_char];
                            buff.push_back(tem);
                            if(tem =='"')
                                break;
                        }
                        token[12].word[buff]++;
                        cout<<buff<<" :"<<token[12].word[buff]<<"\n";
                        buff = "";
                        foundToken = true;
                        
                        if(tem == '"')
                            foundPrintf = false;
                    }
                    state =0;
                    break;
                }
            }
        }
         if(STOP == 1) break;
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

    char filename[] = "scanner_";
    strcat(filename,argv[1]);
    
    bool correct = s.outputFile(filename);
    if(correct) cout<<"The file output.\n";
    else 
        cout<<"[Error] It can't output file\n";

    //s.printText();
    return 0;
}
