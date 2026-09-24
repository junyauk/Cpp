#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <span>
#include <memory>


namespace Ex05_ThreadPool_IO
{
	class ScopedHandle
	{
	public:
		explicit ScopedHandle(HANDLE handle = INVALID_HANDLE_VALUE) : m_handle(handle) {}
		~ScopedHandle()
		{
			if (isValid())
			{
				CloseHandle(m_handle);
				m_handle = INVALID_HANDLE_VALUE;
			}
		}
		// Copy (delete copy constructor and assignment operator)
		ScopedHandle(const ScopedHandle&) = delete;
		ScopedHandle& operator=(const ScopedHandle&) = delete;

		// Move (implement move constructor and assignment operator)
		ScopedHandle(ScopedHandle&& other) noexcept : m_handle(other.m_handle)
		{
			other.m_handle = INVALID_HANDLE_VALUE;
		}
		ScopedHandle& operator=(ScopedHandle&& other) noexcept
		{
			if (this != &other)
			{
				close();
				m_handle = other.m_handle;
				other.m_handle = INVALID_HANDLE_VALUE;
			}
			return *this;
		}

		HANDLE get() const { return m_handle; }
		BOOL close()
		{
			BOOL result = TRUE;
			if (isValid())
			{
				result = CloseHandle(m_handle);
				m_handle = INVALID_HANDLE_VALUE;
			}
			return result;
		}
		BOOL reset(HANDLE handle)
		{
			BOOL result = close();
			m_handle = handle;
			return result;
		}
		HANDLE release()
		{
			HANDLE temp = m_handle;
			m_handle = INVALID_HANDLE_VALUE;
			return temp;
		}
		explicit operator bool() const
		{
			return isValid();
		}
		
	private:
		BOOL isValid() const
		{
			return m_handle != nullptr && m_handle != INVALID_HANDLE_VALUE;
		}
		HANDLE m_handle;
	};
}
