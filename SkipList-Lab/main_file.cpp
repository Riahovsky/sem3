#include <iostream>
#include <vector>
#include <random>

#include <iterator>
#include <algorithm>

using namespace std;
const int maxNumberOfLevel = 5;
const float p = 0.3;

template <typename T>
class Node
{
public:
    T data;
    vector<Node<T>*> next;                                            
    Node(T data, int Level) : data(data), next(Level + 1, nullptr) {} 
};

template <typename T>
class skipList
{
private:
    Node<T> *head;
    int Level;
    int s = 0;

public:
    skipList() {
        head = new Node(T(), maxNumberOfLevel);  
        Level = 0;
        s = 0;
        
    }

    skipList(skipList<T> const & other): head(new Node(T(), maxNumberOfLevel)), Level(other.Level), s(other.s) {
        head = other.head;
        cout << "Copy constructor" << endl;

    }

    skipList<T>& operator=(skipList<T>& other) {
        delete this->head;
        this->Level = other.Level;
        this->head = other.head;
        this->s = other.s;
        cout << "Copy operator" << endl;
        return  *this;
    }

    skipList(skipList<T> const&& other):head(other.head),Level(other.Level) {
        delete other.head ;
        other.head = nullptr;
        other.Level = 0;
        other.s = 0;
        cout << "Move constructor" << endl;
    }

    skipList<T>& operator=(skipList<T>&& other) {
        if (this != other) {
            delete this->head;
            this->head = other.head;
            this->Level = other.Level;
            this->s = other.s;
            delete other.head ;
            other.head = nullptr;
            other.Level = 0;
            other.s = 0;
            cout << "Move operator" << endl;

        }
        return *this;
    }

    void empty() {
        bool q = false;
        if (head->next[0] == nullptr and s == 0) {
            q = true;
        }
        cout << "Empty:" << " " << q << endl;
    }

    void size() {
        cout << "Size:" << " " << s << endl;
    }

    void insert(T data) {
        int newLevel = 0; 
        ++s;
        int start = 0;
        int end = 100;

    

    while (newLevel < maxNumberOfLevel and rand() % (end - start + 1) + start <= p*100) 
    {
        newLevel++;
    } 
    

    if (Level < newLevel) 
    {
        head->next.resize(newLevel + 1, nullptr);
        
        Level = newLevel;
    }


    Node<T>* current = head; 


    vector<Node<T>*> Update(Level + 1, nullptr); 

    

    for (int i = Level; i >= 0; i--) 
    {
        

        while (current->next[i] and current->next[i]->data < data) 
        {
            current = current->next[i];
        }
    

        Update[i] = current;

    }

    current = current->next[0];   

    if (current == nullptr ) 
    {
        Node<T>* newNode = new Node(data, Level);

        for (int i = 0; i <= newLevel; i++) 
        {
            newNode->next[i] = Update[i]->next[i];

            Update[i]->next[i] = newNode;  

        }

        cout << "Element " << data << " inserted successfully.\n";
    }

}
void display() 
{

    cout << "skip List:"<< endl;

    for (int i = Level; i >= 0; i--) 
    {
        Node<T>* current = head->next[i]; 

        cout << "Level " << i << ": "; 

        while (current != nullptr)       
        {
            cout << current->data << " ";
            current = current->next[i]; 
        }
        cout << endl;
    }
}

class Iterator {
    private: 
    friend class skipList;
    public:
    Iterator()  {}

    Node<T>* begin() {
        cout << "begin()" << endl;
        return head->next[0];
    }
    //Iterator end() {
    //    return next.end();
  // }


};
Iterator it;



/*
	class Iterator{
		friend class SkipList<T>;
	public:
		Iterator(const Iterator& InIterator) {};
		Iterator& operator++(Node<T>*) {

        };
		Iterator& operator--() {

        };
		Iterator operator++() {

        };
		Iterator operator--() {

        };
	Iterator Begin(vector<Node<T>*> curr) {
        return curr.begin();
    };
	Iterator End(vector<Node<T>*> curr) {
       return curr.end();
    };
	void erase() {};
	int count() {};
	void clear() {};
	Iterator find() {};
};
*/
};  





int main()
{
    skipList<int> MMM;
    skipList<int> MMM1 = skipList(MMM);
    skipList<int> MMM2;
    MMM2 = MMM;
    MMM.empty();
    MMM.size();

    MMM.insert(1);
    MMM.insert(2);
    MMM.insert(3);

    MMM.insert(4);
    MMM.insert(5);
    MMM.insert(6);
    MMM.insert(6);
    MMM.insert(6);
    MMM.display();
    MMM.size();
    cout << MMM.it.begin()->data << endl;

}
