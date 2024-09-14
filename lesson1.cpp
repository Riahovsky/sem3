#include <iostream>

using namespace std;
struct Node {
private:
    Node* next = nullptr;
    int value = 0;
    static Node* NIL;
    explicit Node();
public:
Node (int value) {
   // this->value = value;
   //this->set(value);
   set(value);
}
Node() : Node(42) {
    cout << "Node" << endl;
}
//Node() = default;

Node(int value,Node* ptr) : next(ptr),value(value) {
//this->next = ptr;
}

//Node (const Node& other) = default;

Node (const Node& other): next(other.next),value(other.value) {
    cout << "fkfkfkf" << endl;
}
//~Node() = default;
~Node() {
    //////
}
int get() const {
    return value;
}

void set(int _value)  {
    value = _value;
}

void setSquared(int value) {
    this->value = value;
}

bool isConected() const;

void loseNext() = delete;

};
Node* Node:: NIL = new Node(0);


bool Node::isConected() const {
    return this->next != nullptr;
}


int main () {
    Node HEAD = Node(42);
    Node TAIL = HEAD;
    Node middle = 14; // = Node(14);
    HEAD.set(21);
    cout << HEAD.get() ;
    return 0;
    }