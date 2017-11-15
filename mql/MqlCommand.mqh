//+------------------------------------------------------------------+
//|                                                   MqlCommand.mqh |
//|                        Copyright 2017, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2017, MetaQuotes Software Corp."
#property link      "https://www.mql5.com"
#property strict
//+------------------------------------------------------------------+
//| defines                                                          |
//+------------------------------------------------------------------+
// #define MacrosHello   "Hello, world!"
// #define MacrosYear    2010
//+------------------------------------------------------------------+
//| DLL imports                                                      |
//+------------------------------------------------------------------+
// #import "user32.dll"
//   int      SendMessageA(int hWnd,int Msg,int wParam,int lParam);
// #import "my_expert.dll"
//   int      ExpertRecalculate(int wParam,int lParam);
// #import
//+------------------------------------------------------------------+
//| EX5 imports                                                      |
//+------------------------------------------------------------------+
// #import "stdlib.ex5"
//   string ErrorDescription(int error_code);
// #import
//+------------------------------------------------------------------+
#import "Win32Dll.dll" 
    void createProcess(int hwnd);
    bool hasMessage();
    string getMessage();
    void removeMessage();
#import

ushort SEP = StringGetCharacter("|", 0);
const int ORDERS = 1001;
const int OPEN_SLIPPAGE = 5;
const int CLOSE_SLIPPAGE = 5;

void processMessage(string message){
   string result[];
   int k = StringSplit(message, SEP, result);
   if(k > 0){
       //main panel command handling
       if(StringCompare(result[0], "buy") == 0){ 
            buyCommand(result);
       }
       else if(StringCompare(result[0], "sell") == 0){
            sellCommand(result);
       }
       else if(StringCompare(result[0], "pingchang") == 0){
            pingChangCommand();
       }
       else if(StringCompare(result[0], "qingchang") == 0){
            qingChangCommand();
       }
       else if(StringCompare(result[0], "duisuo") == 0){
            duisuo();
       }
       else if(StringCompare(result[0], "quansuo") == 0){
            quansuo();
       }
       else if(StringCompare(result[0], "deleteStop") == 0){
            removeStopLevel();
       }
       else if(StringCompare(result[0], "deleteProfit") == 0){
            removeProfitLevel();
       }
       //shoudong ping chang handling
       else if(StringCompare(result[0], "pingAll") == 0){
            pingAll(result[1]);
       }
       else if(StringCompare(result[0], "pingShort") == 0){
            pingShort(result[1]);
       }
       else if(StringCompare(result[0], "pingLong") == 0 ){
            pingLong(result[1]);
       }
       else if(StringCompare(result[0], "pingProfitable") == 0){
            pingProfitable(result[1]);
       }
       else if(StringCompare(result[0], "pingSellProfitable") == 0){
            pingSellProfitable(result[1]);
       }
       else if(StringCompare(result[0], "pingBuyProfitable") == 0) {
            pingBuyProfitable(result[1]);
       }
       else if(StringCompare(result[0], "pingLoss") == 0){
            pingLoss(result[1]);
       }
       else if(StringCompare(result[0], "pingSellLoss") == 0){
            pingSellLoss(result[1]);
       }
       else if(StringCompare(result[0], "pingBuyLoss") == 0 ){
            pingBuyLoss(result[1]);
       }
       else if(StringCompare(result[0], "deletePending") == 0){
            deletePending(result[1]);
       } 
       else if(StringCompare(result[0], "deleteBuyPending") == 0){
            deleteBuyPending(result[1]);
       }
       else if(StringCompare(result[0], "deleteSellPending") == 0){
            deleteSellPending(result[1]);
       }
   }
   else{
      //raise exception
   }
}


void duisuo(){
   int tickets[1001];
   int ticket;
   double lots = 0;
   getAllActiveOrdersOfSymbol(tickets, Symbol());
   for(int i = 0; i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderType() == OP_SELL)
         lots -= OrderLots(); 
      else
         lots += OrderLots(); 
      
   }
   if(lots < 0)
      ticket = OrderSend(OrderSymbol(), OP_BUY, lots , Ask, OPEN_SLIPPAGE, 0, 0);
   else
      ticket = OrderSend(OrderSymbol(), OP_SELL, lots, Bid, OPEN_SLIPPAGE, 0, 0);
      
   if(ticket < 0){
      int errorCode = GetLastError();
      //raise exception
   }
   
}

void quansuo(){
   int tickets[1001];
   getAllActiveOrders(tickets);
   int ticket;
   string symbols[1001];
   int symbolSize = 0;
   int counter = 0;
   //get symbols of all orders
   for(int i =0 ; i < 1001; i++){
       if(tickets[i] == 0) break;
       if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
       bool contained = false;
       for(int j=0; j < symbolSize; j++){
          if(StringCompare(symbols[j], OrderSymbol()) == 0){
               contained  = true;
               break;
          }
       }
       if(!contained){
           symbols[counter++] = OrderSymbol();
           symbolSize++;
       }
   }
   //duisuo
   for(int i=0; i < symbolSize; i++){
      string currentSymbol = symbols[i];
      double lots = 0;
      for(int j = 0; j < ORDERS; j++){
         if(tickets[j] == 0 ) break;
         if(OrderSelect(tickets[j], SELECT_BY_TICKET) == false) continue;
         if(OrderType() == OP_SELL)
            lots -= OrderLots();
         else
            lots += OrderLots();
      }
      if(lots < 0)
         ticket = OrderSend(OrderSymbol(), OP_BUY, lots , Ask, OPEN_SLIPPAGE, 0, 0);
      else
         ticket = OrderSend(OrderSymbol(), OP_SELL, lots, Bid, OPEN_SLIPPAGE, 0, 0);
   
      if(ticket < 0){
         int errorCode = GetLastError();
         //raise exception
      }
   }
    
}

void pingAll(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
    for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}
void pingShort(string condition){
    int tickets[1001];
    bool closed;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
    for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderType() == OP_BUY) continue;
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}
void pingLong(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
    for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderType() == OP_SELL) continue;
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}

void pingProfitable(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
    for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderProfit() < 0) continue;
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}

void pingSellProfitable(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
     for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderProfit() < 0) continue;
      if(OrderType() == OP_BUY) continue;
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}

void pingBuyProfitable(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
    for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderProfit() < 0) continue;
      if(OrderType() == OP_SELL) continue;
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}

void pingLoss(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
    for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderProfit() >= 0) continue; 
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}

void pingSellLoss(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
    for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderProfit() >= 0) continue;
      if(OrderType() == OP_BUY) continue; 
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}

void pingBuyLoss(string condition){
    int tickets[1001];
    bool closed = true;
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
     for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
      if(OrderProfit() >= 0) continue;
      if(OrderType() == OP_SELL) continue; 
       closed = OrderClose(tickets[i], OrderLots(), OrderOpenPrice(), CLOSE_SLIPPAGE);
       if(!closed){
         int errorCode = GetLastError();
         //raise exception
       }
    }
}

void deletePending(string condition){
    int tickets[1001];
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
}

void deleteBuyPending(string condition){
    int tickets[1001];
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
}

void deleteSellPending(string condition){
    int tickets[1001];
    if(StringCompare(condition, "benbi") == 0 ){
         getAllActiveOrdersOfSymbol(tickets, Symbol());
    }
    else if(StringCompare(condition, "quanbi") == 0 ){
         getAllActiveOrders(tickets);
    }
    else if(StringCompare(condition, "ea") == 0){
    
    }
}

void pingChangCommand(){
   int tickets[1001];
   getAllActiveOrdersOfSymbol(tickets, Symbol());
   bool closed = true;
   for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0)
         break;
      else{
         if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
         if(OrderType() == OP_SELL)
          closed = OrderClose(tickets[i], OrderLots(), Ask, CLOSE_SLIPPAGE);
         else
          closed = OrderClose(tickets[i], OrderLots(), Bid, CLOSE_SLIPPAGE);
          
         if(!closed){
            int errorCode = GetLastError();
            // raise exception
         }
      }
   }
}

void qingChangCommand(){
   int tickets[1001];
   getAllActiveOrders(tickets);
   bool closed = true;
   for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0)
         break;
      else{
         if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue;
         if(OrderType() == OP_SELL)
          closed = OrderClose(tickets[i], OrderLots(), Ask, CLOSE_SLIPPAGE);
         else
          closed = OrderClose(tickets[i], OrderLots(), Bid, CLOSE_SLIPPAGE);
          
         if(!closed){
            int errorCode = GetLastError();
            // raise exception
         }
      }
   }
}

void removeStopLevel(){
   int tickets[1001];
   getAllActiveOrdersOfSymbol(tickets, Symbol());
   bool modifed = true;
   for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      else{
         if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue; 
         else{
            modifed = OrderModify(tickets[i], OrderOpenPrice(), 0, OrderTakeProfit(), 0);
            if(!modifed){
               int errorCode = GetLastError();
               //raise exception
            }
         }
      }
   }
}

void removeProfitLevel(){
    int tickets[1001];
   getAllActiveOrdersOfSymbol(tickets, Symbol());
   bool modifed = true;
   for(int i=0;i < ORDERS; i++){
      if(tickets[i] == 0) break;
      else{
         if(OrderSelect(tickets[i], SELECT_BY_TICKET) == false) continue; 
         else{
            modifed = OrderModify(tickets[i], OrderOpenPrice(), OrderStopLoss(), 0, 0);
            if(!modifed){
               int errorCode = GetLastError();
               //raise exception
            }
         }
      }
   }
}

void buyCommand(string &message[]){
    string lots = message[1]; 
    int stop = 0;
    int profit = 0;  
    if(StringCompare(message[2], "none") != 0){ 
      stop = StringToInteger(message[2]);     
      }
    if(StringCompare(message[3], "none") != 0){  
      profit = StringToInteger(message[3]); 
     
     }
       
    buy(StringToDouble(lots), stop , profit);   
     
}

void sellCommand(string &message[]){
   string lots = message[1];
   int stop = 0;
   int profit = 0;
   if(StringCompare(message[2], "none") != 0)
      stop = StringToInteger(message[2]);     
   if(StringCompare(message[3], "none") != 0)
      profit = StringToInteger(message[3]);
       
    sell(StringToDouble(lots), stop , profit);   
}

void buy(double lots, int stop, int profit){ 
   int ticket = 0;
   if(stop==0 && profit ==0)
      ticket = OrderSend(Symbol(), OP_BUY, lots, Ask, OPEN_SLIPPAGE, 0, 0);
   else if(stop == 0 && profit != 0)
      ticket = OrderSend(Symbol(), OP_BUY, lots, Ask, OPEN_SLIPPAGE, 0, Ask + profit*Point);
   else if(stop != 0 && profit == 0)
      ticket = OrderSend(Symbol(), OP_BUY, lots, Ask, OPEN_SLIPPAGE, Ask - stop*Point, 0);
   else
      ticket = OrderSend(Symbol(), OP_BUY, lots, Ask, OPEN_SLIPPAGE, Ask - stop*Point, Ask + profit*Point);
   
   if(ticket < 0){
      int errorCode = GetLastError();
      //raise exception
   }
}

void sell(double lots, int stop, int profit){
   int ticket = 0;
   if(stop==0 && profit ==0)
      ticket = OrderSend(Symbol(), OP_SELL, lots, Bid, OPEN_SLIPPAGE, 0, 0);
   else if(stop == 0 && profit != 0)
      ticket = OrderSend(Symbol(), OP_SELL, lots, Bid, OPEN_SLIPPAGE, 0, Bid - profit * Point);
   else if(stop != 0 && profit == 0)
      ticket = OrderSend(Symbol(), OP_SELL, lots, Bid, OPEN_SLIPPAGE, Bid + stop * Point, 0);
   else
      ticket = OrderSend(Symbol(), OP_SELL, lots, Bid, OPEN_SLIPPAGE, Bid + stop * Point, Bid - profit * Point);
      
   if(ticket < 0){
      int errorCode = GetLastError();
      //raise exception
   }
}

void getAllActiveOrders(int &tickets[]){ 
   int total = OrdersTotal();
   int counter = 0;
   for( int i =0; i < total; i++){
      if(OrderSelect(i, SELECT_BY_POS) == false) continue;
      tickets[counter] = OrderTicket();
      counter ++;
   }  
}

void getAllActiveOrdersOfSymbol(int &tickets[], string symbol){
   int total = OrdersTotal();
   int counter = 0;
   for( int i =0; i < total; i++){
      if(OrderSelect(i, SELECT_BY_POS) == false) continue;
      if(StringCompare(OrderSymbol(), symbol)!= 0) continue;
      tickets[counter] = OrderTicket();
      counter ++;
   } 
}