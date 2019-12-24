//
// Created by maziy on 12/12/2019.
//

#include <ctime>
#include <cstdlib>
#include "RandomPacketGenerator.h"


struct gpv::gpv_t* RandomPacketGenerator::generate() {

    //srand(time(0));


    uint64_t pktCount = (rand() % 32) + 1; // Generate random number of packets which goes into GPV
    uint32_t srcIp = rand() % ipSrcs.size();
    uint32_t srcPort = rand() % srcPorts.size();
    uint32_t dstPort = rand() % dstPorts.size();
    uint32_t proto = rand() % protos.size();
    struct gpv::hdr* pkt_hdr = new struct gpv::hdr(ipSrcs[srcIp], srcPorts[srcPort], dstPorts[dstPort], protos[proto], pktCount);


    gpv::gpv_t* rv = new struct gpv::gpv_t();
    for (int i = 0; i < pktCount; ++i) {
        uint64_t pad_ = 0;
        uint64_t pkt_len_ = (rand()%4096) + 1;
        uint64_t ts_delta_us_ = (rand()%67108864) + 1;
        uint64_t ts_egress_delta_us_ = (rand()%4194304 ) + 1;
        uint16_t queue_id_ = (rand()%32) + 1;
        uint16_t queue_depth_ = (rand()%2048) + 1;
        uint16_t ip_id_ = (rand()%65536) + 1;
        uint32_t pd_ = ipDsts[0];

        struct gpv::pkt* p = new struct gpv::pkt(pad_, pkt_len_, ts_delta_us_, ts_egress_delta_us_, queue_id_, queue_depth_, ip_id_, pd_);
        rv->pkt[i] = p;
    }
    /* cout <<"[dbg] src ip: " <<pkt_hdr->ip_src << " " <<"dst ip: " << pkt_hdr -> ip_dst << " "
         <<"src port: " << pkt_hdr->tp_src << " " <<"dst port: " << pkt_hdr->tp_dst << " pkt count: " << pkt_hdr->pkt_count << " proto: " << pkt_hdr->ip_proto
         << " pkt ts_us: " << pkt_hdr->ts_us << endl; */
    rv->hdr = pkt_hdr;
    return rv;
}