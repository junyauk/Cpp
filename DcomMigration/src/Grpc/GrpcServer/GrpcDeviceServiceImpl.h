#pragma once
#include "..\..\Shared\device.grpc.pb.h"
#include <mutex>
#include <string>

// Difference between DCOM and gRPC
// - use std::string, instead of BSTR
// - return ::grpc::Status::OK, instead of HRESULT

class GrpcDeviceServiceImpl final : public dcom_migration::GrpcDeviceService::Service
{
public:
	GrpcDeviceServiceImpl()
		: m_currentSpeed(0.0)
		, m_targetSpeed(0.0)
		, m_temperature(25.0)
		, m_isFaulted(false)
		, m_faultCode("NONE") {}

	::grpc::Status GetState(
		::grpc::ServerContext* context,
		const ::dcom_migration::Empty* request,
		::dcom_migration::MotorState* response) override
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (m_currentSpeed < m_targetSpeed) m_currentSpeed += 50.0;
		if (m_currentSpeed > m_targetSpeed) m_currentSpeed -= 50.0;

		response->set_current_speed(m_currentSpeed);
		response->set_target_speed(m_targetSpeed);
		response->set_temperature(m_temperature);
		response->set_is_faulted(m_isFaulted);
		response->set_fault_code(m_faultCode);

		return ::grpc::Status::OK;
	}

	::grpc::Status SetTargetSpeed(
		::grpc::ServerContext* context,
		const ::dcom_migration::TargetSpeedRequest* request,
		::dcom_migration::Empty* response) override
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		double speed = request->speed();
		if (speed < 0 || speed > 3000)
		{
			m_isFaulted = true;
			m_faultCode = "ERROR_OVER_SPEED";
			return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Speed must be between 0 and 3000");
		}

		m_targetSpeed = speed;
		return ::grpc::Status::OK;
	}

	::grpc::Status Start(
		::grpc::ServerContext* context,
		const ::dcom_migration::Empty* request,
		::dcom_migration::ActionResponse* response) override
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (m_isFaulted)
		{
			response->set_success(false);
			return ::grpc::Status::OK;
		}

		m_targetSpeed = 1500.0;
		response->set_success(true);
		return ::grpc::Status::OK;
	}

	::grpc::Status Stop(
		::grpc::ServerContext* context,
		const ::dcom_migration::Empty* request,
		::dcom_migration::ActionResponse* response) override
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_targetSpeed = 0.0;
		response->set_success(true);
		return ::grpc::Status::OK;
	}

	::grpc::Status ResetAlarm(
		::grpc::ServerContext* context,
		const ::dcom_migration::Empty* request,
		::dcom_migration::Empty* response) override
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_isFaulted = false;
		m_faultCode = "NONE";
		return ::grpc::Status::OK;
	}

private:
	std::mutex m_mutex;

	double m_currentSpeed;
	double m_targetSpeed;
	double m_temperature;
	bool m_isFaulted;
	std::string m_faultCode;
};


