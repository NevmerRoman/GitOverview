#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::binary_search;
using std::advance;
using std::distance;

bool bin_search(int value, vector<int>& v){

    vector<int>::iterator point = v.begin();
    vector<int>::iterator a = v.begin();
    vector<int>::iterator b = v.end();

    while (distance(a, b) > 1){
        point = a;
        advance(point, distance(a, b)/2);
        if (*a > *point) b = point;
        else if (*point > *b) a = point;
    }

    if (*point > *b) point = b;

    if (binary_search(v.begin(), point, value) || binary_search(point, v.end(), value)) return true;
    else return false;
}

void print(vector<int>& v){
    for(const int& i : v){
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> v1 = {10,11,12,13,14,15,16,0,1,2,3,4,5,6,7,8,9};
    vector<int> v2 = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    vector<int> v3 = {16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    vector<int> v4 = {4,5,6,7,8,9,10,11,12,13,14,15,16,0,1,2,3};

    cout << "vector 1 = ";
    print(v1);
    cout << "vector 2 = ";
    print(v2);
    cout << "vector 3 = ";
    print(v3);
    cout << "vector 4 = ";
    print(v4);

    cout << "search 20 in vector 1 = " << bin_search(20, v1) << endl;
    cout << "search 15 in vector 2 = " << bin_search(15, v2) << endl;
    cout << "search 30 in vector 3 = " << bin_search(30, v3) << endl;
    cout << "search 0 in vector 4 = " << bin_search(0, v4) << endl;
    return 0;
}
