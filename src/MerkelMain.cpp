#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <limits>
#include "Candlestick.h"
#include "BarChart.h"

MerkelMain::MerkelMain() : currentMenuState(MAIN_MENU)
{

}

void MerkelMain::init()
{
    // loadOrderBook();
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        // printMenu();
          if (currentMenuState == MAIN_MENU)
        {
            std::cout << "Type in 1-8" << std::endl;
            printMenu();
        }
        else if (currentMenuState == CANDLESTICK_MENU)
        {
            printCandlestickMenu();
        }
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{

 if (currentMenuState == MAIN_MENU)
    {
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 Candlestick
    std::cout << "6: Print candlestick plot" << std::endl;
    // 7 Bar Chart
    std::cout << "7: Print Bar Chart" << std::endl;
    // 8 continue   
    std::cout << "8: Continue " << std::endl;


    std::cout << "============== " << std::endl;

    std::cout << "Current time is : " << currentTime << std::endl;
    }

       else if (currentMenuState == CANDLESTICK_MENU)
    {
        // Print the candlestick menu
        Candlestick::printCandlestickMenu();
    }
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product : " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p,
                                                                  currentTime);
        std::cout << " asks seen: " << entries.size() << std::endl;
        std::cout << " max ask : " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << " min ask : " << OrderBook::getlowPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5 " << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "wallet has insufficient funds." << std::endl;
            }
        }
        catch (const std::exception&)
        {
            std::cout << " MerkelMain::enterAsk bad input! " << std::endl;
        }
    }

    std::cout << "you typed: " << input << std::endl;
}

void MerkelMain::enterBid()
{

    std::cout << "Make an bid - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5 " << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
                );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "wallet has insufficient funds." << std::endl;
            }
        }
        catch (const std::exception &)
        {
            std::cout << " MerkelMain::enterbid bad input! " << std::endl;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p :orderBook.getKnownProducts())
    {
        std::cout << "matching" << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "sale price: " << sale.price << " amount: " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                //update the wallet
                wallet.processSale(sale);
            }
    
        }
    }    

    currentTime = orderBook.getNextTime(currentTime);
    
}

/** print the second menu*/
void MerkelMain::printCandlestickMenu()
{
    std::cout << "Type 1-10 to choose the product and type " << std::endl;
    Candlestick::printCandlestickMenu();

    std::string userInput;
    int chosenOption;
    std::cout << "Enter your choice: ";
    std::getline(std::cin, userInput);

    try
    {
        chosenOption = std::stoi(userInput);
    }
    catch (const std::exception &)
    {
        std::cout << "Invalid input. Going back to main menu." << std::endl;
        chosenOption = 0;
    }

    if (chosenOption < 0 || chosenOption >= static_cast<int>(Candlestick::options.size()))
    {
        std::cout << "Invalid choice. Going back to main menu." << std::endl;
    }
    else if (chosenOption > 0)
    {
        std::vector<std::string> tokens = Candlestick::tokenising(chosenOption);
        Candlestick::filter_products(tokens);
        std::vector<Candlestick> Candlesticks = Candlestick::createCandlestickVector();
        Candlestick::createCandlestickPlot(Candlesticks);
    }

    // option 0, an invalid choice and a finished plot all return to the main menu
    currentMenuState = MAIN_MENU;
    printMenu();
}

void MerkelMain::printBarChart() 
{
    std::vector<BarChart> BarCharts = BarChart::createBarChartVector();
    BarChart::createBarChart(BarCharts);

}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    // std::cout << "Type in 1-8" << std::endl;
    std::getline(std::cin, line);
    try {
    userOption = std::stoi(line);
    } catch (const std::exception&)
    {
        //
    }

    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (currentMenuState == MAIN_MENU)
    {
        // Process options for the main menu
        if (userOption == 1)
        {
            printHelp();
        }
        else if (userOption == 2)
        {
            printMarketStats();
        }
        else if (userOption == 3)
        {
            enterAsk();
        }
        else if (userOption == 4)
        {
            enterBid();
        }
        else if (userOption == 5)
        {
            printWallet();
        }
        else if (userOption == 6)
        {
            currentMenuState = CANDLESTICK_MENU;
        }
        else if (userOption == 7)
        {
            printBarChart();
        }
        else if (userOption == 8)
        {
            gotoNextTimeframe();
        }
    }
    else if (currentMenuState == CANDLESTICK_MENU)
    {
        if (userOption == 0)
        {
            currentMenuState = MAIN_MENU;  
        }
    }
}