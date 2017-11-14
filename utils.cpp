#pragma once
#include "stdafx.h"
#include "utils.h"

LPCSTR StringToLPCSTR(String^ s) {
	return (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
}

void MarshalString(String^ s, std::string& os) {
	const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}
