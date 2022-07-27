#ifndef HELLOCPP_SIMPLE_H
#define HELLOCPP_SIMPLE_H


#include <iostream>

class Simple {
private:
    int id{};

public:
    Simple(int id) : id(id) {}
    int getId() const { return id; }
    void setId(int nid) {
        std::cout << "old: " << this->id << " new: " << nid << std::endl;
        id = nid;
    }
};


#endif //HELLOCPP_SIMPLE_H
