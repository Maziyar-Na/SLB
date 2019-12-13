//
// Created by maziy on 12/12/2019.
//

#include <iostream>
#include "LoadBalancer.h"
#include "pkt.h"

struct pv_net_pkt* LoadBalancer::process_pkt(struct pkt *input_pkt) {
    struct pv_net_pkt* rv = new struct pv_net_pkt;
    pkt5tuple pkt_info(input_pkt->srcIp, input_pkt->dstIp, input_pkt->srcPort, input_pkt->dstPort, input_pkt->protocol);

    if (flow_server_map.find(pkt_info) != flow_server_map.end()) {
        rv->dstIp = flow_server_map[pkt_info]->get_ip();
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
    SLB_trace.write((char*) &out_pkt, sizeof(struct pv_net_pkt));
}