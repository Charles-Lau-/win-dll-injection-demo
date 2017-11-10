#include"stdafx.h"
#include "WPFPage.h"
#include <string> 
#include <cstdio>
#include <iostream>


Label ^WPFPage::CreateLabel(int column, int row, String ^ text)
{
	Label ^ newLabel = gcnew Label();
	newLabel->Content = text;
	newLabel->Foreground = Brushes::White;
	newLabel->FontWeight = FontWeights::Normal;
	newLabel->FontSize = 12;
	Grid::SetColumn(newLabel, column);
	Grid::SetRow(newLabel, row);
	this->Children->Add(newLabel);
	return newLabel;
}
TextBox ^WPFPage::CreateTextBox(int column, int row, String^ text)
{
	TextBox ^newTextBox = gcnew TextBox();
	newTextBox->Margin = Thickness(0, 0, 0, 0);
	newTextBox->Text = text;
	newTextBox->TextAlignment = TextAlignment::Center;
	newTextBox->Foreground = Brushes::White;
	Grid::SetColumn(newTextBox, column);
	Grid::SetRow(newTextBox, row);
	this->Children->Add(newTextBox);
	return newTextBox;
}

Border ^WPFPage::CreateBorder(int column, int row, Color color, int thickness) {
	Border^ border = gcnew Border();
	Grid::SetColumn(border, column);
	Grid::SetRow(border, row);

	border->BorderBrush = gcnew SolidColorBrush(color);
	border->BorderThickness = Thickness(thickness);
	border->VerticalAlignment = System::Windows::VerticalAlignment::Bottom;
	border->Margin = Thickness(0, 10, 0, 5);
	Grid::SetColumn(border, column);
	Grid::SetRow(border, row);
	this->Children->Add(border);
	return border;
	
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


CheckBox^ WPFPage::CreateCheckBox(int column, int row) {
	CheckBox^ newbox = gcnew CheckBox();
	Grid::SetColumn(newbox, column);
	Grid::SetRow(newbox, row);
	this->Children->Add(newbox);
	return newbox;
}


void WPFPage::SetFontFamily(FontFamily^ newFontFamily)
{
	_defaultFontFamily = newFontFamily;
}

