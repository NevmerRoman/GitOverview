#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using std::vector;
using std::list;
using std::cout;
using std::endl;
using std::binary_search;
using std::sort;

bool MyCompare(const int i1, const int i2){
    return i1 > i2;
}

int main(){
    vector<int> v = {0,1,3,2,4,5,7,6,8,9};
    list<int> l = {0,1,3,2,4,5,7,6,8,9};

    l.sort();
    /*sort(v.begin(), v.end(), [](const int i1, const int i2){
                                return i1 > i2;});*/

    sort(v.begin(), v.end(), MyCompare);

    cout << "list:" << endl;
    for(const int& i : l){
        cout << i << " ";
    }
    cout << endl;

    cout << "vector:" << endl;
    for(const int& i : v){
        cout << i << " ";
    }
    cout << endl;

    cout << binary_search(v.begin(), v.end(), 4) << endl;

    return 0;
}
