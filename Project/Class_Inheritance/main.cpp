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
            cout << "distructor\n";
        }

        Container(){
            _data = nullptr;
            _size = 0;
            cout << "constructor\n";
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

        virtual bool empty() const = 0;
        virtual void clear() = 0;
};

class AssociativeContainer : public Container{
    protected:
        unsigned int key;
    public:
        AssociativeContainer() : Container(){}

        virtual void insert() = 0;
        virtual void erase() = 0;
        virtual void swap() = 0;
};

class map : public AssociativeContainer{
    public:
        map() : AssociativeContainer(){cout << "map\n";}

        bool empty() const{return false;}

        void clear(){}

        void insert(){}

        void erase(){}

        void swap(){}
};

class set : public AssociativeContainer{
    public:
        set() : AssociativeContainer(){cout << "set\n";}

        bool empty() const{return false;}

        void clear(){}

        void insert(){}

        void erase(){}

        void swap(){}
};

class NonAssociativeContainer : public Container{
    public:
        NonAssociativeContainer() : Container(){}
        virtual void push_back(const char& value) = 0;
        virtual void push_back(char&& value) = 0;
        virtual void pop_back() = 0;
};

class list : public NonAssociativeContainer{
    public:
        list() : NonAssociativeContainer(){cout << "list\n";}
        bool empty() const{return false;}

        void clear(){}

        void push_back(const char& value){}

        void push_back(char&& value){}

        void pop_back(){}

        void push_front( const char& value ){}

        void push_front( char&& value ){}

        void pop_front(){}
};

class vector : public NonAssociativeContainer{
    public:
        vector() : NonAssociativeContainer(){cout << "vector\n";}

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
    list B;
    map C;
    set D;
    return 0;
}
