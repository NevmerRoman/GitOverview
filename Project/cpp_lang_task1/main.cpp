#include <iostream>
#include <iomanip>
#include "stdio.h"
#include "cpp_lang_task1.h"
#include <fstream>

using namespace student;
using std::cout;
using std::rand;
using std::srand;
using std::setw;
using std::ofstream;

string::~string(){
    delete [] _data;
    _size = 0;
}

string::string (){
    _data = nullptr;
    _size = 0;
}

string::string (unsigned int count, char ch){
    _size = count;
    _data = new char[_size+1];
    for (unsigned int i = 0; i < _size; i++){
        _data[i] = ch;
    }
    _data[_size]  = '\0';
}

string::string (const char* other, unsigned int count){
    unsigned int length = strlen(other);
    _size = count;
    _data = new char[_size+1];
    unsigned int lim = _size;
    if (length < _size){
        lim = length;
        for(unsigned int i = length; i < _size; i++){
            _data[i] = '\0';
        }
    }
    for (unsigned int i = 0; i < lim; ++i){
        _data[i] = other[i];
    }
    _data[_size]  = '\0';
}

string::string (const char* other){
    _size = strlen(other);
    _data = new char[_size+1];
    for (unsigned int i = 0; i < _size; ++i){
        _data[i] = other[i];
    }
    _data[_size]  = '\0';
}

string::string (const string& other){
    _size = other._size;
    _data = new char[_size+1];
    for (unsigned int i = 0; i < _size; ++i){
        _data[i] = other._data[i];
    }
    _data[_size]  = '\0';
}

string::string (string&& other)
    :_data(other._data)
    ,_size(other._size) {
    other._data = nullptr;
    other._size = 0;
}

string& string::operator= (const string& other){
    delete [] _data;
    _size = other._size;
    _data = new char[_size+1];
    for (unsigned int i = 0; i < _size; ++i){
        _data[i] = other._data[i];
    }
    _data[_size]  = '\0';
    return *this;
}

string& string::operator= (string&& other){
    delete [] _data;
    _data = other._data;
    _size = other._size;
    other._data = nullptr;
    other._size = 0;
    return *this;
}

string& string::operator= (const char* other){
    delete [] _data;
    _size = strlen(other);
    _data = new char[_size+1];
    for (unsigned int i = 0; i < _size; ++i){
        _data[i] = other[i];
    }
    _data[_size]  = '\0';
    return *this;
}

char& string::operator[](unsigned int pos){
    return _data[pos];
}

const char& string::operator[](unsigned int pos) const{
    return _data[pos];
}

const char* string::data () const{
    return _data;
}

bool string::empty (){
    if (_data == nullptr){
        return true;
    }
    for(unsigned int i = 0; i < _size; i++){
        if (_data[i] != '\0') return false;
    }
    return true;
}

unsigned int string::size () const{
    return _size;
}

void string::clear(){
    for(unsigned int i = 0; i < _size; i++){
        _data[i] = '\0';
    }
}

void string::push_back (char ch){
    unsigned int i = 0;
    while(_data[i]) i++;
    if (i < _size){
        _data[i] = ch;
    }
    else{
        _data = (char*) realloc(_data, _size+2);
        _data[_size] = ch;
        _size++;
        _data[_size] = '\0';
    }
}

void string::pop_back (){
    _size--;
    _data = (char*) realloc(_data, _size+1);
    _data[_size] = '\0';
}

string& string::append (const char* other, unsigned int count){
    unsigned int i = 0;
    unsigned int length = 0;
    if (strlen(other) < count) count = strlen(other);
    while (_data[i]) i++;
    if ((i < _size) && ((_size - i) <= count)){
        for(unsigned int j = i; ((j < _size) && (count > 0)); j++){
            _data[j] = other[j - i];
            count--;
        }
    }
    if (count > 0){
        length = _size + count;
        _data = (char*) realloc(_data, length+1);
        for(unsigned int j = _size; ((j < length) || (strlen(other) < count)); j++){
            _data[j] = other[j - i];
        }
    }
    _size = length;
    _data[_size] = '\0';
    return *this;
}

string& string::append (const string& other){
    unsigned int i = 0;
    unsigned int count = other._size;
    while (_data[i]) i++;
    if ((i < _size) && ((_size - i) <= count)){
        for(unsigned int j = i; ((j < _size) && (count > 0)); j++){
            _data[j] = other[j - i];
            count--;
        }
    }
    if (count > 0){
        unsigned int length = _size + count;
        _data = (char*) realloc(_data, length+1);
        for(unsigned int j = _size; j < length; j++){
            _data[j] = other[j - i];
        }
        _size = length;
    }
    _data[_size] = '\0';
    return *this;
}

string& string::append (unsigned int count, const char& ch){
    unsigned int i = 0;
    while (_data[i]) i++;
    if ((i < _size) && ((_size - i) <= count)){
        for(unsigned int j = i; ((j < _size) && (count > 0)); j++){
            _data[j] = ch;
            count--;
        }
    }
    if (count > 0){
        unsigned int length = _size + count;
        _data = (char*) realloc(_data, length+1);
        for(i = _size; i < length; i++){
            _data[i] = ch;
        }
        _size = length;
    }
    _data[_size] = '\0';
    return *this;
}

string string::substr(unsigned int pos, unsigned int count){
    try{
        if (pos > _size){
            throw 123;
        }
    }
    catch(int th){
        cout << "ERROR " << th << " out_of_range\n";
    }
    unsigned int length;
    if((count == npos)||(count > (_size - pos))){
        length = _size - pos;
    }
    else{
        length = count;
    }
    string str(length, '\0');
    for(unsigned int i = pos; i < (pos + length); i++){
        str[i - pos] = _data[i];
    }
    str._data[length] = '\0';
    return str;
}

unsigned int string::strlen(const char* str){
    unsigned int len = 0;
    while (str[len]) len++;
    return len;
}

void string::print(){
    for(unsigned int i = 0; i < _size; i++){
        cout << _data[i];
    }
    cout << '\n';
}

void test_string(){
    cout << "\n     TEST STRING\n\n";
    cout << "     TEST1 constructor\n";
        string str1;

        string str2(5, 'f');
        str2.print();
        cout << "Size str2(5, \'f\') = " << str2.size() << '\n';

        string str3("Hello", 10);
        str3.print();
        cout << "Size str3(\"Hello\", 10) = " << str3.size() << '\n';

        string str4("Suffering");
        str4.print();
        cout << "Size str4(\"Suffering\") = " << str4.size() << '\n';

        string str5(str2);
        str5.print();
        cout << "Size str5(str2) = " << str5.size() << '\n';

        string str6(std::move(str3));
        str6.print();
        cout << "Size str6(std::move(str3) = " << str6.size() << '\n';

    cout << "\n     TEST2 operator = and operator []\nstr1 = ";
        str4.print();
        cout << "size str1 = " << str4.size() << "\nstr2 = str1\nstr2 = ";
        str1 = str4;
        str1.print();
        cout << "size str2 = " << str1.size() << "\n\n";

        cout << "char* ch = Hello World!\nstr2 = char* ch\nstr2 = ";
        str1 = "Hello World!";
        str1.print();
        cout << "size str2 = " << str1.size() << "\n\n";

        cout << "str1 = std::move(str2), str2 = \"Die\"\nstr1 = ";
        str2 = "Die";
        str1 = std::move(str2);
        str1.print();
        cout << "size str1 = " << str1.size() << "\n\n";

        str1 = "I want to see you cry";
        cout << "str = ";
        str1.print();
        cout << "str[7] = " << str1[7] << "\n\n";

    cout << "     TEST3 empty, clear, size, push_back, pop_back, append, substr\n";
        string str7;
        string str8(10, '\0');
        str3 = "Hello";
        cout << "string str1; \nstr1.empty() = " << str7.empty() << "\nstr2(10, \" \")\nstr2.empty() = " << str8.empty() << "\nstr3 = \"Hello\"\nstr3.empty() = " << str3.empty() << '\n';
        cout << "str3.size() = " << str3.size() << "\nstr3.clear()\n";
        str3.clear();
        cout << "str3.empty() = " << str3.empty() << "\nstr3.size() = " << str3.size() << "\n\n";

        cout << "str = ";
        str1.print();
        str1.push_back('!');
        cout << "str.push_back(\'!\')\nstr = ";
        str1.print();
        str1.pop_back();
        cout << "str.pop_back()\nstr = ";
        str1.print();

        str1 = "Hello";
        str2 = " World!";
        cout << "\nstr1 = ";
        str1.print();
        cout << "str1.size() = " << str1.size() << "\nstr2 = ";
        str2.print();
        cout << "str2.size() = " << str2.size() << "\nstr1.append(str2) = ";
        str1.append(str2);
        str1.print();
        cout << "str1.size = " << str1.size() << '\n';
        str1 = "Hello";
        cout << "str1 = Hello\nstr1.append(\" World!\", 10) = ";
        str1.append(" World!", 10);
        str1.print();
        cout << "str1.size() = " << str1.size() << '\n';
        cout << "str1 = Hello World!   \nstr1.append(8, \'!\') = ";
        str1.append(8, '!');
        str1.print();
        cout << "str1.size() = " << str1.size() << "\n\n";

        cout << "str1 = I need your help!\nstr2 = str1.substr(12, 4)\nstr2 = ";
        str1 = "I need your help";
        str2 = str1.substr(12, 4);
        str2.print();
        cout << "str2.size() = " << str2.size() << '\n';
}



template <typename T>
vector<T>::~vector(){
    delete [] _data;
    _size = 0;
}

template <typename T>
vector<T>::vector(){
    _data = nullptr;
    _size = 0;
}

template <typename T>
vector<T>::vector(const vector& other){
    _data = (T*) malloc(other._size * sizeof(T));
    _size = other._size;
    for(unsigned int i = 0; i < _size; i++) _data[i] = other._data[i];
}

template <typename T>
vector<T>::vector(vector&& other)
  :_data(other._data)
  ,_size(other._size) {
  other._data = nullptr;
  other._size = 0;
}

template <typename T>
vector<T>::vector(unsigned int count, const T& val){
    _data = (T*) malloc(count * sizeof(T));
    _size = count;
    for (unsigned int i = 0; i < count; i++) _data[i] = val;
}

template <typename T>
vector<T>::vector(int count){
    _data = (T*) malloc(count * sizeof(T));
    _size = count;
}

template <typename T>
T& vector<T>::operator[] (unsigned int pos){
    return _data[pos];
}

template <typename T>
const T&  vector<T>::operator[] (unsigned int pos) const{
    return _data[pos];
}

template <typename T>
T* vector<T>::data(){
    return _data;
}

template <typename T>
const T* vector<T>::data() const{
    return _data;
}

template <typename T>
bool vector<T>::empty() const{
    if (_data == nullptr) return true;
    unsigned int i = 0;
    T val = T();
    while(_data[i] == val){
        i++;
    }
    if (i >= _size){
        return true;
    }
    return false;
}

template <typename T>
void vector<T>::clear(){
    T val = T();
    for(unsigned int i = 0; i < _size; i++)_data[i] = val;
}

template <typename T>
void vector<T>::push_back(const T& value){
    _data = (T*) realloc(_data, ((_size + 1) * sizeof(T)));
    _data[_size] = value;
    _size++;
}

template <typename T>
void vector<T>::push_back(T&& value){
    _data = (T*) realloc(_data, ((_size) * sizeof(T)));
    _data[_size] = value;
    _size++;
}

template <typename T>
void vector<T>::pop_back(){
    _size--;
    _data = (T*) realloc(_data, (_size * sizeof(T)));
}

template <typename T>
void vector<T>::insert( unsigned int pos, unsigned int count, const T& value){
    unsigned int length = _size + count;
    _data = (T*) realloc(_data, length * sizeof(T));
    for(unsigned int i = 0; i < count; i++){
        _data[_size + i] = _data[pos + i];
        _data[pos + i] = value;
    }
    _size = length;
}

template <typename T>
void vector<T>::print(){
    for(unsigned int i = 0; i < _size; i++) cout << _data[i];
    cout << '\n';
}

template <typename T>
unsigned int vector<T>::size(){
    return _size;
}

void test_vector(){
    cout << "\n     TEST_VECTOR\n";

    cout << "\n     TEST1 constructor\n";
        vector<int> vecin1;

        vector<int> vecin2(10);
        cout << "vecin2(10) = ";
        vecin2.print();
        cout << "size vecin2 = " << vecin2.size() << "\n\n";

        vector<int> vecin3(5, 9);
        cout << "vecin3(5, 9) = ";
        vecin3.print();
        cout << "size vecin3 = " << vecin3.size() << "\n\n";

        vector<int> vecin4(vecin3);
        cout << "vecin4(vecin3) = ";
        vecin4.print();
        cout << "size vecin4 = " << vecin4.size() << "\n\n";

        vector<int> vecin5(std::move(vecin3));
        cout << "vecin5(std::move(vecin3)) = ";
        vecin5.print();
        cout << "size vecin5 = " << vecin5.size() << "\n\n";

        vector<char> vecch1;

        vector<char> vecch2(8);
        cout << "vecch(8) = ";
        vecch2.print();
        cout << "size vecch2 = " << vecch2.size() << "\n\n";

        vector<char> vecch3(10, 'O');
        cout << "vecch3(10, \'O\') = ";
        vecch3.print();
        cout << "size vecch3 = " << vecch3.size() << "\n\n";

        vector<char> vecch4(vecch3);
        cout << "vecch4(vecch3) = ";
        vecch4.print();
        cout << "size vecch4 = " << vecch4.size() << "\n\n";

        vector<char> vecch5(std::move(vecch3));
        cout << "vecch5(std::move(vecch3)) = ";
        vecch5.print();
        cout << "size vecch5 = " << vecch5.size() << "\n\n";

    cout << "     TEST2 operator []\nvecin5 = ";
        vecin5.print();
        cout << "vecin5[3] = " << vecin5[3] << "\n\nvecch5 = ";

        vecch5.print();
        cout << "vecch5[2] = " << vecch5[2] << "\n\n";

    cout << "     TEST3 empty, clear, push_back, pop_back, insert\n";
        cout << "vecin4 = ";
        vecin4.print();
        cout << "vecin4.empty() = " << vecin4.empty() << "\nvecin4.clear()\n";
        vecin4.clear();
        cout << "vecin4.empty() = " << vecin4.empty() << "\n\n";
        cout << "vecch4 = ";
        vecch4.print();
        cout << "vecch4.empty() = " << vecch4.empty() << "\nvecch4.clear()\n";
        vecch4.clear();
        cout << "vecch4.empty() = " << vecch4.empty() << "\n\n";

        cout << "vecin5 = ";
        vecin5.print();
        cout << "vecin5 size = " << vecin5.size() << '\n';
        cout << "vecin5.push_back(4)\n";
        vecin5.push_back(4);
        cout << "vecin5 = ";
        vecin5.print();
        cout << "vecin5 size = " << vecin5.size() << "\nvecin5.pop_back()\nvecin5 = ";
        vecin5.pop_back();
        vecin5.print();
        cout << "vecin5 size = " << vecin5.size() << "\n\n";

        cout << "vecch5 = ";
        vecch5.print();
        cout << "vecch5 size = " << vecch5.size() << '\n';
        cout << "vecch5.push_back(\'M\')\n";
        vecch5.push_back('M');
        cout << "vecch5 = ";
        vecch5.print();
        cout << "vecch5 size = " << vecch5.size() << "\nvecch5.pop_back()\nvecch5 = ";
        vecch5.pop_back();
        vecch5.print();
        cout << "vecch5 size = " << vecch5.size() << "\n\n";

        cout << "vecin5.insert(2, 6, 6) = ";
        vecin5.insert(2, 6, 6);
        vecin5.print();
        cout << "vecin5 size = " << vecin5.size() << '\n';

        cout << "vecch5.insert(4, 8, \'M\') = ";
        vecch5.insert(4, 8, 'M');
        vecch5.print();
        cout << "vecch5 size = " << vecch5.size() << '\n';
}



void print_number_table (short col, short row){
    srand(time(0));
    int mas[row][col];
    ofstream fout;
    fout.open("/home/student/Project/cpp_lang_task1/table.log");
    cout << ' ';
    fout << ' ';
    for(int j = 0; j < col - 1; j++){
        cout << "******";
        fout << "******";
    }
    cout << "*****\n";
    fout << "*****\n";
    for(int i = 0; i < row - 1; i++){
        for(int j = 0; j < col; j++){
            mas[i][j] = rand() % 1000;
            cout << '|' << setw(4) << mas[i][j] << ' ';
            fout << '|' << setw(4) << mas[i][j] << ' ';
        }
        cout << '|' << '\n' << '|';
        fout << '|' << '\n' << '|';
        for (int j = 0; j < col - 1; j++){
            cout << "-----+";
            fout << "-----+";
        }
        cout << "-----|" << '\n';
        fout << "-----|" << '\n';
    }
    for(int j = 0; j < col; j++){
        mas[row - 1][j] = rand() % 1000;
        cout << '|' << setw(4) << mas[row - 1][j] << ' ';
        fout << '|' << setw(4) << mas[row - 1][j] << ' ';
    }
    cout << '|' << "\n ";
    fout << '|' << "\n ";
    for(int j = 0; j < col - 1; j++){
        cout << "******";
        fout << "******";
    }
    cout << "*****\n";
    fout << "*****\n";
    fout.close();
}

int main(){
    srand(time(0));
    print_number_table(rand() % 20 + 1, rand() % 20 + 1);
    test_string();
    test_vector();
    return 0;
}
