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
using namespace System::Windows::Shapes;


public ref class PanelMoveEventArgs :EventArgs {
private:
	String^ actor;
	Point^ p; 
public:
	PanelMoveEventArgs(String^ actor, Point^ p) { this->actor = actor; this->p = p; };

	property String^ Actor {
		String^ get() { return this->actor; }
		void set(String^ value) { this->actor = value; }
	}

	property Point^ Location {
		Point^ get() { return this->p;}
		void set(Point^ value) { this->p = value;}
	}
};
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

public ref class WPFPage :Grid {
public:
	delegate void ButtonClickHandler(Object ^, MyApplicationEventArgs^);
	delegate void GridMoveHandler(Object ^, PanelMoveEventArgs ^);
	WPFPage() {}
	event ButtonClickHandler ^OnButtonClicked;
	event GridMoveHandler ^OnGridMoved;
	property FontFamily^ DefaultFontFamily
	{
		FontFamily^ get() { return _defaultFontFamily; }
		void set(FontFamily^ value) { SetFontFamily(value); }
	};
	Label ^CreateLabel(int column, int row, String ^ text);
	TextBox ^CreateTextBox(int column, int row, String^ text);
	Button ^CreateButton(int column, int row, String ^ text);
	//draw a line
	Border ^CreateBorder(int column, int row, Color color, int thickness);

	CheckBox^ CreateCheckBox(int column, int row);



	void SetFontFamily(FontFamily^ newFontFamily);

protected:

	System::Collections::ArrayList^  container;
	//record the position before moving the grid;maintain the status of being pressed; exclude button click event from move event
	Point mousePrePosition;
	Boolean isBeingPressed;
	Boolean excludeButtonClicked;

	FontFamily^ _defaultFontFamily;

};


