#pragma once

#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "Candlestick.h"
#include "CSVReader.h"

//class definition 
class BarChart
{
public:
    //constructor
    BarChart(std::string timeInterval,
             std::string productType,
             double open,
             double close);

    std::string timeInterval;
    std::string productType;
    double open;
    double close;


    /**return filtered orders based on productType*/
    static std::vector<OrderBookEntry> filtering_orders(std::string productType);
    
    /**create a barchart object*/
    static BarChart createBarChart(std::vector<OrderBookEntry> orders, double open_price, std::string timing, std::string type);

    /**return a vector of barchart objects*/
    static std::vector<BarChart> createBarChartVector();

    /** return barcharts from the vector of BarChart objects*/
    static void createBarChart(std::vector<BarChart> BarCharts);
};