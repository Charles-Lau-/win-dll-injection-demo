#include"stdafx.h"
#include "DuoBiPage.h"
#include <string> 
#include <cstdio>
#include <iostream>



void DuoBiPage::ButtonClicked(Object ^sender, RoutedEventArgs ^args) {
	MyApplicationEventArgs^ myargs = gcnew MyApplicationEventArgs();
	Boolean send = false;
	if (sender == this->closeButton) {
		myargs->Actor = "panel";
		myargs->Verb = "close";
		myargs->Target = "duobi_panel";
		send = true;
	}
	//TODO: validate input data
	//bool okClicked = true;
	//System::Windows::MessageBox::Show("button click event happened");
	//OnButtonClicked(this, gcnew MyPageEventArgs(okClicked));
	if (send) {
		if (this->excludeButtonClicked)
			this->excludeButtonClicked = false;
		else {

			OnButtonClicked(this, myargs);
		}
	}
};



void DuoBiPage::GridMouseMove(Object ^sender, MouseEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		if (this->container->IndexOf(sender) > 0) {
			if (pos.X != this->mousePrePosition.X && pos.Y != this->mousePrePosition.Y)
				this->excludeButtonClicked = true;
		}


		OnGridMoved(this, gcnew PanelMoveEventArgs("duobi_panel",
			gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y))
		);
	}
}

void DuoBiPage::GridMouseUp(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Released && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		OnGridMoved(this, gcnew PanelMoveEventArgs("duobi_panel",
			gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y))
		);
	}

}

void DuoBiPage::GridMouseDown(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed) {
		this->isBeingPressed = true;
		this->mousePrePosition = args->GetPosition(this);
	}
}



DuoBiPage::DuoBiPage() {
	int rows = 10;
	int column = 10;
	array<ColumnDefinition ^> ^ columnDef = gcnew array<ColumnDefinition ^>(column);
	array<RowDefinition ^> ^ rowDef = gcnew array<RowDefinition ^>(rows);
	this->container = gcnew System::Collections::ArrayList();
	this->excludeButtonClicked = false;
	this->Background = gcnew SolidColorBrush(Colors::Black);
	//this->Margin = Thickness(10, 0, 0, 10);
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
	//Add the first row title
	title = CreateLabel(0, 0, "多币平仓管理模块");
	Grid::SetColumnSpan(title, 9);
	title->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
	title->VerticalAlignment = System::Windows::VerticalAlignment::Center;
	title->Margin = Thickness(3);

	closeButton = CreateButton(9, 0, "X");
	closeButton->Background = Brushes::Red;
	closeButton->VerticalAlignment = System::Windows::VerticalAlignment::Center;
	closeButton->HorizontalAlignment = System::Windows::HorizontalAlignment::Right;
	title->Margin = Thickness(3);


	num = CreateCell(0, 1, "编号");
	num->Margin = Thickness(5, 0, 0, 5);
	symbol = CreateCell(1, 1, "商品名称");
	point = CreateCell(2, 1, "点差");
	sell = CreateCell(3,1, "Sell");
	sellLimit = CreateCell(4, 1, "SellLimit");
	sellStop = CreateCell(5, 1, "SellStop");
	buy = CreateCell(6, 1, "Buy");
	buylimit = CreateCell(7, 1, "BuyLimit");
	buystop = CreateCell(8, 1 , "BuyStop");
	profit = CreateCell(9, 1, "浮动利润");
	profit->Margin = Thickness(0, 0, 5, 5);


	this->closeButton->Click += gcnew RoutedEventHandler(this, &DuoBiPage::ButtonClicked);

	this->container->Add(title);
	this->container->Add(closeButton);
	this->container->Add(num);
	this->container->Add(symbol);
	this->container->Add(point);
	this->container->Add(sell);
	this->container->Add(sellLimit);
	this->container->Add(sellStop);
	this->container->Add(buy);
	this->container->Add(buylimit);
	this->container->Add(buystop);
	this->container->Add(profit);


	//handle move grid event
	this->isBeingPressed = false;
	this->IsHitTestVisible = true;
	this->MouseDown += gcnew  MouseButtonEventHandler(this, &DuoBiPage::GridMouseDown);
	this->MouseUp += gcnew MouseButtonEventHandler(this, &DuoBiPage::GridMouseUp);
	this->MouseMove += gcnew MouseEventHandler(this, &DuoBiPage::GridMouseMove);


	for (int i = 0; i < this->container->Count; i++) {
		UIElement^ ele = static_cast<UIElement^>(this->container[i]);
		ele->PreviewMouseDown += gcnew  MouseButtonEventHandler(this, &DuoBiPage::GridMouseDown);
		ele->PreviewMouseUp += gcnew MouseButtonEventHandler(this, &DuoBiPage::GridMouseUp);
		ele->PreviewMouseMove += gcnew MouseEventHandler(this, &DuoBiPage::GridMouseMove);
	}
}






Button ^DuoBiPage::CreateButton(int column, int row, String ^ text)
{
	Button ^newButton = gcnew Button();
	newButton->Content = text;
	//newButton->Margin = Thickness(1,0.5,1,0.5);
	newButton->Foreground = Brushes::White;
	//newButton->Height = 30;
	Grid::SetColumn(newButton, column);
	Grid::SetRow(newButton, row);
	Grid::SetColumnSpan(newButton, 5);
	newButton->Margin = Thickness(2, 0, 2, 10);
	newButton->Background = Brushes::Gray;
	//newButton->Style = Style->F
	this->Children->Add(newButton);
	return newButton;
}





Label ^DuoBiPage::CreateCell(int column, int row, String ^ text) {
	Label ^ newLabel = gcnew Label();
	newLabel->Content = text;
	newLabel->Foreground = Brushes::White;
	newLabel->FontWeight = FontWeights::Normal;
	newLabel->FontSize = 12;
	newLabel->BorderThickness = Thickness(1);
	newLabel->BorderBrush = Brushes::White;
	newLabel->Margin = Thickness(0, 0, 0, 5);
	newLabel->Background = Brushes::BlueViolet;
	Grid::SetColumn(newLabel, column);
	Grid::SetRow(newLabel, row);
	this->Children->Add(newLabel);
	return newLabel;
}
