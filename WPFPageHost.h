#pragma once
#include "MainPage.h"
#include "ShouDongPage.h"

public ref class MainPageHost {
private: 
public:
	MainPageHost(){};
	//initial property settings
	//initial property settings
	static System::Windows::Media::Brush^ initBackBrush;
	static System::Windows::Media::Brush^ initForeBrush;
	static System::Windows::Media::FontFamily^ initFontFamily;
	static System::Windows::FontStyle initFontStyle;
	static System::Windows::FontWeight initFontWeight;
	static double initFontSize;
	static MainPage^ hostedPage;
};


public ref class ShouDongPageHost {
private:
public:
	ShouDongPageHost(){};
	//initial property settings
	//initial property settings
	static System::Windows::Media::Brush^ initBackBrush;
	static System::Windows::Media::Brush^ initForeBrush;
	static System::Windows::Media::FontFamily^ initFontFamily;
	static System::Windows::FontStyle initFontStyle;
	static System::Windows::FontWeight initFontWeight;
	static double initFontSize;
	static ShouDongPage^ hostedPage;
};

