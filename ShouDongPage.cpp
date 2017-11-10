#include"stdafx.h"
#include "ShouDongPage.h"
#include <string> 
#include <cstdio>
#include <iostream>



void ShouDongPage::ButtonClicked(Object ^sender, RoutedEventArgs ^args) {
	MyApplicationEventArgs^ myargs = gcnew MyApplicationEventArgs();
	Boolean send = false;
	if (sender == this->pingAll) {
		myargs->Actor = "pingAll";
		send = true;
	}
	else if (sender == this->pingShort) {
		myargs->Actor = "pingShort";
		send = true;

	}
	else if (sender == this->pingLong) {
		myargs->Actor = "pingLong";
		send = true;

	}
	else if (sender == this->pingProfitable) {
		myargs->Actor = "pingProfitable";
		send = true;
	}
	else if (sender == this->pingSellProfitable) {
		myargs->Actor = "pingSellProfitable";
		send = true;
	}
	else if (sender == this->pingBuyProfitable) {
		myargs->Actor = "pingBuyProfitable";
		send = true;
	}
	else if (sender == this->pingLoss) {
		myargs->Actor = "pingLoss";
		send = true;
	}
	else if (sender == this->pingSellLoss) {
		myargs->Actor = "pingSellLoss";
		send = true;
	}
	else if (sender == this->pingBuyLoss) {
		myargs->Actor = "pingBuyLoss";
		send = true;
	}
	else if (sender == this->deletePending) {
		myargs->Actor = "deletePending";
		send = true;
	}
	else if (sender == this->deleteBuyPending) {
		myargs->Actor = "deleteBuyPending"; 
		send = true;
	}
	else if (sender == this->deleteSellPending) {
		myargs->Actor = "deleteSellPending";
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
	title = CreateLabel(0, 0, "�ֶ�ƽ�ֹ���ģ��");
	Grid::SetColumnSpan(title, 12);
	title->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
	title->Margin = Thickness(0, 0, 0, 10);

	closeButton = CreateButton(12, 0, "X");
	closeButton->Background = gcnew SolidColorBrush(Colors::Red);
	closeButton->Foreground = gcnew SolidColorBrush(Colors::Black);

	closeButton->Margin = Thickness(0, 0, 0, 10);

	closeButton->Click += gcnew RoutedEventHandler(this, &ShouDongPage::ButtonClicked);

	Grid::SetColumnSpan(closeButton, 3);


	note = CreateLabel(0, 1, "�յ���Χ��");
	Grid::SetColumnSpan(note, 3);


	benbiLabel = CreateLabel(3, 1, "����");
	Grid::SetColumnSpan(benbiLabel, 2);

	benbiCheckbox = CreateCheckBox(5, 1);
	Grid::SetColumnSpan(benbiCheckbox, 2);
	benbiCheckbox->IsChecked = true;
	benbiCheckbox->BorderBrush = gcnew SolidColorBrush(Colors::Red);

	quanbiLabel = CreateLabel(7, 1, "ȫ��");
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
	pingAll = CreateButton(0, 3, "һ��ƽ��");
	pingShort = CreateButton(5, 3, "һ��ƽ��");
	pingLong = CreateButton(10, 3, "һ��ƽ��");

	pingProfitable = CreateButton(0, 4, "ƽӯ����");
	pingSellProfitable = CreateButton(5, 4, "ƽ��ӯ��");
	pingBuyProfitable = CreateButton(10, 4, "ƽ��ӯ��");

	pingLoss = CreateButton(0, 5, "ƽ����");
	pingSellLoss = CreateButton(5, 5, "ƽ�տ���");
	pingBuyLoss = CreateButton(10, 5, "ƽ��ӯ��");


	deletePending = CreateButton(0, 6, "ɾ���ҵ�");
	deleteSellPending = CreateButton(5, 6, "ɾSell�ҵ�");
	deleteBuyPending = CreateButton(10, 6, "ɾBuy�ҵ�");


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


void SetFontFamily(FontFamily^ newFontFamily) {}

