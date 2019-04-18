#include <iostream>

using namespace std;

typedef enum {Black, Red} colorsNode;

template <typename T>
struct Node{
    Node *left;
    Node *right;
    Node *parent;
    T value;
    colorsNode color;
};

template <typename T>
class RedBlackTree{
private:
    Node<T> *RBT_root;
    Node<T> *NIL;
    unsigned int countNodes;

    Node<T> *NewNode(T val){
        countNodes++;
        Node<T> *node = new Node<T>;
        node->value = val;
        node->left = 0;
        node->right = 0;
        node->parent = 0;
        node->color = Red;
        return node;
    }

    void Clear(Node<T>* node){
        if(!node) return;
        if(node->left) Clear(node->left);
        if(node->right) Clear(node->right);
        delete node;
    }

    void Show(Node<T>* node, int high, char dir)//high - высота, dir - значок
    {
        int n;
        if(!node) return;
        for(n=0; n < high; n++) putchar(' ');
        if(node->color == Red)
            cout << dir << '[' << node->value << ']' << " (Red)" << endl;
        else
            cout << dir << '[' << node->value << ']' << " (Black)" << endl;
        Show(node->left, high + 2, '-');
        Show(node->right, high + 2, '+');
    }

    Node<T> *RotateLeft(Node<T> *X){
        Node<T> *Y = X->right;
        X->right = Y->left;
        if (Y->left) Y->left->parent = X;
        Y->parent = X->parent;
        if (X->parent){
            if (X->parent->left == X) X->parent->left = Y;
            else X->parent->right = Y;
        }
        Y->left = X;
        X->parent = Y;
        if(X == RBT_root) RBT_root = Y;
        return Y;
    }

    Node<T> *RotateRight(Node<T> *X){
        Node<T> *Y = X->left;
        X->left = Y->right;
        if (Y->right) Y->right->parent = X;
        Y->parent = X->parent;
        if (X->parent){
            if (X->parent->right == X) X->parent->right = Y;
            else X->parent->left = Y;
        }
        Y->right = X;
        X->parent = Y;
        if(X == RBT_root) RBT_root = Y;
        return Y;
    }

    void BalanceInsert(Node<T> *node){
        Node<T> *par = node->parent;
        while((node != RBT_root) && (par->color == Red)){
            int flag = 0;
            if(par->parent->left && par->parent->right && (par->parent->left->color == Red) && (par->parent->right->color == Red)){
                par->parent->left->color = Black;
                par->parent->right->color = Black;
                par->parent->color = Red;
                node = par->parent;
                par = par->parent->parent;
            }
            if((node == RBT_root) || (par == RBT_root)) return;
            if(!(par->parent->left) || (par->parent->left->color == Black)){  //если par - правый сын своего отца, а левый сын черный
                if(node == par->left) par = RotateRight(par);
                par->color = Black;
                par->parent->color = Red;
                RotateLeft(par->parent);
                flag = 1;
            }
            if(!flag && (!(par->parent->right) || (par->parent->right->color == Black))){ //если par - левый сын своего отца, а правый сын черный
                if(node == par->right) par = RotateLeft(par);
                par->color = Black;
                par->parent->color = Red;
                par = RotateRight(par->parent);
            }
        }
    }

    void BalanceRemove(Node<T> *node, char seid_son){
        Node<T> *X = node->right;
        if(!X){
            X->value = T();
            X->color = Black;
            X->parent = node->parent;
            if(seid_son == 'L') node->parent->left = X;
            else node->parent->right = X;
        }

        Node<T> *par = X->parent;
        while((X != RBT_root) && (X->color == Black)){

            if(X == par->left){

                if((par->right) && (par->right->color == Red)){
                    par = RotateLeft(par);
                    par->color = Black;
                    par->left->color = Red;
                }
                else{

                    }

                }
            }

            else if(X == par->right){

                if(par->left->color == Red){
                    par = RotateRight(par);
                    par->color = Black;
                    par->right->color = Red;
                }
            }
        }
    }

public:
    RedBlackTree(){
        RBT_root = 0;
        countNodes = 0;
    }

    ~RedBlackTree(){
        Clear(RBT_root);
    }

    void Clear(){
        Clear(RBT_root);
        countNodes = 0;
        RBT_root = 0;
    }

    void Show()
    {
        printf("[tree]\n");
        Show(RBT_root,0,'*');
    }

    bool Find(T value){
        Node<T> *node = RBT_root;
        while(node) {
            if(node->value==value) return true;
            if(node->value>value) node = node->left;
            else node = node->right;
        }
        return false;
    }

    void Insert(T value){
        if(!RBT_root) RBT_root = NewNode(value);
        else{
            Node<T> *node = RBT_root;
            Node<T> *par = NewNode(T());
            countNodes--;
            char flag = '\0';
            while(node){
                par = node;
                if(value < node->value){
                    node = node->left;
                    flag = 'L';
                }
                else if(value > node->value){
                    node = node->right;
                    flag = 'R';
                }
                else return;
            }
            node = NewNode(value);
            node->parent = par;
            if(flag == 'L') par->left = node;
            else par->right = node;
            if(par->color == Red) BalanceInsert(node);
        }
        RBT_root->color = Black;
    }

    void Remove(T value){
        Node<T> *node = RBT_root;
        char seid_son = '\0';
        while(node && node->value != value) {
            if(node->value > value) node = node->left;
            if(node->value < value) node = node->right;
        }

        if (node->value != value){
            cout << "false value" << endl;
            return;
        }

        if(node == node->parent->left) seid_son = 'L';
        else seid_son = 'R';

        if(!node->left && !node->right){                                   // Если нет детей
            if(node == RBT_root){
                delete RBT_root;
                return;
            }
            if(node == node->parent->left) node->parent->left = 0;
            else node->parent->right = 0;
        }

        else if(node->left && !node->right){                               // Если есть только левый сын
            if(node == RBT_root){
                RBT_root = node->left;
                RBT_root->parent = 0;
                RBT_root->color = Black;
                return;
            }
            else if(node == node->parent->left) node->parent->left = node->left;
            else node->parent->right = node->left;
            node->left->parent = node->parent;
        }

        else if(!node->left && node->right){                               // Если есть только правый сын
            if(node == RBT_root){
                RBT_root = node->right;
                RBT_root->parent = 0;
                RBT_root->color = Black;
                return;
            }
            else if(node == node->parent->left) node->parent->left = node->right;
            else node->parent->right = node->right;
            node->right->parent = node->parent;
        }

        else{                                                              // Если есть оба сына
            Node<T> *son = node->right;
            while(son->left) son = son->left;
            if(!son) son = node->left;
            node->value = son->value;

            if((son == son->parent->right) && (son->right)){
                son->right->parent = son->parent;
                son->parent->right = son->right;
            }
            else if(son->right){
                son->right->parent = son->parent;
                son->parent->left = son->right;
            }
            else if(son == son->parent->right) son->parent->right = 0;
            else son->parent->left = 0;
            node = son;
        }

        if(node->color == Black) BalanceRemove(node, seid);
    }

    unsigned int GetNodesCount(){
        return countNodes;
    }
};

void Test_int(){
    RedBlackTree<int> tree;
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(28);
    tree.Insert(-6);
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(-4);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(4);
    tree.Insert(17);
    cout << endl;
    tree.Show();

    cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
    cout << "\nFind(1) = " << tree.Find(1) << endl;
    cout << "Find(8) = " << tree.Find(8) << endl;

    cout << "Remove(7)" << endl;
    tree.Remove(7);
    cout << "After Remove : " << endl;
    tree.Show();

    cout << "\nAfter Clear : " << endl;
    tree.Clear();
    tree.Show();
}

void Test_double(){
    RedBlackTree<double> tree;
    tree.Insert(1.0);
    tree.Insert(5.54);
    tree.Insert(5.53);
    tree.Insert(5.8);
    tree.Insert(6.66);
    tree.Insert(0.13);
    tree.Insert(9.99);
    tree.Insert(6.455);
    tree.Insert(3.3);
    tree.Insert(2.15);
    tree.Insert(0);
    tree.Insert(8);
    cout << endl;
    tree.Show();
    cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
    cout << "\nFind(1.1) = " << tree.Find(1.1) << endl;
    cout << "Find(6.66) = " << tree.Find(6.66) << endl;
    cout << "\nAfter Clear : " << endl;
    tree.Clear();
    tree.Show();
}

void Test_char(){
    RedBlackTree<char> tree;
    tree.Insert('a');
    tree.Insert('b');
    tree.Insert('c');
    tree.Insert('d');
    tree.Insert('e');
    tree.Insert('f');
    tree.Insert('g');
    tree.Insert('h');
    tree.Insert('i');
    tree.Insert('j');
    cout << endl;
    tree.Show();
    cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
    cout << "\nFind('i') = " << tree.Find('i') << endl;
    cout << "Find('t') = " << tree.Find('t') << endl;
    cout << "\nAfter Clear : " << endl;
    tree.Clear();
    tree.Show();
}

void Test_string(){
    #include <string>
    //using std::string;
    RedBlackTree<std::string> tree;
    tree.Insert("Vika");
    tree.Insert("Roma");
    tree.Insert("Oleg");
    tree.Insert("Kate");
    tree.Insert("Olga");
    tree.Insert("Uliana");
    tree.Insert("Artem");
    tree.Insert("Vladislav");
    tree.Insert("Galina");
    tree.Insert("Pavel");
    cout << endl;
    tree.Show();
    cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
    cout << "\nFind(\"Svetlana\") = " << tree.Find("Svetlana") << endl;
    cout << "Find(\"Uliana\") = " << tree.Find("Uliana") << endl;
    cout << "\nAfter Clear : " << endl;
    tree.Clear();
    tree.Show();
}


int main(){
    Test_int();
    //Test_double();
    //Test_char();
    //Test_string();
    return 0;
}
