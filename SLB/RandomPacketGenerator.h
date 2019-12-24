//
// Created by maziy on 12/12/2019.
//

#ifndef SLB_RANDOMPACKETGENERATOR_H
#define SLB_RANDOMPACKETGENERATOR_H


#include <vector>
#include "pkt.h"
using namespace std;

class RandomPacketGenerator {
private:
    vector<uint32_t> ipSrcs;

    vector<uint32_t> ipDsts;

    vector<uint32_t> srcPorts;

    vector<uint32_t> dstPorts;

    vector<uint32_t> protos;
public:
    RandomPacketGenerator(vector<uint32_t> ipSrcs_, vector<uint32_t> ipDsts_, vector<uint32_t> srcPorts_, vector<uint32_t> dstPorts_, vector<uint32_t> protos_) :
    ipSrcs(ipSrcs_),
    ipDsts(ipDsts_),
    srcPorts(srcPorts_),
    dstPorts(dstPorts_),
    protos(protos_){}

    struct gpv::gpv_t* generate();
};


#endif //SLB_RANDOMPACKETGENERATOR_H
