//
// Created by maziy on 12/12/2019.
//

#include <iostream>
#include "LoadBalancer.h"
#include "pkt.h"

struct pv_net_pkt* LoadBalancer::process_pkt(struct pkt *input_pkt) {
    struct pv_net_pkt* rv = new struct pv_net_pkt;
    pkt5tuple pkt_info(input_pkt->srcIp, input_pkt->dstIp, input_pkt->srcPort, input_pkt->dstPort, input_pkt->protocol);
    unordered_map<pkt5tuple, Server*>::iterator it = flow_server_map.find(pkt_info);
    if ( it != flow_server_map.end()) {
        rv->dstIp = flow_server_map[pkt_info]->get_ip();
        //cout << "[dbg] Key: srcip: " << it->first.srcIp << " dstip: " << it->first.dstIp << " srcport: " <<  it->first.srcPort << " dstport: " << it->first.dstPort << " proto: " << it->first.protocol << endl;
        //cout << "[dbg] pkt info: srcip: " << pkt_info.srcIp << " dstip: " << pkt_info.dstIp << " srcport: " <<  pkt_info.srcPort << " dstport: " << pkt_info.dstPort << " proto: " << pkt_info.protocol << endl;
        //cout << "[dbg] Server found!" << endl;
        switch(rv->dstIp) {
            case 4321:
                counter[0]++;
                break;
            case 5432:
                counter[1]++;
                break;
            case 6543:
                counter[2]++;
                break;
            case 7654:
                counter[3]++;
                break;
            case 8765:
                counter[4]++;
                break;
            case 9876:
                counter[5]++;
                break;
        }
    }
    else {
        flow_server_map.insert({pkt_info, Servers[round_robin_counter]});
        rv->dstIp = Servers[round_robin_counter]->get_ip();
        round_robin_counter += 1;
        round_robin_counter %= Servers.size();
    }

    rv->pub_net_pkt = input_pkt;

    return rv;
}

void LoadBalancer::log_pkt(struct pv_net_pkt *out_pkt) {
    SLB_trace.write((char*) &out_pkt->dstIp, sizeof(uint32_t));
    SLB_trace.write((char*) &out_pkt->pub_net_pkt->srcIp, sizeof(uint32_t));
    SLB_trace.write((char*) &out_pkt->pub_net_pkt->dstIp, sizeof(uint32_t));
    SLB_trace.write((char*) &out_pkt->pub_net_pkt->srcPort, sizeof(uint32_t));
    SLB_trace.write((char*) &out_pkt->pub_net_pkt->dstPort, sizeof(uint32_t));
    SLB_trace.write((char*) &out_pkt->pub_net_pkt->protocol, sizeof(uint32_t));
    SLB_trace.write(out_pkt->pub_net_pkt->payload, sizeof(char)*256);
    //SLB_trace.write((char*) &out_pkt, sizeof(out_pkt));
}