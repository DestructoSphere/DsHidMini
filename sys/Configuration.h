#pragma once

typedef struct _DEVICE_CONTEXT *PDEVICE_CONTEXT;

_Must_inspect_result_
NTSTATUS
ConfigLoadForDevice(
	_Inout_ PDEVICE_CONTEXT Context
);