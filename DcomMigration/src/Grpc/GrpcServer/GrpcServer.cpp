#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX_DEPRECATION_WARNINGS
#pragma warning(disable: 4996)

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include <grpcpp/grpcpp.h> // For using gRPC

#include "GrpcDeviceServiceImpl.h"

using grpc::Server;
using grpc::ServerBuilder;

void RunServer()
{
    std::string server_address("0.0.0.0:50051");    // Replace "0.0.0.0" with your address and port.

    GrpcDeviceServiceImpl service;

    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials()); // No crypting. Use SslServerCredentials  for sequre connection

    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "========================================" << std::endl;
    std::cout << " gRPC motor server started. " << std::endl;
    std::cout << " waiting for connecting to port [50051] ... " << std::endl;
    std::cout << " For finishing, close this window " << std::endl;
    std::cout << " or stop this program. " << std::endl;
    std::cout << "========================================" << std::endl;

    server->Wait();
}

int main()
{
    RunServer();
    return 0;
}
