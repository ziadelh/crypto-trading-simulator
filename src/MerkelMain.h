#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "DataFile.h"

class MerkelMain
{
    public:

        MerkelMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int  getUserOption();
        void processUserOption(int userOption);
        void printCandlestickMenu();
        void printBarChart();

        std::string currentTime;

        OrderBook orderBook{DATA_FILE};

        Wallet wallet{};
         enum MenuState
            {
                 MAIN_MENU,
                CANDLESTICK_MENU
            };

    MenuState currentMenuState;


        
};
