#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX_DEPRECATION_WARNINGS
#pragma warning(disable: 4996)

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "..\..\Shared\device.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using dcom_migration::GrpcDeviceService;
using dcom_migration::MotorState;
using dcom_migration::Empty;
using dcom_migration::TargetSpeedRequest;
using dcom_migration::ActionResponse;

class GrpcDeviceClient {
private:
    // Connection stub for communicating with server
    std::unique_ptr<GrpcDeviceService::Stub> stub_;

public:
    // Receive th channel at constructor
    GrpcDeviceClient(std::shared_ptr<Channel> channel)
        : stub_(GrpcDeviceService::NewStub(channel)) {}

    // --- Start motor ---
    bool StartMotor() {
        Empty request;
        ActionResponse response;
        ClientContext context;

        // Call remote function of server
        Status status = stub_->Start(&context, request, &response);

        if (status.ok()) {
            return response.success();
        }
        else {
            std::cerr << "RPC error (Start): " << status.error_message() << std::endl;
            return false;
        }
    }

    // --- Get the status of motor and display ---
    void MonitorStatus(int times) {
        for (int i = 0; i < times; ++i) {
            Empty request;
            MotorState response;
            ClientContext context;

            Status status = stub_->GetState(&context, request, &response);

            if (status.ok()) {
                std::cout << " Times: " << (i + 1)
                    << " | Current spin speed: " << response.current_speed() << " rpm"
                    << " | Target spin speed: " << response.target_speed() << " rpm"
                    << " | Temperature: " << response.temperature() << " Celsius"
                    << " | Error: " << response.fault_code() << std::endl;
            }
            else {
                std::cerr << "RPC error (GetState): " << status.error_message() << std::endl;
            }

            // wait for 0.5 sec
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    // --- Stop motor ---
    bool StopMotor() {
        Empty request;
        ActionResponse response;
        ClientContext context;

        Status status = stub_->Stop(&context, request, &response);

        if (status.ok()) {
            return response.success();
        }
        else {
            std::cerr << "RPC error (Stop): " << status.error_message() << std::endl;
            return false;
        }
    }
};

int main(int argc, char** argv) {
    std::cout << "Starting gRPC client..." << std::endl;

    // 1. Create a communication channel by specifying the server's IP address and port (localhost, port 50051)
    // Specify "Insecure" (no encryption) for authentication, matching the server-side configuration.
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

    // Create an instance of client
    GrpcDeviceClient client(channel);

    std::cout << "Connecting to gRPC server..." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 2. Start motor
    std::cout << " Start the motor..." << std::endl;
    if (client.StartMotor()) {
        std::cout << "-> Received the motor start command." << std::endl;
    }

    // 3. Poling 5 times
    std::cout << "\n Monitoring the motor status (5 measurements):" << std::endl;
    client.MonitorStatus(5);

    // 4. Stop motor
    std::cout << "\n Stop motor..." << std::endl;
    if (client.StopMotor()) {
        std::cout << "-> Received motor stop command." << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "gRPC client finished." << std::endl;
    return 0;
}
