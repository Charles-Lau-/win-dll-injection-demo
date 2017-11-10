#pragma once
#include "WPFPage.h"

public ref class ShouDongPage:WPFPage {
public:
	ShouDongPage();
	ShouDongPage(int height, int width) {};

	void ButtonClicked(Object ^sender, RoutedEventArgs ^args);
;


	Button ^CreateButton(int column, int row, String ^ text) ;


	void GridMouseMove(Object ^sender, MouseEventArgs^ args);
	void GridMouseDown(Object ^sender, MouseButtonEventArgs^ args);
	void GridMouseUp(Object ^sender, MouseButtonEventArgs^ args);


private:


	Label^ title;

	Button^ closeButton;

	Border^ sep;

	Label^ note;
	Label^ benbiLabel;
	Label^ quanbiLabel;
	Label^ eaLabel;

	CheckBox^ benbiCheckbox;
	CheckBox^ quanbiCheckbox;
	CheckBox^ eaCheckbox;


	Button^ pingAll;
	Button^ pingShort;
	Button^ pingLong;
	Button^ pingProfitable;
	Button^ pingBuyProfitable;
	Button^ pingSellProfitable;
	Button^ pingLoss;
	Button^ pingBuyLoss;
	Button^ pingSellLoss;

	Button^ deletePending;
	Button^ deleteBuyPending;
	Button^ deleteSellPending;


};

