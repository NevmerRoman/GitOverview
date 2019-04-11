#include <iostream>

using std::cout;

template <typename T>
class Container{
    protected:
        T* _data;
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

        T* data(){
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

template <typename T>
class AbstractContainer : public Container<T>{

};

template <typename T>
class map : public AbstractContainer<T>{

};

template <typename T>
class set : public AbstractContainer<T>{

};

template <typename T>
class NonAbstractContainer : public Container<T>{
    public:
        NonAbstractContainer() : Container<T>(){}
        virtual void push_back(const T& value) = 0;
        virtual void pop_back() = 0;
};

template <typename T>
class list : public NonAbstractContainer<T>{

};

template <typename T>
class vector : public NonAbstractContainer<T>{
    public:
        vector() : NonAbstractContainer<T>(){}

        bool empty() const{
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

        void clear(){
            T val = T();
            for(unsigned int i = 0; i < _size; i++)_data[i] = val;
        }

        void push_back(const T& value){
            _data = (T*) realloc(_data, ((_size + 1) * sizeof(T)));
            _data[_size] = value;
            _size++;
        }

        void push_back(T&& value){
            _data = (T*) realloc(_data, ((_size) * sizeof(T)));
            _data[_size] = value;
            _size++;
        }

        void pop_back(){
            _size--;
            _data = (T*) realloc(_data, (_size * sizeof(T)));
        }
};

int main(){
    vector<int> A;
    return 0;
}
