#pragma once
#include "WPFPage.h"

public ref class MainPage :WPFPage {
public:
	MainPage();
	MainPage(int height, int width) {};



	void ButtonClicked(Object ^sender, RoutedEventArgs ^args) ;

	void GridMouseMove(Object ^sender, MouseEventArgs^ args);
	void GridMouseDown(Object ^sender, MouseButtonEventArgs^ args);
	void GridMouseUp(Object ^sender, MouseButtonEventArgs^ args);


	void switchShouDongOff();
	void switchDuoBiOff();

private:
	

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


	Border^ sepLine1;
	Border^ sepLine2;
	Border^ sepLine3;
	Border^ sepLine4;


	Label^ shouDongPingChang;
	Label^ duoBiPingChang;


	Button^ shouDongPingChangSwitch1;
	Button^ shouDongPingChangSwitch2;

	Button^ duoBiPingChangSwitch1;
	Button^ duoBiPingChangSwitch2;

	Boolean isAdvanced;


};

