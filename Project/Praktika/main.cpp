#include <iostream>
#include <map>
#include <string>
#include <set>
#include <unordered_map>  // без сортировки
#include <unordered_set>  // без сортировки

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::unordered_map;
using std::unordered_set;

class Base;
bool operator < (const Base& left, const Base& right);

class Base{
    int i;
    double d;
    string s;
    public:
        inline const int& get_i() const{
            return i;
        }

        inline void set_i(int _i){
            i = _i;
        }

        //friend bool operator < (const Base& left, const Base& right);
};

bool operator < (const Base& left, const Base& right){
    return left.get_i() < right.get_i();
}

int main()
{
    map<string, int> m;

    set<int> s;

    set<Base> s_base;

    s.insert(1);
    s.insert(2);
    s.insert(-100);
    s.insert(1);

    s.count(-100); //поиск по ключу

    for(const int& i : s){
        cout << i << endl;
    }
    cout << endl;

    m["Roman"] = 13;
    m["Roman"] = 21;
    m["Vika"] = 210;
    m["Sasha"] = 16;
    m["Oleg"] = 8;

    cout << "here " << m["Roman"] << endl << endl;

    m.insert({"Igor", 50});
    for(const pair<string, int>& i : m){
        cout << i.first << " " << i.second << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
