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


typedef struct pkt5tuple {
    uint32_t srcIp;
    uint32_t dstIp;
    uint32_t srcPort;
    uint32_t dstPort;
    uint32_t protocol;

    pkt5tuple() {}

    pkt5tuple(uint32_t srcIp_, uint32_t dstIp_, uint32_t srcPort_, uint32_t dstPort_, uint32_t protocol_) :
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
}pkt5Tuple;

class LoadBalancer {
private:

    map<pkt5tuple, Server*> flow_server_map;
    vector<Server*> Servers;
    uint8_t round_robin_counter;
    ofstream SLB_trace;
public:
    LoadBalancer(vector<Server*> servers, string log_file) : Servers(servers), round_robin_counter(0), SLB_trace(ofstream(log_file, ios::binary)) {}

    vector<Server*> get_servers() { return Servers; }
    void add_server(Server* s){ Servers.push_back(s); }

    struct pv_net_pkt* process_pkt(struct pkt* input_pkt);

    void log_pkt(struct pv_net_pkt* out_pkt);

    void close_log_file() {SLB_trace.close();}
};


#endif //SLB_LOADBALANCER_H
