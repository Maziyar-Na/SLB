//
// Created by maziy on 12/12/2019.
//

#include <ctime>
#include <cstdlib>
#include "RandomPacketGenerator.h"


struct pkt* RandomPacketGenerator::generate() {

    //srand(time(NULL));

    uint32_t srcIp = rand() % ipSrcs.size();
    uint32_t srcPort = rand() % srcPorts.size();
    uint32_t dstPort = rand() % dstPorts.size();
    uint32_t proto = rand() % protos.size();

    struct pkt* p = new struct pkt;
    p->srcIp = ipSrcs[srcIp] ;
    p->dstIp = ipDsts[0];
    p->srcPort = srcPorts [srcPort];
    p->dstPort = dstPorts[dstPort];
    p->protocol = protos[proto];
    for(int i = 0; i<256; i++)
        p->payload[i] = 'a' + i%26;
    return p;
}