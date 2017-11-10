#pragma once

#pragma once
#include "WPFPage.h"

public ref class DuoBiPage:WPFPage {
public:
	DuoBiPage();
	DuoBiPage(int height, int width) {};

	void ButtonClicked(Object ^sender, RoutedEventArgs ^args);


	Button ^CreateButton(int column, int row, String ^ text);

	void GridMouseMove(Object ^sender, MouseEventArgs^ args);
	void GridMouseDown(Object ^sender, MouseButtonEventArgs^ args);
	void GridMouseUp(Object ^sender, MouseButtonEventArgs^ args);

	Label ^DuoBiPage::CreateCell(int column, int row, String ^ text);


private:


	Label^ title;

	Button^ closeButton;

	Border^ sep;


	Label^ num;
	Label^ symbol;
	Label^ point;
	Label^ sell;
	Label^ sellLimit;
	Label^ sellStop;
	Label^ buy;
	Label^  buylimit;
	Label^ buystop;
	Label^ profit;



};


