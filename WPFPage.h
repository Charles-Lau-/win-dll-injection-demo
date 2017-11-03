#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Text;
using namespace System::Windows;
using namespace System::Runtime;
using namespace System::Windows::Controls;
using namespace System::Windows::Data;
using namespace System::Windows::Input;
using namespace System::Windows::Documents;
using namespace System::Windows::Media;
using namespace System::Windows::Media::Imaging;

public ref class MyApplicationEventArgs:EventArgs {
private:
	String^ actor;
	String^ verb;
	String^ target;
public:
	MyApplicationEventArgs(String^ actor) { this->actor = actor; };
	MyApplicationEventArgs(String^ actor, String^ verb) { this->verb = verb; this->actor = actor;};
	MyApplicationEventArgs(String^ actor, String^ verb, String^ target) { this->actor = actor; this->verb = verb; this->target = target; };
	MyApplicationEventArgs() {};

	property String^ Actor {
		String^ get() { return this->actor; }
		void set(String^ value) { this->actor = value; }
	}

	property String^ Verb {
		String^ get() { return this->verb; }
		void set(String^ value) { this->verb = value; }
	}

	property String^ Target {
		String^ get() { return this->target; }
		void set(String^ value) { this->target = value; }
	}
};


public ref class WPFPage:Grid {
public:
	delegate void ButtonClickHandler(Object ^, MyApplicationEventArgs^);
	delegate void GridMoveHandler(Object ^, Point ^);
	WPFPage() {};
	WPFPage(int height, int width);
	event ButtonClickHandler ^OnButtonClicked;
	event GridMoveHandler ^OnGridMoved;
	property FontFamily^ DefaultFontFamily
	{
		FontFamily^ get() { return _defaultFontFamily; }
		void set(FontFamily^ value) { SetFontFamily(value); }
	};
	Label ^WPFPage::CreateLabel(int column, int row, String ^ text);
	TextBox ^WPFPage::CreateTextBox(int column, int row, String^ text);
	Button ^WPFPage::CreateButton(int column, int row, String ^ text);

	
	void WPFPage::ButtonClicked(Object ^sender, RoutedEventArgs ^args);
	//for move of the window
	void WPFPage::GridMouseMove(Object ^sender, MouseEventArgs^ args);
	void WPFPage::SetFontFamily(FontFamily^ newFontFamily);
	void WPFPage::GridMouseDown(Object ^sender, MouseButtonEventArgs^ args);
	void WPFPage::GridMouseUp(Object ^sender, MouseButtonEventArgs^ args);




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
	
	System::Collections::ArrayList^  container;
	//record the position before moving the grid;maintain the status of being pressed; exclude button click event from move event
	Point mousePrePosition;
	Boolean isBeingPressed;
	Boolean excludeButtonClicked;

	Button^ hiddenButton;
	Button^ advanceButton;
	Button^ configureButton;
	Button^ pingchangButton;
	Button^ qingchangButton;
	Button^ duisuoButton;
	Button^ quansuoButton;

	Button^ sellButton;
	Button^ convenientButton1;
	Button^ convenientButton2;
	Button^ convenientButton3;
	Button^ convenientButton4;
	TextBox^ lotsButton5;
	Button^ buyButton;

	Button^ deleteStopButton;
	Button^ stopButton;
	TextBox^ stopLevelInput;
	Button^ pointButton;
	TextBox^ profitLevelInput;
	Button^ profitButton;
	Button^ deleteProfitButton;

	FontFamily^ _defaultFontFamily;

}; 

