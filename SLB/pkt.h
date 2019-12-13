//
// Created by maziy on 12/12/2019.
//

#ifndef SLB_PKT_H
#define SLB_PKT_H

#include <stdint-gcc.h>

struct pkt {

    uint32_t srcIp;
    uint32_t dstIp;
    uint32_t srcPort;
    uint32_t dstPort;
    uint32_t protocol;

    char payload[256];
};

struct pv_net_pkt {

    uint32_t dstIp;
    struct pkt* pub_net_pkt;
};

#endif //SLB_PKT_H
