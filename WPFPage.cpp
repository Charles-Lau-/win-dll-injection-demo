#include"stdafx.h"
#include "WPFPage.h"
#include <string> 
#include <cstdio>
#include <iostream>

void WPFPage::GridMouseMove(Object ^sender, MouseEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		OnGridMoved(this, gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y));
	}
}

void WPFPage::GridMouseUp(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Released && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		OnGridMoved(this, gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y));
		this->isBeingPressed = false;
	}
}

void WPFPage::GridMouseDown(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed) {
		this->isBeingPressed = true;
		this->mousePrePosition = args->GetPosition(this);
	}
}

WPFPage::WPFPage(int allottedWidth, int allotedHeight)
{
	int rows = 5;
	int column = 8;
	array<ColumnDefinition ^> ^ columnDef = gcnew array<ColumnDefinition ^>(column);
	array<RowDefinition ^> ^ rowDef = gcnew array<RowDefinition ^>(rows);

	this->Height = allotedHeight;
	this->Width = allottedWidth;
	this->Background = gcnew SolidColorBrush(Colors::Black);

	//Set up the Grid's row and column definitions
	for (int i = 0; i < column; i++)
	{
		columnDef[i] = gcnew ColumnDefinition();
		columnDef[i]->Width = GridLength(1, GridUnitType::Auto);
		this->ColumnDefinitions->Add(columnDef[i]);
	}
	for (int i = 0; i < rows; i++)
	{
		rowDef[i] = gcnew RowDefinition();
		rowDef[i]->Height = GridLength(1, GridUnitType::Auto);
		this->RowDefinitions->Add(rowDef[i]);
	}
	//Add the first rowbutton
	hiddenButton = CreateButton(0, 0, "hid");
	hiddenButton->Background = gcnew SolidColorBrush(Colors::Yellow);
	advanceButton = CreateButton(1, 0, "adv");
	advanceButton->Background = gcnew SolidColorBrush(Colors::Blue);
	configureButton = CreateButton(2, 0, "config");
	configureButton->Background = gcnew SolidColorBrush(Colors::Green);
	pingchangButton = CreateButton(3, 0, "平仓");
	qingchangButton = CreateButton(4, 0, "清仓");
	duisuoButton = CreateButton(5, 0, "对锁");
	quansuoButton = CreateButton(6, 0, "全锁");
	CreateButton(7, 0, "abc");
	pingchangButton->Background = gcnew SolidColorBrush(Colors::Gray);
	qingchangButton->Background = gcnew SolidColorBrush(Colors::Gray);
	duisuoButton->Background = gcnew SolidColorBrush(Colors::Gray);
	quansuoButton->Background = gcnew SolidColorBrush(Colors::Gray);
	//add the second row button
	sellButton = CreateButton(0, 1, "SELL");
	sellButton->Background = gcnew SolidColorBrush(Colors::Red);
	convenientButton1 = CreateButton(3, 1, "0.01");
	convenientButton2 = CreateButton(4, 1, "0.10");
	convenientButton3 = CreateButton(3, 2, "0.50");
	convenientButton4 = CreateButton(4, 2, "1.00");
	convenientButton1->Background = gcnew SolidColorBrush(Colors::Gray);
	convenientButton2->Background = gcnew SolidColorBrush(Colors::Gray);
	convenientButton3->Background = gcnew SolidColorBrush(Colors::Gray);
	convenientButton4->Background = gcnew SolidColorBrush(Colors::Gray);
	lotsButton5 = CreateTextBox(3, 3, "0.50");
	lotsButton5->Background = gcnew SolidColorBrush(Colors::Pink);
	buyButton = CreateButton(5, 1, "BUY");
	buyButton->Background = gcnew SolidColorBrush(Colors::Red);

	Grid::SetRowSpan(sellButton, 3);
	Grid::SetRowSpan(buyButton, 3);

	Grid::SetColumnSpan(buyButton, 3);
	Grid::SetColumnSpan(sellButton, 3);
	Grid::SetColumnSpan(lotsButton5, 2);

	//add the last row
	deleteStopButton = CreateButton(0, 4, "删");
	deleteStopButton->Background = gcnew SolidColorBrush(Colors::Gray);
	stopButton = CreateButton(1, 4, "无");
	stopButton->Background = gcnew SolidColorBrush(Colors::Pink);
	stopLevelInput = CreateTextBox(2, 4, "500");
	stopLevelInput->Background = gcnew SolidColorBrush(Colors::Pink);
	profitLevelInput = CreateTextBox(4, 4, "500");
	profitLevelInput->Background = gcnew SolidColorBrush(Colors::Pink);
	profitButton = CreateButton(6, 4, "有");
	profitButton->Background = gcnew SolidColorBrush(Colors::Pink);
	deleteProfitButton = CreateButton(7, 4, "删");
	deleteProfitButton->Background = gcnew SolidColorBrush(Colors::Gray);




	Grid::SetColumnSpan(stopLevelInput, 2);
	Grid::SetColumnSpan(profitLevelInput, 2);

	//handle move grid event
	this->isBeingPressed = false;
	this->IsHitTestVisible = true;
	this->MouseDown += gcnew  MouseButtonEventHandler(this, &WPFPage::GridMouseDown);
	this->MouseUp += gcnew MouseButtonEventHandler(this, &WPFPage::GridMouseUp);
	this->MouseMove += gcnew MouseEventHandler(this, &WPFPage::GridMouseMove);

	//handle button click
	hiddenButton->Click += gcnew RoutedEventHandler(this, &WPFPage::ButtonClicked);
	//cancelButton->Click += gcnew RoutedEventHandler(this, &WPFPage::ButtonClicked);
}

Label ^WPFPage::CreateLabel(int column, int row, String ^ text)
{
	Label ^ newLabel = gcnew Label();
	newLabel->Content = text;
	newLabel->Margin = Thickness(10, 5, 10, 0);
	newLabel->FontWeight = FontWeights::Normal;
	newLabel->FontSize = 12;
	Grid::SetColumn(newLabel, column);
	Grid::SetRow(newLabel, row);
	return newLabel;
}
TextBox ^WPFPage::CreateTextBox(int column, int row, String^ text)
{
	TextBox ^newTextBox = gcnew TextBox();
	//newTextBox->Margin = Thickness(10, 5, 10, 0);
	newTextBox->Text = text;
	newTextBox->TextAlignment = TextAlignment::Center;
	newTextBox->Foreground = Brushes::White;
	Grid::SetColumn(newTextBox, column);
	Grid::SetRow(newTextBox, row);
	this->Children->Add(newTextBox);
	return newTextBox;
}

Button ^WPFPage::CreateButton(int column, int row, String ^ text)
{
	Button ^newButton = gcnew Button();
	newButton->Content = text;
	//newButton->Margin = Thickness(1,0.5,1,0.5);
	newButton->Foreground = Brushes::White;
	//newButton->Height = 30;
	Grid::SetColumn(newButton, column);
	Grid::SetRow(newButton, row);
	//newButton->Style = Style->F
	this->Children->Add(newButton);
	return newButton;
}

void WPFPage::ButtonClicked(Object ^sender, RoutedEventArgs ^args)
{

	//TODO: validate input data
	bool okClicked = true;
	System::Windows::MessageBox::Show("button click event happened");
	//OnButtonClicked(this, gcnew MyPageEventArgs(okClicked));
}


void WPFPage::SetFontFamily(FontFamily^ newFontFamily)
{

	_defaultFontFamily = newFontFamily;
	titleText->FontFamily = newFontFamily;
	nameLabel->FontFamily = newFontFamily;
	addressLabel->FontFamily = newFontFamily;
	cityLabel->FontFamily = newFontFamily;
	stateLabel->FontFamily = newFontFamily;
}

