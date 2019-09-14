#pragma once
#include <Windows.h>
#include <memory>
#include <WindowsInspector.Kernel/Common.hpp>

struct HandleDeleter 
{
	void operator()(HANDLE value) 
	{ 
		if (value != NULL && value != INVALID_HANDLE_VALUE) 
		{
			CloseHandle(value);
		}
	}
};

using OwnedHandle = std::unique_ptr<std::remove_pointer<HANDLE>::type, HandleDeleter>;

class InspectorDriver 
{
	OwnedHandle hDriver;
public:

	InspectorDriver();
	InspectorDriver(OwnedHandle hDriver);

    CircularBuffer* Listen();
    void Stop();
};