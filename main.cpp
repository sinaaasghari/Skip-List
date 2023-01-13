///Sina Asghari
//SkipList

#include<iostream>
#include<string.h>
#include<stack>
#include<vector>
#include<bits\stdc++.h>
using namespace std;
template <class T>
struct Node{
    public:
    T key;
    Node<T>* next;
    Node<T>* pre;
    Node<T>* up;
    Node<T>* down;
    Node(const T& key){
        this->key = key;
        this->next = NULL;
        this->down = NULL;
        this->up = NULL;
        this->pre = NULL;
    }
    void print(){
        if(key < 2147483645 && key > -2147483645){
            cout << key <<" ";
        }
    }
};
template <class T>
class SkipList{
    public:
    SkipList();
    
    void insert(T n);
   
    Node<T>* insertLevel(T n, int level, Node<T>* down);
   
    void print();
   
    Node<T>* Search(T key);
   
    void Delete_Node(Node<T>* N);
    void Delete(T key);

   
    vector <Node<T>*> Heads;
   
    int levels;
};
template <class T>
SkipList<T>::SkipList(){
    srand(static_cast<unsigned int>(time(NULL)));
    Node<T>* head1 = new Node<T>(-2147483645);
    Node<T>* tail1 = new Node<T>(2147483645);
    head1->next = tail1;
    tail1->pre = head1;
    Heads.push_back(head1);
}
template <class T>
Node<T>* SkipList<T>::Search(T key){
    Node<T>* topleft;
    topleft = Heads[Heads.size() - 1];
    Node<T>* pt = new Node<T>(-2147483645);
    pt = topleft;
    while(pt != NULL){
        if(pt->key == key){
            break;
        }
        else if(key > pt->key && key >= pt->next->key){
            pt = pt->next;
        }
        else if(key > pt->key && key < pt->next->key){
            pt = pt->down;
        }
    }
    return pt;
}
template <class T>
Node<T>* SkipList<T>::insertLevel(T data, int level, Node<T>* Down){
    int i = level;
    Node<T>* N = new Node<T>(data);
    N->down = Down;
    Node<T>* pt = new Node<T>(0);
    pt = Heads[i];

    while(pt->next != NULL && data > pt->next->key){
        pt = pt->next;
    }
    N->pre = pt;
    N->next = pt->next;
    pt->next = N;
    N->next->pre = N;
    return N;
}
template <class T>
void SkipList<T>::insert(T data){
    int i = 0;
    Node<T>* Down = insertLevel(data, i, NULL);
    int coin_toss = rand() % 2;
    while(coin_toss == 0){
        i++;
        if(levels < i){
            levels++;
            Node<T>* newHead = new Node<T>(-2147483645);
            Node<T>* newTail = new Node<T>(2147483645);
            newHead->next = newTail;
            newTail->pre = newHead;
            Heads[i - 1]->up = newHead;
            newHead->down = Heads[i - 1];
            Heads.push_back(newHead);
        }
        Node<T>* N = insertLevel(data, i, Down);
        Down->up = N;
        Down = N;
        coin_toss = rand() % 2;
    }
    return;
}
template <class T>
void SkipList<T>::Delete_Node(Node<T>* N){
    if(N->down != NULL){
        N->down->up = NULL;
    }
    if(N->up != NULL){
        N->up->down = NULL;
    }
    Node<T>* NEXT = N->next;
    Node<T>* PRE = N->pre;
    PRE->next = NEXT;
    delete(N);
    NEXT->pre = PRE;
}
template<class T>
void SkipList<T>::Delete(T N){
    Node<T>* pt = Search(N);
    while(pt != NULL){
        Node<T>* temp = pt->down;
        Delete_Node(pt);
        pt = temp;
    }
}
template <class T>
void SkipList<T>::print(){
    for(int i = 0; i != Heads.size(); i++){
        cout <<"LEVEL: " << i << endl;
        Node<T>* pt = new Node<T>(-2147483645);
        pt = Heads[i];
        while(pt != NULL){
            pt->print();
            pt = pt->next;
        }
        cout << endl;
    }
}

int main(){
    SkipList<int> *SL = new SkipList<int>();
    SL->insert(4);
    SL->insert(54);
    SL->insert(147);
    SL->insert(14);
    SL->insert(18);
    SL->insert(1777);
    SL->insert(1156);
    SL->insert(1);
    SL->print();
    cout << endl;
    SL->Delete(18);
    SL->print();
}