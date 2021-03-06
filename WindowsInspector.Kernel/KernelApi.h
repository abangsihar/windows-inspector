#pragma once
#include <ntifs.h>

#define THREAD_QUERY_INFORMATION 0x40

typedef NTSTATUS(NTAPI * ZwQueryInformationThreadFunc)(
	_In_ HANDLE ThreadHandle,
	_In_ THREADINFOCLASS ThreadInformationClass,
	_Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
	_In_ ULONG ThreadInformationLength,
	_Out_opt_ PULONG ReturnLength
	);

extern ZwQueryInformationThreadFunc ZwQueryInformationThread;

NTSTATUS 
KernelApiInitialize(
    VOID
    );

NTSTATUS 
GetCurrentProcessHandle(
    __out PHANDLE ProcessHandle
    );

NTSTATUS
GetProcessHandleById(
    __in ULONG ProcessId,
    __out PHANDLE ProcessHandle
    );


FORCEINLINE
ULONG
GetProcessId(
	PVOID ProcessObject
	)
{
	return HandleToUlong(PsGetProcessId((PEPROCESS)ProcessObject));
}

FORCEINLINE
ULONG
GetThreadId(
	PVOID ThreadObject
	)
{
	return HandleToUlong(PsGetThreadId((PETHREAD)ThreadObject));
}

FORCEINLINE
VOID
UnlockFreeMdl(
	PMDL Mdl
	)
{
	MmUnlockPages(Mdl);
	IoFreeMdl(Mdl);
}

NTSTATUS
MapUserModeAddressToSystemSpace(
	__in PVOID Buffer,
	__in ULONG Length,
	__in LOCK_OPERATION Operation,
	__out PMDL* OutputMdl,
	__out PVOID* MappedBuffer
);
