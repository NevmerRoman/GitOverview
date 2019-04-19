#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Base{
public:
    Base() : number(new int[INT32_MAX]),
             name(new char[INT32_MAX])
    {
        cout << "Base\n";
        throw "this exception";
        cout << "next Base()\n";
    }

    ~Base(){
        cout << "~Base\n";
        delete number;
        delete name;
    }

protected:

private:
    int* number;
    char* name;
};

/*bool my_compare(const int val1, const int val2){
    return val1 < val2;
}

struct MyCompare{
    bool operator()(const int val1, const int val2){
        return val1 < val2;
    }
} my_compare_s;*/

int main(){
    try{
        Base b;
    }catch(const char* s){
        cout << s << endl;
    }catch(const std::bad_alloc& s){
        cout << s.what() << endl;
    }

    //vector<int> v = {10, 5, 7, 9, 0, 1, 2, -4, 0, 3, 9, -8};
    //sort(v.begin(), v.end(),my_compare_s);
    return 0;
}
