#include <iostream>
#include <vector>

using std namespace;
template <typename T>
class Node {
    int data;
    vector<Node*> next;
    Node(int data, int Level): data(data), next(Level+1,nullptr) {}
};

class SkipList {
    private:
        Node* head;
        int Level;
    public:
        SkipList(): head(nullptr), Level(0) {}
        SkipList(int maxNumberofLevel) {
            head = new Node(0, maxNumberofLevel);
            Level = 0;
        }
        friend bool empty {
            return head == nullptr;
        }
        void insert(int data) 
{
    int newLevel = 0; 

    while (newLevel < maxNumberOfLevel and (rand() % 2) == 1) 
    {
        newLevel++;
    } 

    if (Level < newLevel) 
    {
        head->next.resize(newLevel + 1, nullptr);
        
        Level = newLevel;
    }


    Node* current = head;


    vector<Node*> Update(Level + 1, nullptr);


    for (int i = Level; i >= 0; i--) 
    {

        while (current->next[i] and current->next[i]->data < data) 
        {
            current = current->next[i];
        }

        Update[i] = current;

    }

    current = current->next[0];  

    if (current == nullptr or current->data != data)
    {
        Node* newNode = new Node(data, Level);

        for (int i = 0; i <= newLevel; i++) 
        {
            newNode->next[i] = Update[i]->next[i];

            Update[i]->next[i] = newNode;

        }

        cout << "Element " << data << " inserted successfully.\n";
    }
    else
    {
        cout << "Element " << data << " already exists.\n";  
    }
} 

};

int main() {

}