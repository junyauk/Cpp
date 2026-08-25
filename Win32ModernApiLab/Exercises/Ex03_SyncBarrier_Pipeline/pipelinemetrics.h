#pragma once
#include <vector>
#include <chrono>

namespace Ex03_SyncBarrier_Pipeline
{
	template<typename T>
	class PipelineMetrics
	{
	public:
		void Reset()
		{
			m_durations.clear();
		}
		void RecordPhaseDuration(const T ns)
		{
			m_durations.push_back(ns);
		}
		T GetDuration(const size_t phase) const
		{
			if (phase >= m_durations.size())
			{
				return T{ 0 };
			}
			return m_durations[phase];
		}
		T GetTotal() const
		{
			T sum = T{ 0 };
			for (auto& d : m_durations)
			{
				sum += d;
			}
			return sum;
		}
	private:
		std::vector<T> m_durations;
	};
}
