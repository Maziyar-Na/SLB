//
// Created by maziy on 12/12/2019.
//

#ifndef SLB_PKT_H
#define SLB_PKT_H

#include <stdint-gcc.h>
#include <iostream>

namespace gpv{
    const uint8_t MAX_LEN = 32;

    struct  hdr {

        hdr();
        hdr(uint32_t ipSrc, uint16_t srcPort, uint16_t dstPort, uint64_t proto, uint64_t pktCount) :
            ip_src(ipSrc),
            tp_src(srcPort),
            tp_dst(dstPort),
            ip_proto(proto),
            pkt_count(pktCount) {}

        uint32_t ip_src     = 0;
        uint32_t ip_dst     = 0;
        uint16_t tp_src     = 0;
        uint16_t tp_dst     = 0;
        uint64_t ip_proto  :  8; // 0 - 255
        uint64_t pkt_count :  5; // 0 - 32 (MAX_LEN)
        uint64_t ts_us     : 51; // 0 - 225179981368524

        std::string str_desc() const;
    };

    struct pkt {
        pkt();
        pkt(uint64_t pad_, uint64_t pkt_len_, uint64_t ts_delta_us_, uint64_t ts_egress_delta_us_, uint16_t queue_id_, uint16_t queue_depth_, uint16_t ip_id_, uint32_t pd_) :
            pad(pad_),
            pkt_len(pkt_len_),
            ts_delta_us(ts_delta_us_),
            ts_egress_delta_us(ts_egress_delta_us_),
            queue_id(queue_id_),
            queue_depth(queue_depth_),
            ip_id(ip_id_),
            pd(pd_) {}

        uint64_t pad                :  4;
        uint64_t pkt_len            : 12; // 0 -     4096
        uint64_t ts_delta_us        : 26; // 0 - 67108864 -> 67s
        uint64_t ts_egress_delta_us : 22; // 0 -  4194304 ->  4s

        uint16_t queue_id           :  5; // 0 -   32
        uint16_t queue_depth        : 11; // 0 - 2048

        uint16_t ip_id;
        uint32_t pd;

    };

    struct gpv_t {
        struct gpv::hdr *hdr = {};
        struct gpv::pkt *pkt[gpv::MAX_LEN] = {{}};

        void print_gpv() {
            std::cout << "[dbg] "<< this->hdr->ip_src << " " << this->hdr->ip_dst << " " << this->hdr->tp_src<< " "
                   << this->hdr->tp_dst << " " << this->hdr->ip_proto<< " "  << this->hdr->pkt_count<< " "
                    << this->hdr->ts_us << std::endl;
        }
        friend inline std::ostream& operator<<(std::ostream& os_, const gpv::gpv_t& gpv_);
    };
}

#endif //SLB_PKT_H
