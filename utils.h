#pragma once
#include "stdafx.h"
#include <string>

using System::String;


LPCSTR StringToLPCSTR(String^ s);
void MarshalString(String^ s, std::string& os);

