#include <iostream>
#include <vector>
#include "RandomPacketGenerator.h"
#include "Server.h"
#include "LoadBalancer.h"

#define __PKT_NUM__ 3000 //30M packets

using namespace std;

int main() {
    cout << "[INFO] Load balancer simulator started!" << endl;

    vector<uint32_t> srcIps{1234, 2345, 3456, 4567, 5678, 6789};
    vector<uint32_t> dstIps{8910};
    vector<uint32_t> srcPorts{443, 80, 8080, 22, 21,  53, 88};
    vector<uint32_t> dstPorts{443, 80, 8080, 22, 21,  53, 88};
    vector<uint32_t> protos{1,2,3,4,5,6};

    RandomPacketGenerator RPG(srcIps, dstIps, srcPorts, dstPorts, protos);

    Server s1(4321);
    Server s2(5432);
    Server s3(6543);
    Server s4(7654);
    Server s5(8765);
    Server s6(9876);

    vector<Server*> servers;
    servers.push_back(&s1);
    servers.push_back(&s2);
    servers.push_back(&s3);
    servers.push_back(&s4);
    servers.push_back(&s5);
    servers.push_back(&s6);

    LoadBalancer SLB (servers, "SLBtrace.gpv");


    for (int i = 0; i < __PKT_NUM__; ++i) {
        //cout << "#####################################################################################################################################################################################" << endl;
        struct gpv::gpv_t* gpv_pkt = RPG.generate();

        struct gpv::gpv_t* pvnp = SLB.process_pkt(gpv_pkt);

        /*cout << "pv net destination ip: " << pvnp->dstIp << " pkt src ip: " << pvnp->pub_net_pkt->srcIp <<
        " pkt dstIp: " << pvnp->pub_net_pkt->dstIp << " pkt src port: " << pvnp->pub_net_pkt->srcPort << " pkt dst port: " << pvnp->pub_net_pkt->dstPort <<
        " pkt proto: " << pvnp->pub_net_pkt->protocol << endl;*/

        SLB.log_pkt(pvnp);
        for(auto pkt : gpv_pkt->pkt)
            delete(pkt);
        delete(gpv_pkt);
    }
    SLB.close_log_file();
    SLB.print_counter();
    return 0;
}