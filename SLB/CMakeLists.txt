cmake_minimum_required(VERSION 3.15)
project(SLB)

set(CMAKE_CXX_STANDARD 14)

add_executable(SLB main.cpp Server.cpp Server.h LoadBalancer.cpp LoadBalancer.h pkt.h RandomPacketGenerator.cpp RandomPacketGenerator.h)