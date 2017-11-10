#include"stdafx.h"
#include "MainPage.h"
#include <string> 
#include <cstdio>
#include <iostream>





void MainPage::GridMouseMove(Object ^sender, MouseEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		if (this->container->IndexOf(sender) > 0) {
			if (pos.X != this->mousePrePosition.X && pos.Y != this->mousePrePosition.Y)
				this->excludeButtonClicked = true;
		}

		

		OnGridMoved(this, gcnew PanelMoveEventArgs("main_panel", 
			gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y))
		);
	}
}

void MainPage::GridMouseUp(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Released && this->isBeingPressed) {
		Point pos = args->GetPosition(this);
		OnGridMoved(this, gcnew PanelMoveEventArgs("main_panel", 
			gcnew Point(pos.X - this->mousePrePosition.X, pos.Y - this->mousePrePosition.Y))
		);
	}

}

void MainPage::GridMouseDown(Object ^sender, MouseButtonEventArgs^ args) {
	if (args->LeftButton == MouseButtonState::Pressed) {
		this->isBeingPressed = true;
		this->mousePrePosition = args->GetPosition(this);
	}
}




MainPage::MainPage()
{
	int rows = 14;
	int column = 8;
	array<ColumnDefinition ^> ^ columnDef = gcnew array<ColumnDefinition ^>(column);
	array<RowDefinition ^> ^ rowDef = gcnew array<RowDefinition ^>(rows);
	this->container = gcnew System::Collections::ArrayList();
	this->excludeButtonClicked = false;
	this->isAdvanced = false;
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
	hiddenButton = CreateButton(0, 0, "收放");
	hiddenButton->Background = gcnew SolidColorBrush(Colors::Yellow);
	advanceButton = CreateButton(1, 0, "高级");
	advanceButton->Background = gcnew SolidColorBrush(Colors::Blue);
	configureButton = CreateButton(2, 0, "配置");
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

	//put buttons in container array for convenient manipulation
	this->container->Add(hiddenButton);
	this->container->Add(advanceButton);
	this->container->Add(configureButton);
	this->container->Add(pingchangButton);
	this->container->Add(qingchangButton);
	this->container->Add(duisuoButton);
	this->container->Add(quansuoButton);

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

	//add second row element in container array for convenient manipulation
	this->container->Add(sellButton);
	this->container->Add(convenientButton1);
	this->container->Add(convenientButton2);
	this->container->Add(convenientButton3);
	this->container->Add(convenientButton4);
	this->container->Add(lotsButton5);
	this->container->Add(buyButton);
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

	//add third row element in container array for convenient manipulation
	this->container->Add(deleteStopButton);
	this->container->Add(stopButton);
	this->container->Add(stopLevelInput);
	this->container->Add(profitButton);
	this->container->Add(profitLevelInput);
	this->container->Add(deleteProfitButton);




	Grid::SetColumnSpan(stopLevelInput, 2);
	Grid::SetColumnSpan(profitLevelInput, 2);



	//handle button click
	hiddenButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	advanceButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	configureButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	pingchangButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	qingchangButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	duisuoButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	quansuoButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);

	sellButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	buyButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);


	convenientButton1->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	convenientButton2->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	convenientButton3->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	convenientButton4->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);


	deleteStopButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	stopButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);

	deleteProfitButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	profitButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);




	//add a separation line for the grid
	this->sepLine1 = CreateBorder(0, 5, Colors::Red, 1);
	Grid::SetColumnSpan(sepLine1, 8);
	//add advanced part  which is consist of multiple choices
	shouDongPingChang = CreateLabel(0, 6, "手动平仓");
	shouDongPingChangSwitch1 = CreateButton(2, 6, "");
	shouDongPingChangSwitch2 = CreateButton(3, 6, "OFF");
	shouDongPingChangSwitch1->Foreground = gcnew SolidColorBrush(Colors::Blue);
	shouDongPingChangSwitch1->Background = gcnew SolidColorBrush(Colors::White);
	shouDongPingChangSwitch2->Background = gcnew SolidColorBrush(Colors::Red);
	shouDongPingChangSwitch1->BorderThickness = Thickness(0);
	shouDongPingChangSwitch2->BorderThickness = Thickness(0);
	shouDongPingChangSwitch1->BorderBrush = gcnew SolidColorBrush(Colors::Transparent);
	shouDongPingChangSwitch2->BorderBrush = gcnew SolidColorBrush(Colors::Transparent);
	shouDongPingChangSwitch1->Margin = Thickness(0, 0, -1, 0);
	shouDongPingChangSwitch2->Margin = Thickness(-1, 0, 0, 0);
	//shouDongPingChangSwitch1->Cursor = gcnew System::Windows::Input::Cursor("hand");
	Grid::SetColumnSpan(shouDongPingChang, 2);

	duoBiPingChang = CreateLabel(4, 6, "多币平仓");
	duoBiPingChangSwitch1 = CreateButton(6, 6, "");
	duoBiPingChangSwitch2 = CreateButton(7, 6, "OFF");
	duoBiPingChangSwitch1->Foreground = gcnew SolidColorBrush(Colors::Blue);
	duoBiPingChangSwitch1->Background = gcnew SolidColorBrush(Colors::White);
	duoBiPingChangSwitch2->Background = gcnew SolidColorBrush(Colors::Red);
	duoBiPingChangSwitch1->BorderThickness = Thickness(0);
	duoBiPingChangSwitch2->BorderThickness = Thickness(0);
	duoBiPingChangSwitch1->BorderBrush = gcnew SolidColorBrush(Colors::Transparent);
	duoBiPingChangSwitch2->BorderBrush = gcnew SolidColorBrush(Colors::Transparent);
	duoBiPingChangSwitch1->Margin = Thickness(0, 0, -1, 0);
	duoBiPingChangSwitch2->Margin = Thickness(-1, 0, 0, 0);
	Grid::SetColumnSpan(duoBiPingChang, 2);


	shouDongPingChangSwitch1->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	shouDongPingChangSwitch2->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);

	duoBiPingChangSwitch1->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
	duoBiPingChangSwitch2->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);

	this->container->Add(shouDongPingChangSwitch1);
	this->container->Add(shouDongPingChangSwitch2);

	this->container->Add(duoBiPingChangSwitch1);
	this->container->Add(duoBiPingChangSwitch2);



	//handle move grid event
	this->isBeingPressed = false;
	this->IsHitTestVisible = true;
	this->MouseDown += gcnew  MouseButtonEventHandler(this, &MainPage::GridMouseDown);
	this->MouseUp += gcnew MouseButtonEventHandler(this, &MainPage::GridMouseUp);
	this->MouseMove += gcnew MouseEventHandler(this, &MainPage::GridMouseMove);


	for (int i = 0; i < this->container->Count; i++) {
		UIElement^ ele = static_cast<UIElement^>(this->container[i]);
		ele->PreviewMouseDown += gcnew  MouseButtonEventHandler(this, &MainPage::GridMouseDown);
		ele->PreviewMouseUp += gcnew MouseButtonEventHandler(this, &MainPage::GridMouseUp);
		ele->PreviewMouseMove += gcnew MouseEventHandler(this, &MainPage::GridMouseMove);
	}

	//cancelButton->Click += gcnew RoutedEventHandler(this, &MainPage::ButtonClicked);
}


void MainPage::ButtonClicked(Object ^sender, RoutedEventArgs ^args)
{

	MyApplicationEventArgs^ myargs = gcnew MyApplicationEventArgs();
	Boolean send = false;
	if (sender == this->qingchangButton) {
		myargs->Actor = "qingchang";
		send = true;
	}
	else if (sender == this->pingchangButton) {
		myargs->Actor = "pingchang";
		send = true;

	}
	else if (sender == this->buyButton) {
		myargs->Actor = "buy";
		send = true;

	}
	else if (sender == this->sellButton) {
		myargs->Actor = "sell";
		send = true;
	}
	else if (sender == this->duisuoButton) {
		myargs->Actor = "duisuo";
		send = true;
	}
	else if (sender == this->quansuoButton) {
		myargs->Actor = "quansuo";
		send = true;
	}
	else if (sender == this->sellButton) {
		myargs->Actor = "buy";
		send = true;
	}
	else if (sender == this->buyButton) {
		myargs->Actor = "sell";
		send = true;
	}
	else if (sender == this->deleteStopButton) {
		myargs->Actor = "deleteStop";
		send = true;
	}
	else if (sender == this->deleteProfitButton) {
		myargs->Actor = "deleteProfit";
		send = true;
	}
	else if (sender == advanceButton) {
		myargs->Actor = "advance_panel";
		myargs->Verb = "show";
		if (this->isAdvanced) {
			myargs->Target = "simple";
			this->isAdvanced = false;
		}
		else {
			myargs->Target = "advance";
			this->isAdvanced = true;
		}
		send = true;
	}

	//deal with click on advanced button
	else if (sender == shouDongPingChangSwitch1 || sender == shouDongPingChangSwitch2) {
		if (this->shouDongPingChangSwitch1->Content == "ON") {
			this->shouDongPingChangSwitch1->Content = "";
			this->shouDongPingChangSwitch2->Content = "OFF";
			myargs->Actor = "advance_switch";
			myargs->Verb = "close";
			myargs->Target = "shoudong_panel";
		}
		else if (this->shouDongPingChangSwitch2->Content == "OFF") {
			this->shouDongPingChangSwitch1->Content = "ON";
			this->shouDongPingChangSwitch2->Content = "";
			myargs->Actor = "advance_switch";
			myargs->Verb = "open";
			myargs->Target = "shoudong_panel";
		}
		send = true;
	}
	else if (sender == duoBiPingChangSwitch1 || sender == duoBiPingChangSwitch2) {
		if (this->duoBiPingChangSwitch1->Content == "ON") {
			this->duoBiPingChangSwitch1->Content = "";
			this->duoBiPingChangSwitch2->Content = "OFF";
			myargs->Actor = "advance_switch";
			myargs->Verb = "close";
			myargs->Target = "duobi_panel";
		}
		else if (this->duoBiPingChangSwitch2->Content == "OFF") {
			this->duoBiPingChangSwitch1->Content = "ON";
			this->duoBiPingChangSwitch2->Content = "";
			myargs->Actor = "advance_switch";
			myargs->Verb = "open";
			myargs->Target = "duobi_panel";
		}
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
	else {
		if (sender == this->convenientButton1
			|| sender == this->convenientButton2
			|| sender == this->convenientButton3
			|| sender == this->convenientButton4) {
			Button^ button = static_cast<Button^>(sender);
			this->lotsButton5->Text = static_cast<String^>(button->Content);
		}
		else if (sender == this->stopButton || sender == this->profitButton)
		{
			Button^ button = static_cast<Button^>(sender);
			String^ content = static_cast<String^>(button->Content);
			if (content == "有")
				button->Content = "无";
			else if (content == "无")
				button->Content = "有";
		}
	}
}


void MainPage::switchShouDongOff() {
	this->shouDongPingChangSwitch1->Content = "";
	this->shouDongPingChangSwitch2->Content = "OFF";
}

