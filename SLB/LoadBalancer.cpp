//
// Created by maziy on 12/12/2019.
//

#include <iostream>
#include "LoadBalancer.h"
#include "pkt.h"

struct gpv::gpv_t* LoadBalancer::process_pkt(struct gpv::gpv_t *input_pkt) {

    //input_pkt->print_gpv();
    pkt5tuple pkt_info(input_pkt->hdr->ip_src, input_pkt->pkt[0]->pd, input_pkt->hdr->tp_src, input_pkt->hdr->tp_dst, input_pkt->hdr->ip_proto);
    unordered_map<pkt5tuple, Server*>::iterator it = flow_server_map.find(pkt_info);
    num_of_gpvs++;
    if ( it != flow_server_map.end()) {
        input_pkt->hdr->ip_dst = flow_server_map[pkt_info]->get_ip();
        switch(input_pkt->hdr->ip_dst) {
            case 4321:
                counter[0] += input_pkt->hdr->pkt_count;
                break;
            case 5432:
                counter[1] += input_pkt->hdr->pkt_count;
                break;
            case 6543:
                counter[2] += input_pkt->hdr->pkt_count;
                break;
            case 7654:
                counter[3] += input_pkt->hdr->pkt_count;
                break;
            case 8765:
                counter[4] += input_pkt->hdr->pkt_count;
                break;
            case 9876:
                counter[5] += input_pkt->hdr->pkt_count;
                break;
        }
    }
    else {


        flow_server_map.insert({pkt_info, Servers[round_robin_counter]});
        input_pkt->hdr->ip_dst = Servers[round_robin_counter]->get_ip();

        switch(input_pkt->hdr->ip_dst) {
            case 4321:
                counter[0] += input_pkt->hdr->pkt_count;
                break;
            case 5432:
                counter[1] += input_pkt->hdr->pkt_count;
                break;
            case 6543:
                counter[2] += input_pkt->hdr->pkt_count;
                break;
            case 7654:
                counter[3] += input_pkt->hdr->pkt_count;
                break;
            case 8765:
                counter[4] += input_pkt->hdr->pkt_count;
                break;
            case 9876:
                counter[5] += input_pkt->hdr->pkt_count;
                break;
        }
        round_robin_counter += 1;
        round_robin_counter %= Servers.size();
    }

    return input_pkt;
}

void LoadBalancer::log_pkt(struct gpv::gpv_t *out_pkt) {
    //cout << out_pkt->hdr->ip_src << out_pkt->hdr->ip_dst << endl;
    uint64_t helper ;
    helper = (out_pkt->hdr->ip_proto << 56) | (out_pkt->hdr->pkt_count << 51) | (out_pkt->hdr->ts_us) ;
    SLB_trace << out_pkt->hdr->ip_src
              << out_pkt->hdr->ip_dst
              << out_pkt->hdr->tp_src
              << out_pkt->hdr->tp_dst
              << helper ;


    for(int i = 0; i < out_pkt->hdr->pkt_count; ++i){
        uint64_t helper2 ;
        uint16_t helper3 ;
        helper2 = (out_pkt->pkt[i]->pad << 60) | (out_pkt->pkt[i]->pkt_len << 48) | (out_pkt->pkt[i]->ts_delta_us << 22 ) | (out_pkt->pkt[i]->ts_egress_delta_us) ;
        helper3 = (out_pkt->pkt[i]->queue_id << 11) | (out_pkt->pkt[i]->queue_depth) ;
        SLB_trace << helper2
                  << helper3
                  << out_pkt->pkt[i]->ip_id
                  << out_pkt->pkt[i]->pd;
        //cout << sizeof(*(out_pkt->pkt[i]))/ sizeof(char) << endl;
    }

}

void LoadBalancer::print_numofGPVS() {
    cout << "[INFO] number of GPVS are: " << num_of_gpvs << endl;
}