#pragma once
#include <atomic>
#include <memory>

namespace CancelToken
{
	class CancelToken
	{
	public:
		CancelToken()
			: m_cancelled(std::make_shared<std::atomic<bool>>(false)) {}
		CancelToken(const CancelToken&) = default;
		CancelToken& operator=(const CancelToken&) = default;
		void cancel() noexcept { m_cancelled->store(true, std::memory_order_relaxed); }
		bool isCancelled() const noexcept { return m_cancelled->load(std::memory_order_relaxed); }

	private:
		std::shared_ptr<std::atomic<bool>> m_cancelled;
	};
}
