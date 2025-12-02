#include <iostream>
#include <string>
#include <vector>

class Clas{

private:

char id;

public:

Clas(char type) : id(type){}

char get_id() const {
    return this->id;
}

};

int main(){
    Clas c1('R');
    Clas c2('L');
    Clas c3('C');
    Clas c4('R');
    std::vector<Clas> vec{c1,c2,c3,c4};

    std::vector<Clas> r{0};
    std::vector<Clas> c{0};
    std::vector<Clas> l{0};

     for(auto i : vec){

        switch(i.get_id()){

            case 'R':
                r.push_back(i);
                break;

            case 'L':
                l.push_back(i);
                break;

            case 'C':
                c.push_back(i);
                break;
        }
    }

    std::cout << "res" << std::endl;

    for(int i = 0; i < r.size(); i++){
        std::cout << r[i].get_id() << " " << std::endl;
    }

    std::cout << "ind" << std::endl;

    for(int i = 0; i < l.size(); i++){
        std::cout << l[i].get_id() << " " << std::endl;
    }

    std::cout << "cap" << std::endl;

    for(int i = 0; i < c.size(); i++){
        std::cout << c[i].get_id() << " " << std::endl;
    }
}