//
// Created by maziy on 12/12/2019.
//

#ifndef SLB_SERVER_H
#define SLB_SERVER_H


#include <stdint-gcc.h>
using namespace std;

class Server {
private:
    uint32_t ip;
public:
    Server(uint32_t ip_) : ip(ip_) {}
    uint32_t get_ip(){return ip;}
    void set_ip(uint32_t ip_) { ip = ip_; }
};


#endif //SLB_SERVER_H
