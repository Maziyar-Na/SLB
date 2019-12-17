//
// Created by maziy on 12/12/2019.
//

#ifndef SLB_LOADBALANCER_H
#define SLB_LOADBALANCER_H

#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>
#include "Server.h"

using namespace std;




typedef  struct pkt5tuple_private pkt5tuple;
struct pkt5tuple_private {
    uint32_t srcIp;
    uint32_t dstIp;
    uint32_t srcPort;
    uint32_t dstPort;
    uint32_t protocol;

    pkt5tuple_private() {}

    pkt5tuple_private(uint32_t srcIp_, uint32_t dstIp_, uint32_t srcPort_, uint32_t dstPort_, uint32_t protocol_) :
            srcIp(srcIp_),
            dstIp(dstIp_),
            srcPort(srcPort_),
            dstPort(dstPort_),
            protocol(protocol_) {}

    bool operator==(const pkt5tuple &p) const
    {
        return srcIp == p.srcIp && dstIp == p.dstIp && srcPort == p.srcPort && dstPort == p.dstPort && protocol == p.protocol;
    }

    bool operator> (const pkt5tuple &c1)const
    {
        return c1.srcIp < srcIp;
    }

    bool operator>= (const pkt5tuple &c1)const
    {
        return c1.srcIp <= srcIp;
    }

    bool operator< (const pkt5tuple &c1)const
    {
        return c1.srcIp > srcIp;
    }

    bool operator<= (const pkt5tuple &c1)const
    {
        return c1.srcIp >= srcIp;
    }
};

namespace std {
    template<>
    struct hash<pkt5tuple>
    {
        std::size_t operator()(const pkt5tuple& k) const
        {
            using std::size_t;
            using std::hash;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return hash<uint32_t >()(k.srcIp)
                   ^ hash<uint32_t >()(k.dstIp)
                   ^ hash<uint32_t >()(k.srcPort)
                   ^ hash<uint32_t >()(k.dstPort)
                   ^ hash<uint32_t >()(k.dstPort);
        }
    };
}


class LoadBalancer {
private:

    unordered_map<pkt5tuple, Server*> flow_server_map;
    vector<Server*> Servers;
    uint8_t round_robin_counter;
    ofstream SLB_trace;
    uint32_t counter[6] = {0,0,0,0,0,0};
public:
    LoadBalancer(vector<Server*> servers, string log_file) : Servers(servers), round_robin_counter(0), SLB_trace(ofstream(log_file, ios::binary)) {}

    vector<Server*> get_servers() { return Servers; }
    void add_server(Server* s){ Servers.push_back(s); }

    struct pv_net_pkt* process_pkt(struct pkt* input_pkt);

    void log_pkt(struct pv_net_pkt* out_pkt);

    void close_log_file() {SLB_trace.close();}

    void print_counter(){cout << "[INFO] server1: " << counter[0]+1 << " server2: " << counter[1]+1 << " server3: " << counter[2]+1 << " server4: " << counter[3]+1 <<
    " server5: " << counter[4]+1 << " server6: " << counter[5]+1 << endl;}
};


#endif //SLB_LOADBALANCER_H
