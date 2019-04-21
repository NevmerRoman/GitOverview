#include <iostream>
#include <string>

using namespace std;

string& delete_duplicates(string& str){
    int t = str.size() - 1;
    for(int i = 0; i < t; i++){
        if(str[i] == str[i+1]){
            str.erase(i, 1);
            t--;
            i--;
        }
    }
    return str;
}


int main(){
    string str = "HHHello   Worllldlll!!abbbaaaac";
    cout << str << endl;
    str = delete_duplicates(str);
    cout << str << endl;
    return 0;
}
