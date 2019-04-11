#include <iostream>

using std::cout;

class Container{
    protected:
        char* _data;
        unsigned int _size;
    public:
        ~Container(){
            delete [] _data;
            _size = 0;
            cout << "dist";
        }

        Container(){
            _data = nullptr;
            _size = 0;
            cout << "const\n";
        }

        char* data(){
            return _data;
        }

        unsigned int size(){
            return _size;
        }

        unsigned int max_size(){
            return _size;
        }

        virtual bool empty() = 0;
        virtual void clear() = 0;
};

class AbstractContainer : public Container{

};

class map : public AbstractContainer{

};

class set : public AbstractContainer{

};

class NonAbstractContainer : public Container{
    public:
        NonAbstractContainer() : Container(){}
        virtual void push_back(const char& value) = 0;
        virtual void pop_back() = 0;
};

class list : public NonAbstractContainer{

};

class vector : public NonAbstractContainer{
    public:
        vector() : NonAbstractContainer(){}

        bool empty() const{
            if (_data == nullptr) return true;
            unsigned int i = 0;
            while(_data[i] == '\0'){
                i++;
            }
            if (i >= _size){
                return true;
            }
            return false;
        }

        void clear(){
            for(unsigned int i = 0; i < _size; i++)_data[i] = '\0';
        }

        void push_back(const char& value){
            _data = (char*) realloc(_data, ((_size + 1) * sizeof(char)));
            _data[_size] = value;
            _size++;
        }

        void push_back(char&& value){
            _data = (char*) realloc(_data, ((_size) * sizeof(char)));
            _data[_size] = value;
            _size++;
        }

        void pop_back(){
            _size--;
            _data = (char*) realloc(_data, (_size * sizeof(char)));
        }
};

int main(){
    vector A;
    return 0;
}
