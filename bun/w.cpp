struct IntAbstractQueue {
    virtual void push(int x) = 0;
    virtual int pop() = 0;
    virtual bool is_empty() const = 0;
    virtual bool is_full() const = 0;

    virtual ~IntAbstractQueue() { }
};

struct IntStack: IntAbstractQueue {
    void push(int x) override {
        data[top++] = x;
    }
    int pop() override {
        return data[--top];
    }
    bool is_empty() const override {
        return 0 == top;
    }
    bool is_full() const override {
        return 10 == top;
    }
private:
    unsigned top = 0;
    int data[10];
};

class IntStackWithMax : public IntStack {
public:
int get_max() const {
IntStack* L =  new IntStack;
int max = 0;
int m1 = 0;
if ((*L).is_empty() == true) {
m1 = 0;
}
else if ((*L).is_full() == true) {
for (int i = 10; i>= 1; --i) {
    m1 = (*L).pop();
    if (m1 >= max) {max = m1;}
}
 }
else {
    while ((*L).is_empty() != true) {
         m1 = (*L).pop();
    if (m1 >= max) {max = m1;}
    }

}
delete L;
return max;
}
};


#include <cassert>
void with_queue_do(IntAbstractQueue &q) {
    assert(q.is_empty());
    q.push(1);
    assert(!q.is_empty());
    assert(1 == q.pop());
    assert(q.is_empty());
    for (int cnt = 0; cnt != 10; ++cnt)
        q.push(cnt);
    assert(q.is_full());
}
void with_stack_do(IntStack &s) {
    with_queue_do(s); 
    for (int cnt = 10; cnt != 0; --cnt)
        assert(cnt - 1 == s.pop());
    assert(s.is_empty());
}
void with_stackwithmax_do(IntStackWithMax &swm) {
    with_queue_do(swm);
    for (int cnt = 10; cnt != 0; --cnt)
        assert(cnt - 1 == swm.get_max() and cnt - 1 == swm.pop());
    assert(swm.is_empty()); 
}

int main() {
    IntStackWithMax swm;
    with_stack_do(swm);
    with_stackwithmax_do(swm);
    return 0;
}