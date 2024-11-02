#include <iostream>
#include <vector>
class Human {
    protected:
    int age;
    std::string name;
public:
Human(int age, std::string name): age(age), name(name) {
    std::cout << "Human()" << std::endl;
}

~Human(){
    std::cout << "~Human" << std::endl;
}

virtual void privet() const {
    std::cout << name << std::endl;
}
};

class Teacher : public Human{
    private:
    public:
    Teacher(int age,std::string name) : Human(age,name){
        std::cout << "Teacher()" << std::endl;
        //void privet() const override {}

    }
};




int main() {
    Human h0 = Human(60, "Mike");
    Teacher t0 = Teacher(50,"Walter");
    std::vector<Human*> container = {&h0, &t0};
    for (auto el: container) {
        el->privet();
    }
     t0.Human::privet(); 

    return 0;
}