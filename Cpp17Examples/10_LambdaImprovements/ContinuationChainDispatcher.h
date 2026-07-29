#pragma once
#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <type_traits>
#include <memory>
#include <utility>
#include <exception>

namespace LambdaImprovements
{
	template <typename F, typename T, bool acceptsPrev>
	struct NextTypeSelector;

	template <typename F, typename T>
	struct NextTypeSelector<F, T, true> {
		using type = std::invoke_result_t<F, T>;
	};

	template <typename F, typename T>
	struct NextTypeSelector<F, T, false> {
		using type = std::invoke_result_t<F>;
	};

	// ChainNode
	template<typename T>
	class ChainNode;

	// ContinuationChainDispatcher
	class ContinuationChainDispatcher
	{
	public:
		template<typename F, typename... Args>
		static auto submit(F&& f, Args&&... args)
		{
			using ReturnType = std::invoke_result_t<F, Args...>;
			auto bound = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
			auto taskPtr = std::make_shared<std::packaged_task<ReturnType()>>(std::move(bound));
			auto future = taskPtr->get_future();

			std::thread([taskPtr]()
				{
					try
					{
						(*taskPtr)();
					}
					catch (...)
					{
						// Handle exceptions if necessary
					}
				}).detach();
			return ChainNode<ReturnType>(std::move(future));
		}
	};

	// General ChainNode
	template<typename T>
	class ChainNode
	{
	public:
		explicit ChainNode(std::future<T>&& fut) : m_sharedFuture(fut.share()) {}
		T get() { return m_sharedFuture.get(); }
		template<typename F>
		auto then(F&& f) { return thenImpl(std::forward<F>(f)); }
	private:
		std::shared_future<T> m_sharedFuture;

		template<typename F>
		auto thenImpl(F&& f)
		{
			constexpr bool acceptsPrev = std::is_invocable_v<F, T>;
			constexpr bool acceptsNone = std::is_invocable_v<F>;

			static_assert(acceptsPrev || acceptsNone,
				"The provided function must accept either the previous result or no arguments.");

			using NextType = typename NextTypeSelector<F, T, acceptsPrev>::type;

			std::shared_ptr<std::packaged_task<NextType()>> packaged(
				new std::packaged_task<NextType()>(
					[sharedPrev = m_sharedFuture, func = std::forward<F>(f)]() mutable -> NextType
					{
						if constexpr (acceptsPrev)
						{
							if constexpr (std::is_void_v<T>)
							{
								sharedPrev.get();
								return func();
							}
							else
							{
								T prev = sharedPrev.get();
								return func(std::move(prev));
							}
						}
						else
						{
							sharedPrev.wait();
							return func();
						}
					}
				)
			);

			std::future<NextType> nextFuture = packaged->get_future();

			std::thread([packaged]()
				{
					try
					{
						(*packaged)();
					}
					catch (...)
					{
						// Handle exceptions if necessary
					}
				}
			).detach();

			return ChainNode<NextType>(std::move(nextFuture));
		}
	};

	// Specialization for void
	template<>
	class ChainNode<void>
	{
	public:
		explicit ChainNode(std::future<void>&& fut)
			: m_sharedFuture(fut.share()) { }

		void get() { m_sharedFuture.get(); }

		template<typename F>
		auto then(F&& f) { return thenImpl(std::forward<F>(f)); }

	private:
		std::shared_future<void> m_sharedFuture;

		template<typename F>
		auto thenImpl(F&& f)
		{
			static_assert(std::is_invocable_v<F>,
				"The provided function must be invocable with no arguments.");

			using NextType = std::invoke_result_t<F>;

			std::shared_ptr<std::packaged_task<NextType()>> packaged(
				new std::packaged_task<NextType()>(
					[sharedPrev = m_sharedFuture, func = std::forward<F>(f)]() mutable -> NextType
					{
						sharedPrev.get();
						return func();
					}
				)
			);

			std::future<NextType> nextFuture = packaged->get_future();

			std::thread([packaged]()
				{
					try
					{
						(*packaged)();
					}
					catch (...)
					{
						// Handle exceptions if necessary
					}
				}).detach();
			return ChainNode<NextType>(std::move(nextFuture));
		}
	};

}
