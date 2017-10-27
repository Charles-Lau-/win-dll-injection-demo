#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Text;
using namespace System::Windows;
using namespace System::Runtime;
using namespace System::Windows::Controls;
using namespace System::Windows::Data;
using namespace System::Windows::Documents;
using namespace System::Windows::Media;
using namespace System::Windows::Media::Imaging;

public ref class MyPageEventArgs :EventArgs {
private:
	bool data;
public:
	MyPageEventArgs(bool data) {
		data = data;
	};
	property bool IsOK {
		bool get() { return data; }
	};
};

public ref class WPFPage:Grid {
public:
	delegate void ButtonClickHandler(Object ^, MyPageEventArgs ^);
	WPFPage() {};
	WPFPage(int height, int width);
	event ButtonClickHandler ^OnButtonClicked;
	property FontFamily^ DefaultFontFamily
	{
		FontFamily^ get() { return _defaultFontFamily; }
		void set(FontFamily^ value) { SetFontFamily(value); }
	};
	Label ^WPFPage::CreateLabel(int column, int row, String ^ text);
	TextBox ^WPFPage::CreateTextBox(int column, int row, int span);
	Button ^WPFPage::CreateButton(int column, int row, String ^ text);

	void WPFPage::ButtonClicked(Object ^sender, RoutedEventArgs ^args);
	void WPFPage::SetFontFamily(FontFamily^ newFontFamily);


	String^ EnteredName;
	String^ EnteredAddress;
	String^ EnteredCity;
	String^ EnteredZip;
	String^ EnteredState;

	Label^ titleText;
	Label^ nameLabel;
	TextBox^ nameTextBox;
	Label^ addressLabel;
	TextBox^ addressTextBox;
	Label^ cityLabel;
	TextBox^ cityTextBox;
	Label^ stateLabel;
	TextBox^ stateTextBox;



private:
	

	Button^ okButton;
	Button^ cancelButton;

	FontFamily^ _defaultFontFamily;

}; 

