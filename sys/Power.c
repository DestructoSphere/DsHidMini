#include "Driver.h"
#include "Power.tmh"


//
// Start Bluetooth communication here
// 
_Use_decl_annotations_

NTSTATUS
DsHidMini_EvtWdfDeviceSelfManagedIoInit(
	WDFDEVICE Device
)
{
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_CONTEXT pDevCtx;
	WDF_DEVICE_PROPERTY_DATA propertyData;

	PAGED_CODE();

	FuncEntry(TRACE_POWER);

	pDevCtx = DeviceGetContext(Device);

	if (pDevCtx->ConnectionType == DsDeviceConnectionTypeBth)
	{
		status = DsBth_SelfManagedIoInit(Device);
	}

	FuncExit(TRACE_POWER, "status=%!STATUS!", status);

	return status;
}

//
// Stop Bluetooth communication here
// 
NTSTATUS
DsHidMini_EvtWdfDeviceSelfManagedIoSuspend(
	WDFDEVICE Device
)
{
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_CONTEXT pDevCtx = DeviceGetContext(Device);

	FuncEntry(TRACE_POWER);

	if (pDevCtx->ConnectionType == DsDeviceConnectionTypeBth)
	{
		status = DsBth_SelfManagedIoSuspend(Device);
	}

	FuncExit(TRACE_POWER, "status=%!STATUS!", status);

	return status;
}

//
// Initialize USB communication here
// 
_Use_decl_annotations_
NTSTATUS
DsHidMini_EvtDevicePrepareHardware(
	WDFDEVICE  Device,
	WDFCMRESLIST  ResourcesRaw,
	WDFCMRESLIST  ResourcesTranslated
)
{
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_CONTEXT pDevCtx;
		
	UNREFERENCED_PARAMETER(ResourcesRaw);
	UNREFERENCED_PARAMETER(ResourcesTranslated);

	FuncEntry(TRACE_POWER);

	pDevCtx = DeviceGetContext(Device);

	//
	// Read common properties (can be refreshed by power-cycling)
	// 
	DsDevice_ReadConfiguration(Device);

	//
	// Initialize USB
	// 
	if (pDevCtx->ConnectionType == DsDeviceConnectionTypeUsb)
	{
		status = DsUdb_PrepareHardware(Device);

		if (NT_SUCCESS(status))
		{
			DsDevice_RegisterHotReloadListener(pDevCtx);
		}
	}

	FuncExit(TRACE_POWER, "status=%!STATUS!", status);

	return status;
}

//
// Power up
// 
NTSTATUS DsHidMini_EvtDeviceD0Entry(
	_In_ WDFDEVICE              Device,
	_In_ WDF_POWER_DEVICE_STATE PreviousState
)
{
	PDEVICE_CONTEXT pDevCtx;
	NTSTATUS status = STATUS_SUCCESS;

	pDevCtx = DeviceGetContext(Device);

	FuncEntry(TRACE_POWER);

	if (pDevCtx->ConnectionType == DsDeviceConnectionTypeUsb)
	{
		status = DsUsb_D0Entry(Device);
	}

	if (pDevCtx->ConnectionType == DsDeviceConnectionTypeBth)
	{
		status = DsBth_D0Entry(Device, PreviousState);
	}
	
	//
	// Start processing received output report packets
	//
	DMF_ThreadedBufferQueue_Start(pDevCtx->OutputReport.Worker);
	
	FuncExit(TRACE_POWER, "status=%!STATUS!", status);

	return status;
}

//
// Power down
// 
NTSTATUS DsHidMini_EvtDeviceD0Exit(
	_In_ WDFDEVICE Device,
	_In_ WDF_POWER_DEVICE_STATE TargetState
)
{
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_CONTEXT pDevCtx;

	UNREFERENCED_PARAMETER(TargetState);

	FuncEntry(TRACE_POWER);

	pDevCtx = DeviceGetContext(Device);

	//
	// Stop processing received output report packets
	//
	DMF_ThreadedBufferQueue_Stop(pDevCtx->OutputReport.Worker);

	if (pDevCtx->ConfigurationReloadWaitHandle)
	{
		UnregisterWait(pDevCtx->ConfigurationReloadWaitHandle);
		pDevCtx->ConfigurationReloadWaitHandle = NULL;
	}

	if (pDevCtx->ConfigurationReloadEvent)
	{
		CloseHandle(pDevCtx->ConfigurationReloadEvent);
		pDevCtx->ConfigurationReloadEvent = NULL;
	}

	if (pDevCtx->ConnectionType == DsDeviceConnectionTypeUsb)
	{
		status = DsUdb_D0Exit(Device);
	}

	if (pDevCtx->ConnectionType == DsDeviceConnectionTypeBth)
	{
		WdfIoTargetPurge(
			pDevCtx->Connection.Bth.HidInterrupt.InputStreamerIoTarget,
			WdfIoTargetPurgeIoAndWait
		);
		WdfIoTargetPurge(
			pDevCtx->Connection.Bth.HidControl.OutputWriterIoTarget,
			WdfIoTargetPurgeIoAndWait
		);
	}

	FuncExit(TRACE_POWER, "status=%!STATUS!", status);

	return status;
}
