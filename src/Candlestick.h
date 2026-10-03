#pragma once
#include <string>
#include <vector>
#include "OrderBookEntry.h"


class Candlestick
{
public:
    Candlestick(std::string date,
                double open,
                double high,
                double low,
                double close);

    std::string date;
    double open;
    double close;
    double low;
    double high;

    /** handling the menu*/
    static std::vector<std::string> options;
    static void printCandlestickMenu();
    static int userOption;

    /** mange order book entries*/
    static std::vector<OrderBookEntry> orders_sub;

    /** tokenisising userinput*/
    static std::vector<std::string> tokenising (int userOption);

    /** filter prodicts based on tokens*/
    static std::vector<OrderBookEntry> filter_products(std::vector<std::string> tokens);

    /** all order book entries from the data file, read the first time they are needed*/
    static const std::vector<OrderBookEntry>& getEntries();
    static double calculateClosingPrice(std::vector<OrderBookEntry> orders);
    static Candlestick createCandlestick(std::vector<OrderBookEntry> orders, double open_price, std::string timing);
    static std::vector<OrderBookEntry> createIntervals(std::vector<OrderBookEntry> orders, std::string date_1, std::string date_2);

    /** create candlestick objects and return vector of candlesticks*/
    static std::vector<Candlestick> createCandlestickVector();
    static void createCandlestickPlot(std::vector<Candlestick> Candlesticks);
};