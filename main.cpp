#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

static void clear_screen();

unordered_set<string>PlainTypes{
    "string", "int", "float", "double", "bool",
    "unsigned long long", "long long", "short",
    "unsigned short", "unsigned int" , "char",
    "unsigned char"
};
unordered_set<string>ComplexTypes{
    "vector", "list", "set", "array"
};

char Validate_DataType(string data){
    if(PlainTypes.find(data) != PlainTypes.end() )
        return 1;
    if(ComplexTypes.find(data) != ComplexTypes.end() )
        return 2;
    return 0;
}

string datatype(string data){
    if(data == ""){
        cout << "Enter the nested type: \n";
        cin >> data;
    }
    char c = Validate_DataType(data);
    while(c == 0){
        cout << "Unsupported data type: Try Again :\n";
        cin >> data;
        c = Validate_DataType(data);
    }
    if(c == 1) return data;

    if(c == 2){
        string nested_type = datatype("");
        return data + '<' + nested_type + '>' ;
    }
}

bool isAlpha(char c){
    if(isupper(c) || islower(c) || c == '_')
        return true;
    return false;
}
string s(int len){
    string str = "";
    for(int i = 0; i<len ; ++i)
        str += " ";
    return str;
}

bool validVarName(string data){
    if(data.size() == 0)return false;
    if(!isAlpha(data[0])) return false;
    return true;
}

string createConstructor(string className,
vector<pair<string,string>>&vars){
    string str = s(4) + className;
    str += '(';
    for(auto var: vars){
        str += var.first + " _" + var.second + ", ";
    }
    str.pop_back();
    str.pop_back();
    str += "){\n";
    for(auto var: vars){
        str += s(8) + var.second + " = _" + var.second + ";\n";
    }
    str += s(4) + "}\n\n";
    return str;
}

void deCapitalizeFirstLetter(string &s){
    if(islower(s[0]))
        return;
    char c = s[0] + 32;
    string str = "";
    str += c;
    str += s.substr(1);
    s = str;
}
string capitalizeFirstLetter(string s){
    if(isupper(s[0]))
        return s;
    char c = s[0] - 32;
    string str = "";
    str += c;
    str += s.substr(1);
    return str;
}

string createSetter(string type,string name){
    string str = s(4) + "void set";
    str += capitalizeFirstLetter(name) + '(';
    str += type + " _" + name + "){\n" ;
    str += s(8) + name + " = _" + name + ";\n";
    str += s(4) + "}\n\n";
    return str;
}
string createGetter(string type,string name){
    string str = s(4) + type + " get";
    str += capitalizeFirstLetter(name);
    str += "(){\n";
    str += s(8) + "return " + name + ";\n";
    str += s(4) + "}\n\n";
    return str;
}

int main()
{
    string ClassName;
    string Type, Name;
    vector<pair<string,string> >vars;

    cout << "Enter ClassName: \n";
    cin >> ClassName;

    int i = 1;
    do{
        cout << "\nEnter zero to break:\n";
        cout << "Enter Type of variable " << i++  << " :\n";
        cin >> Type;
        if(Type == "0")break;
        Type = datatype(Type);

        cout << "Enter the name of variable:\n";
        cin >> Name;
        while(!validVarName(Name)){
            cout << "Invalid Variable name. Try Again:\n";
            cin >> Name;
        }
        deCapitalizeFirstLetter(Name);

        vars.push_back(make_pair(Type,Name));
        clear_screen();
    }while(1);
    string filename;
    cout << "\n\nEnter Filename for class creation:\n";
    cin >> filename;
    filename += ".cpp";

    ofstream code;
    code.open(filename, ios::out);
    if(code.is_open() == false){
        cout << "File not open. Try again: \n";
        cin >> filename;
        code.open(filename+".cpp", ios::out);
    }
    code << "#include <iostream>\n\n";
    code << "using namespace std;\n\n";
    code << "class " << ClassName << '\n';
    code << "{\n" << "private:\n";
    for(auto var: vars){
        code << s(4) << var.first << ' ';
        code << var.second + ";\n";
    }
    code << "public:\n";
    code << createConstructor(ClassName,vars);
    for(auto var: vars){
        string s1 = var.first;
        string s2 = var.second;
        code << createSetter(s1,s2);
        code << createGetter(s1,s2);
    }
    code << "};\n\n";
    code << "int main()\n";
    code << "{\n" + s(4) + "return 0;\n" + "}\n";
}

#ifdef __unix__
    static void clear_screen() {
        system("clear");
    }
#else
    static void clear_screen() {
        system("CLS");
    }
#endif

