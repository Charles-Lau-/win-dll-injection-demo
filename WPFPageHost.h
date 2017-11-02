#pragma once
#include "WPFPage.h"

public ref class WPFPageHost
{

private: 

public:
	WPFPageHost(){};
	//initial property settings
	//initial property settings
	static System::Windows::Media::Brush^ initBackBrush;
	static System::Windows::Media::Brush^ initForeBrush;
	static System::Windows::Media::FontFamily^ initFontFamily;
	static System::Windows::FontStyle initFontStyle;
	static System::Windows::FontWeight initFontWeight;
	static double initFontSize;
	static WPFPage^ hostedPage;
};
