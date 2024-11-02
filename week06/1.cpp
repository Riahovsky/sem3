#include <iostream>
/*template <typename T>
struct Node {
private:
    T value;
};
*/

template <typename T>
struct List {
private:
template <typenaame U>
struct Node {
private:
    U value;
    Node* next;
    Node* prev;
public:
    Node(const Node<U> other) :
};
Node* NIL;
Node* HEAD;
Node* TAIL;
public:
List(T value) {
    NIL = new Node<T>();
    HEAD = new Node<T>();
    TAIL = HEAD;
}

List(List<T>& other) {
    this->HEAD = new Node<T>(*other.HEAD);
    this->TAIL = other.TAIL;
    this->NIL = new Node<T>(*other.NIL);
}
List() : NIL(new Node<T>) {

}
~List() {
    delete HEAD;
    delete NIL;
}


};

int main() {
    //List<int>::Node<int> node = List<int>::Node<int>();
    List<int>* old_list = new List<int>(12); 
    List<int>* new_list = old_list;
    delete new_list;
}