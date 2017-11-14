#include"stdafx.h"
#include "ShouDongPage.h"
#include <string> 
#include <cstdio>
#include <iostream>



void ShouDongPage::ButtonClicked(Object ^sender, RoutedEventArgs ^args) {
	MyApplicationEventArgs^ myargs = gcnew MyApplicationEventArgs();
	Boolean send = false;
	if (sender == this->pingAll) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingAll";
		send = true;
	}
	else if (sender == this->pingShort) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingShort";
		send = true;

	}
	else if (sender == this->pingLong) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingLong";
		send = true;

	}
	else if (sender == this->pingProfitable) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingProfitable";
		send = true;
	}
	else if (sender == this->pingSellProfitable) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingSellProfitable";
		send = true;
	}
	else if (sender == this->pingBuyProfitable) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingBuyProfitable";
		send = true;
	}
	else if (sender == this->pingLoss) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingLoss";
		send = true;
	}
	else if (sender == this->pingSellLoss) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingSellLoss";
		send = true;
	}
	else if (sender == this->pingBuyLoss) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "pingBuyLoss";
		send = true;
	}
	else if (sender == this->deletePending) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "deletePending";
		send = true;
	}
	else if (sender == this->deleteBuyPending) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "deleteBuyPending"; 
		send = true;
	}
	else if (sender == this->deleteSellPending) {
		myargs->Actor = "shoudong_panel";
		myargs->Verb = "deleteSellPending";
		send = true;
	}

	else if (sender == this->closeButton) {
		myargs->Actor = "panel";
		myargs->Verb = "close";
		myargs->Target = "shoudong_panel";
		send = true;
	}

	else if (sender == this->benbiCheckbox) {
		this->benbiCheckbox->IsChecked = true;
		this->quanbiCheckbox->IsChecked = false;
		this->eaCheckbox->IsChecked = false;
	}

	else if (sender == this->quanbiCheckbox) {
		this->quanbiCheckbox->IsChecked = true;
		this->benbiCheckbox->IsChecked = false;
		this->eaCheckbox->IsChecked = false;
	}

	else if (sender == this->eaCheckbox) {
		this->quanbiCheckbox->IsChecked = false;
		this->benbiCheckbox->IsChecked = false;
		this->eaCheckbox->IsChecked = true;
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



void ShouDongPage::GridMouseMove(Object ^sender, MouseEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		if (this->container->IndexOf(sender) > 0) {
			if (pos.X != this->mousePrePosition.X && pos.Y != this->mousePrePosition.Y)
				this->excludeButtonClicked = true;
		}


		OnGridMoved(this, gcnew PanelMoveEventArgs("shoudong_panel",
			gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y))
		);
	}
}

void ShouDongPage::GridMouseUp(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Released && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		OnGridMoved(this, gcnew PanelMoveEventArgs("shoudong_panel",
			gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y))
		);
	}

}

void ShouDongPage::GridMouseDown(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed) {
		this->isBeingPressed = true;
		this->mousePrePosition = args->GetPosition(this);
	}
}



ShouDongPage::ShouDongPage() {
	int rows = 7;
	int column = 15;
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
	title = CreateLabel(0, 0, "手动平仓管理模块");
	Grid::SetColumnSpan(title, 12);
	title->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
	title->Margin = Thickness(0, 0, 0, 10);

	closeButton = CreateButton(12, 0, "X");
	closeButton->Background = gcnew SolidColorBrush(Colors::Red);
	closeButton->Foreground = gcnew SolidColorBrush(Colors::Black);

	closeButton->Margin = Thickness(0, 0, 0, 10);

	closeButton->Click += gcnew RoutedEventHandler(this, &ShouDongPage::ButtonClicked);

	Grid::SetColumnSpan(closeButton, 3);


	note = CreateLabel(0, 1, "空单范围：");
	Grid::SetColumnSpan(note, 3);


	benbiLabel = CreateLabel(3, 1, "本币");
	Grid::SetColumnSpan(benbiLabel, 2);

	benbiCheckbox = CreateCheckBox(5, 1);
	Grid::SetColumnSpan(benbiCheckbox, 2);
	benbiCheckbox->IsChecked = true;
	benbiCheckbox->BorderBrush = gcnew SolidColorBrush(Colors::Red);

	quanbiLabel = CreateLabel(7, 1, "全币");
	Grid::SetColumnSpan(quanbiLabel, 2);

	quanbiCheckbox = CreateCheckBox(9, 1);
	Grid::SetColumnSpan(quanbiCheckbox, 2);
	quanbiCheckbox->IsChecked = false;

	eaLabel = CreateLabel(11, 1, "ea");
	Grid::SetColumnSpan(eaLabel, 2);

	eaCheckbox = CreateCheckBox(13, 1);
	Grid::SetColumnSpan(eaCheckbox, 2);

	eaCheckbox->IsChecked = false;

	benbiCheckbox->VerticalAlignment = System::Windows::VerticalAlignment::Center;
	quanbiCheckbox->VerticalAlignment = System::Windows::VerticalAlignment::Center;
	eaCheckbox->VerticalAlignment = System::Windows::VerticalAlignment::Center;

	//benbiCheckbox->Background = gcnew SolidColorBrush(Colors::Green);
	//quanbiCheckbox->Background = gcnew SolidColorBrush(Colors::Red);
	//eaCheckbox->Background = gcnew SolidColorBrush(Colors::Red);
	
	this->sep = CreateBorder(0, 2, Colors::Red, 1);
	this->sep->Margin = Thickness(0, 5, 0, 10);
	Grid::SetColumnSpan(this->sep, 15);

	
	benbiCheckbox->Click += gcnew RoutedEventHandler(this, &ShouDongPage::ButtonClicked); 
	quanbiCheckbox->Click += gcnew RoutedEventHandler(this, &ShouDongPage::ButtonClicked);
	eaCheckbox->Click += gcnew RoutedEventHandler(this, &ShouDongPage::ButtonClicked);

	//create command buttons
	pingAll = CreateButton(0, 3, "一键平仓");
	pingShort = CreateButton(5, 3, "一键平空");
	pingLong = CreateButton(10, 3, "一键平多");

	pingProfitable = CreateButton(0, 4, "平盈利单");
	pingSellProfitable = CreateButton(5, 4, "平空盈单");
	pingBuyProfitable = CreateButton(10, 4, "平多盈单");

	pingLoss = CreateButton(0, 5, "平亏损单");
	pingSellLoss = CreateButton(5, 5, "平空亏单");
	pingBuyLoss = CreateButton(10, 5, "平空盈单");


	deletePending = CreateButton(0, 6, "删除挂单");
	deleteSellPending = CreateButton(5, 6, "删Sell挂单");
	deleteBuyPending = CreateButton(10, 6, "删Buy挂单");


	this->container->Add(title);
	this->container->Add(closeButton);
	this->container->Add(note);
	this->container->Add(benbiLabel);
	this->container->Add(quanbiLabel);
	this->container->Add(eaLabel);

	this->container->Add(benbiCheckbox);
	this->container->Add(quanbiCheckbox);
	this->container->Add(eaCheckbox);


	this->container->Add(pingAll);
	this->container->Add(pingShort);
	this->container->Add(pingLong);
	this->container->Add(pingProfitable);
	
	this->container->Add(pingBuyProfitable);
	this->container->Add(pingSellProfitable);
	this->container->Add(pingLoss);
	this->container->Add(pingBuyLoss);
	this->container->Add(pingSellLoss);

	this->container->Add(deletePending);
	this->container->Add(deleteBuyPending);
	this->container->Add(deleteSellPending);



	//handle move grid event
	this->isBeingPressed = false;
	this->IsHitTestVisible = true;
	this->MouseDown += gcnew  MouseButtonEventHandler(this, &ShouDongPage::GridMouseDown);
	this->MouseUp += gcnew MouseButtonEventHandler(this, &ShouDongPage::GridMouseUp);
	this->MouseMove += gcnew MouseEventHandler(this, &ShouDongPage::GridMouseMove);


	for (int i = 0; i < this->container->Count; i++) {
		UIElement^ ele = static_cast<UIElement^>(this->container[i]);
		ele->PreviewMouseDown += gcnew  MouseButtonEventHandler(this, &ShouDongPage::GridMouseDown);
		ele->PreviewMouseUp += gcnew MouseButtonEventHandler(this, &ShouDongPage::GridMouseUp);
		ele->PreviewMouseMove += gcnew MouseEventHandler(this, &ShouDongPage::GridMouseMove);
	}

}






Button ^ShouDongPage::CreateButton(int column, int row, String ^ text)
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

Boolean ShouDongPage::isBenbi(){
      return this->benbiCheckbox->IsChecked;
}

Boolean ShouDongPage::isQuanbi(){
 	return this->quanbiCheckbox->IsChecked;
}

Boolean ShouDongPage::isEa(){
	return this->eaCheckbox->IsChecked;
}

void SetFontFamily(FontFamily^ newFontFamily) {}


