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

    void DeleteNode(Node<T>* node){
        countNodes--;
        delete node;
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
        if (X->parent->left == X) X->parent->left = Y;
        else X->parent->right = Y;
        Y->left = X;
        X->parent = Y;
        return Y;
    }

    Node<T> *RotateRight(Node<T> *X){
        Node<T> *Y = X->left;
        X->left = Y->right;
        if (Y->right) Y->right->parent = X;
        Y->parent = X->parent;
        if (X->parent->right == X) X->parent->right = Y;
        else X->parent->left = Y;
        Y->right = X;
        X->parent = Y;
        return Y;
    }

    void BalanceInsert(Node<T>* node){
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
            if((!(par->parent->right) || (par->parent->right->color == Black)) && flag!=1){ //если par - левый сын своего отца, а правый сын черный
                if(node == par->right) par = RotateLeft(par);
                par->color = Black;
                par->parent->color = Red;
                par = RotateRight(par->parent);
            }
        }
    }

    /*bool BalanceRemove1(Node<T>**root){
        Node<T> *node=*root;
        Node<T> *left=node->left;
        Node<T> *right=node->right;
        if(left && !left->color) {
            left->color=Black;
            return false;
        }
        if(right && !right->color) { // случай 1
            node->color=Red;
            right->color=Black;
            node=*root=RotateLeft(node);
            if(BalanceRemove1(&node->left)) node->left->color=Black;
            return false;
        }
        unsigned int mask=0;
        Node<T> *right_left=right->left;
        Node<T> *right_right=right->right;
        if(right_left && !right_left->color)    mask|=1;
        if(right_right && !right_right->color)  mask|=2;
        switch(mask)
        {
        case 0:     // случай 2 - if((!p21 || !p21->red) && (!p22 || !p22->red))
            right->color=Black;
            return true;
        case 1:
        case 3:     // случай 3 - if(p21 && p21->red)
            right->color=Red;
            right_left->color=Black;
            right_right=node->right=RotateRight(right);
            right_right=right->right;
        case 2:     // случай 4 - if(p22 && p22->red)
            right->color=node->color;
            right_right->color=node->color=Black;
            *root=RotateLeft(node);
        }
        return false;
    }

    bool BalanceRemove2(Node<T>**root){

        Node<T> *node=*root;
        Node<T> *left=node->left;
        Node<T> *right=node->right;
        if(right && !right->color) {
            right->color=Black;
            return false;
        }
        if(left && !left->color) { // случай 1
            node->color=Red;
            left->color=Black;
            node=*root=RotateRight(node);
            if(BalanceRemove2(&node->right)) node->right->color=Black;
            return false;
        }
        unsigned int mask=0;
        Node<T> *left_left=left->left;
        Node<T> *left_right=left->right;
        if(left_left && !left_left->color)      mask|=1;
        if(left_right && !left_right->color)    mask|=2;
        switch(mask) {
        case 0:     // случай 2 - if((!p12 || !p12->red) && (!p11 || !p11->red))
            left->color=Red;
            return true;
        case 2:
        case 3:     // случай 3 - if(p12 && p12->red)
            left->color=Red;
            left_left->color=Black;
            left=node->left=RotateLeft(left);
            left_left=left->left;
        case 1:     // случай 4 - if(p11 && p11->red)
            left->color=node->color;
            left_left->color=node->color=Black;
            *root=RotateRight(node);
        }
        return false;
    }*/

    bool GetMin(Node<T>**root, Node<T>**result){
        Node<T> *node=*root;
        if(node->left) {
            if(GetMin(&node->left,result)) return BalanceRemove1(root);
        } else {
            *root=node->right;
            *result=node;
            return node->color;
        }
        return false;
    }

    bool Remove(Node<T>**root, T value){
        Node<T> *t, *node = *root;
            if(!node) return false;
            if(node->value < value) {
                if(Remove(&node->right,value)) return BalanceRemove2(root);
            }
            else if(node->value > value) {
                if(Remove(&node->left,value)) return BalanceRemove1(root);
            }
            else {
                bool result;
                if(!node->right) {
                    *root=node->left;
                    result=node->color;
                }
                else {
                    result=GetMin(&node->right,root);
                    t=*root;
                    t->color=node->color;
                    t->left=node->left;
                    t->left=node->right;
                    if(result) result=BalanceRemove2(root);
                }
                DeleteNode(node);
                return result;
            }
            return 0;
    }


public:
    RedBlackTree(){
        RBT_root = 0;
        countNodes = 0;
    }

    ~RedBlackTree(){
        Clear(RBT_root);
        countNodes = 0;
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
        Node<T> *node=RBT_root;
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
            Node<T> *par = NewNode(0);
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
        Remove(&RBT_root,value);
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
    cout << endl;
    tree.Show();

    cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
    /*cout << "\nFind(-1) = " << tree.Find(-1) << endl;
    cout << "Find(8) = " << tree.Find(8) << endl;

    cout << "\nAfter Remove(477) : " << endl;
    tree.Remove(477);
    tree.Show();*/

    cout << "\nAfter Clear : " << endl;
    tree.Clear();
    tree.Show();
}
/*void Test_double(){
    RedBlackTree<double> tree;
    tree.Insert(1.0);
    tree.Insert(5.54);
    tree.Insert(5.53);
    tree.Insert(5.8);
    tree.Insert(6/9);
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
    cout << "Find(6/9) = " << tree.Find(6/9) << endl;
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
}*/


int main(){
    Test_int();
    //Test_double();
    //Test_char();
    //Test_string();
    return 0;
}

/*RedBlackTree<int> EmptyNode(0, Black, nullptr, nullptr, nullptr);

RedBlackTree<int> *NilNode = &EmptyNode;

Stemplate <typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::NewNode(T value){

}
template <typename T>
void RedBlackTree<T>::DeleteNode(Node*){

}
template <typename T>
void RedBlackTree<T>::Clear(Node*){

}
template <typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::Rotate21(Node*){

}
template <typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::Rotate12(Node*){

}
template <typename T>
void RedBlackTree<T>::BalanceInsert(Node**){

}
template <typename T>
bool RedBlackTree<T>::BalanceRemove1(Node**){

}
template <typename T>
bool RedBlackTree<T>::BalanceRemove2(Node**){

}
template <typename T>
bool RedBlackTree<T>::Insert(T, Node**){

}
template <typename T>
bool RedBlackTree<T>::GetMin(Node**, Node**){

}
template <typename T>
bool RedBlackTree<T>::Remove(Node**, T){

}
*/
