#include "BarChart.h"

#include <iostream>
#include <algorithm>
#include <map>


BarChart::BarChart(std::string _timeInterval,
                   std::string _productType,
                   double _open,
                   double _close)

    : timeInterval(_timeInterval),
      productType(_productType),
      open(_open),
      close(_close)

{
}

/** filter orders based on productType*/
std::vector<OrderBookEntry> BarChart::filtering_orders (std::string productType)
{
    std::vector<OrderBookEntry> filtered_orders;
    for (const OrderBookEntry &order : Candlestick::getEntries())
    {
        if (order.product == productType)
        {
            filtered_orders.push_back(order);
        }
    }
    return filtered_orders;
}

/** create barchart object*/
BarChart BarChart::createBarChart(std::vector<OrderBookEntry> orders, double open_price, std::string timing, std::string type)
{
    std::string timeInterval = timing;
    std::string product = type;
    double open = open_price;
    double close = Candlestick::calculateClosingPrice(orders);

    BarChart barchart{timeInterval, product, open, close};
    return barchart;
}

/** create vector of barchart objects*/
std::vector<BarChart> BarChart::createBarChartVector()
{
    /**Creating vectors for each product*/
    std::vector<OrderBookEntry> BTC_USDT = BarChart::filtering_orders("BTC/USDT");
    std::vector<OrderBookEntry> DOGE_BTC = BarChart::filtering_orders("DOGE/BTC");
    std::vector<OrderBookEntry> DOGE_USDT = BarChart::filtering_orders("DOGE/USDT");
    std::vector<OrderBookEntry> ETH_BTC = BarChart::filtering_orders("ETH/BTC");
    std::vector<OrderBookEntry> ETH_USDT = BarChart::filtering_orders("ETH/USDT");


    /** Separating each product vector into 4 time intervals*/
    /** BTC/USDT */
    std::vector<OrderBookEntry> BTC_USDT_1 = Candlestick::createIntervals(BTC_USDT, "2020/06/01 11:57:30", "2020/06/01 12:42:30");
    std::vector<OrderBookEntry> BTC_USDT_2 = Candlestick::createIntervals(BTC_USDT, "2020/06/01 12:42:30", "2020/06/01 13:27:30");
    std::vector<OrderBookEntry> BTC_USDT_3 = Candlestick::createIntervals(BTC_USDT, "2020/06/01 13:27:30", "2020/06/01 14:12:30");
    std::vector<OrderBookEntry> BTC_USDT_4 = Candlestick::createIntervals(BTC_USDT, "2020/06/01 14:12:30", "2020/06/01 14:57:00");

    /** DOGE/BTC */
    std::vector<OrderBookEntry> DOGE_BTC_1 = Candlestick::createIntervals(DOGE_BTC, "2020/06/01 11:57:30", "2020/06/01 12:42:30");
    std::vector<OrderBookEntry> DOGE_BTC_2 = Candlestick::createIntervals(DOGE_BTC, "2020/06/01 12:42:30", "2020/06/01 13:27:30");
    std::vector<OrderBookEntry> DOGE_BTC_3 = Candlestick::createIntervals(DOGE_BTC, "2020/06/01 13:27:30", "2020/06/01 14:12:30");
    std::vector<OrderBookEntry> DOGE_BTC_4 = Candlestick::createIntervals(DOGE_BTC, "2020/06/01 14:12:30", "2020/06/01 14:57:00");

    /** DOGE/USDT*/
    std::vector<OrderBookEntry> DOGE_USDT_1 = Candlestick::createIntervals(DOGE_USDT, "2020/06/01 11:57:30", "2020/06/01 12:42:30");
    std::vector<OrderBookEntry> DOGE_USDT_2 = Candlestick::createIntervals(DOGE_USDT, "2020/06/01 12:42:30", "2020/06/01 13:27:30");
    std::vector<OrderBookEntry> DOGE_USDT_3 = Candlestick::createIntervals(DOGE_USDT, "2020/06/01 13:27:30", "2020/06/01 14:12:30");
    std::vector<OrderBookEntry> DOGE_USDT_4 = Candlestick::createIntervals(DOGE_USDT, "2020/06/01 14:12:30", "2020/06/01 14:57:00");

    /** ETH/BTC*/
    std::vector<OrderBookEntry> ETH_BTC_1 = Candlestick::createIntervals(ETH_BTC, "2020/06/01 11:57:30", "2020/06/01 12:42:30");
    std::vector<OrderBookEntry> ETH_BTC_2 = Candlestick::createIntervals(ETH_BTC, "2020/06/01 12:42:30", "2020/06/01 13:27:30");
    std::vector<OrderBookEntry> ETH_BTC_3 = Candlestick::createIntervals(ETH_BTC, "2020/06/01 13:27:30", "2020/06/01 14:12:30");
    std::vector<OrderBookEntry> ETH_BTC_4 = Candlestick::createIntervals(ETH_BTC, "2020/06/01 14:12:30", "2020/06/01 14:57:00");

    /** ETH/USDT*/
    std::vector<OrderBookEntry> ETH_USDT_1 = Candlestick::createIntervals(ETH_USDT, "2020/06/01 11:57:30", "2020/06/01 12:42:30");
    std::vector<OrderBookEntry> ETH_USDT_2 = Candlestick::createIntervals(ETH_USDT, "2020/06/01 12:42:30", "2020/06/01 13:27:30");
    std::vector<OrderBookEntry> ETH_USDT_3 = Candlestick::createIntervals(ETH_USDT, "2020/06/01 13:27:30", "2020/06/01 14:12:30");
    std::vector<OrderBookEntry> ETH_USDT_4 = Candlestick::createIntervals(ETH_USDT, "2020/06/01 14:12:30", "2020/06/01 14:57:00");

    /**creating bar chart objects for each vector interval*/
    /**BTC/USDT*/
    BarChart BTC_USDT_Bar1 = BarChart::createBarChart(BTC_USDT_1, 0.0, "11:57:30 --> 12:42:30", "BTC/USDT");
    BarChart BTC_USDT_Bar2 = BarChart::createBarChart(BTC_USDT_2, BTC_USDT_Bar1.close, "12:42:30 --> 13:27:30" , "BTC/USDT");
    BarChart BTC_USDT_Bar3 = BarChart::createBarChart(BTC_USDT_3, BTC_USDT_Bar2.close, "13:27:30 --> 14:12:30", "BTC/USDT");
    BarChart BTC_USDT_Bar4 = BarChart::createBarChart(BTC_USDT_4, BTC_USDT_Bar3.close, "14:12:30 --> 14:57:00", "BTC/USDT");
    BTC_USDT_Bar1 = BarChart::createBarChart(BTC_USDT_1, BTC_USDT_Bar4.close, "11:57:30 --> 12:42:30", "BTC/USDT");

    /**DOGE/BTC*/
    BarChart DOGE_BTC_Bar1 = BarChart::createBarChart(DOGE_BTC_1, 0.0, "11:57:30 --> 12:42:30", "DOGE/BTC");
    BarChart DOGE_BTC_Bar2 = BarChart::createBarChart(DOGE_BTC_2, DOGE_BTC_Bar1.close, "12:42:30 --> 13:27:30", "DOGE/BTC");
    BarChart DOGE_BTC_Bar3 = BarChart::createBarChart(DOGE_BTC_3, DOGE_BTC_Bar2.close, "13:27:30 --> 14:12:30", "DOGE/BTC");
    BarChart DOGE_BTC_Bar4 = BarChart::createBarChart(DOGE_BTC_4, DOGE_BTC_Bar3.close, "14:12:30 --> 14:57:00", "DOGE/BTC");
    DOGE_BTC_Bar1 = BarChart::createBarChart(DOGE_BTC_1, DOGE_BTC_Bar4.close, "11:57:30 --> 12:42:30", "DOGE/BTC");

    /**DOGE/USDT*/
    BarChart DOGE_USDT_Bar1 = BarChart::createBarChart(DOGE_USDT_1, 0.0, "11:57:30 --> 12:42:30", "DOGE/USDT");
    BarChart DOGE_USDT_Bar2 = BarChart::createBarChart(DOGE_USDT_2, DOGE_USDT_Bar1.close, "12:42:30 --> 13:27:30", "DOGE/USDT");
    BarChart DOGE_USDT_Bar3 = BarChart::createBarChart(DOGE_USDT_3, DOGE_USDT_Bar2.close, "13:27:30 --> 14:12:30", "DOGE/USDT");
    BarChart DOGE_USDT_Bar4 = BarChart::createBarChart(DOGE_USDT_4, DOGE_USDT_Bar3.close, "14:12:30 --> 14:57:00", "DOGE/USDT");
    DOGE_USDT_Bar1 = BarChart::createBarChart(DOGE_USDT_1, DOGE_USDT_Bar4.close, "11:57:30 --> 12:42:30", "DOGE/USDT");

    /** ETH/BTC*/
    BarChart ETH_BTC_Bar1 = BarChart::createBarChart(ETH_BTC_1, 0.0, "11:57:30 --> 12:42:30", "ETH/BTC");
    BarChart ETH_BTC_Bar2 = BarChart::createBarChart(ETH_BTC_2, ETH_BTC_Bar1.close, "12:42:30 --> 13:27:30", "ETH/BTC");
    BarChart ETH_BTC_Bar3 = BarChart::createBarChart(ETH_BTC_3, ETH_BTC_Bar2.close, "13:27:30 --> 14:12:30", "ETH/BTC");
    BarChart ETH_BTC_Bar4 = BarChart::createBarChart(ETH_BTC_4, ETH_BTC_Bar3.close, "14:12:30 --> 14:57:00", "ETH/BTC");
    ETH_BTC_Bar1 = BarChart::createBarChart(ETH_BTC_1, ETH_BTC_Bar4.close, "11:57:30 --> 12:42:30", "ETH/BTC");

    /** ETH/USDT*/
    BarChart ETH_USDT_Bar1 = BarChart::createBarChart(ETH_USDT_1, 0.0, "11:57:30 --> 12:42:30", "ETH/USDT");
    BarChart ETH_USDT_Bar2 = BarChart::createBarChart(ETH_USDT_2, ETH_USDT_Bar1.close, "12:42:30 --> 13:27:30", "ETH/USDT");
    BarChart ETH_USDT_Bar3 = BarChart::createBarChart(ETH_USDT_3, ETH_USDT_Bar2.close, "13:27:30 --> 14:12:30", "ETH/USDT");
    BarChart ETH_USDT_Bar4 = BarChart::createBarChart(ETH_USDT_4, ETH_USDT_Bar3.close, "14:12:30 --> 14:57:00", "ETH/USDT");
    ETH_USDT_Bar1 = BarChart::createBarChart(ETH_USDT_1, ETH_USDT_Bar4.close, "11:57:30 --> 12:42:30", "ETH/USDT");

    std::vector<BarChart> BarCharts = {BTC_USDT_Bar1,BTC_USDT_Bar2,BTC_USDT_Bar3,BTC_USDT_Bar4,DOGE_BTC_Bar1,
                                       DOGE_BTC_Bar2,DOGE_BTC_Bar3,DOGE_BTC_Bar4,DOGE_USDT_Bar1,DOGE_USDT_Bar2,
                                       DOGE_USDT_Bar3,DOGE_USDT_Bar4,ETH_BTC_Bar1,ETH_BTC_Bar2,ETH_BTC_Bar3,
                                       ETH_BTC_Bar4,ETH_USDT_Bar1,ETH_USDT_Bar2,ETH_USDT_Bar3,ETH_USDT_Bar4};
    return BarCharts;
}

/** create barchart visualization*/
void BarChart::createBarChart(std::vector<BarChart> BarCharts)
{
    const int maxChars = 50;

    /** find the lowest and highest closing price of each product, so every product is scaled on its own*/
    std::map<std::string, double> lowestPrice;
    std::map<std::string, double> highestPrice;
    for (int i = 0; i < BarCharts.size(); ++i)
    {
        const std::string &product = BarCharts[i].productType;
        if (highestPrice.count(product) == 0)
        {
            lowestPrice[product] = BarCharts[i].close;
            highestPrice[product] = BarCharts[i].close;
        }
        else
        {
            lowestPrice[product] = std::min(lowestPrice[product], BarCharts[i].close);
            highestPrice[product] = std::max(highestPrice[product], BarCharts[i].close);
        }
    }

    std::cout << "Bar Chart: periods where the price rose, with the closing price between each product's lowest and highest close" << std::endl;

    for (int i = 0; i < BarCharts.size(); ++i)
    {
        if (BarCharts[i].close > BarCharts[i].open)
        {
            const std::string &product = BarCharts[i].productType;
            double priceRange = highestPrice[product] - lowestPrice[product];

            /** calc position of closing price */
            int closePos = maxChars - 1;
            if (priceRange > 0.0)
            {
                closePos = static_cast<int>((BarCharts[i].close - lowestPrice[product]) / priceRange * (maxChars - 1));
            }

            /** time interval, product, barchart visualization*/
            std::cout << BarCharts[i].timeInterval << " | " << BarCharts[i].productType << " | ";
            for (int j = 0; j < maxChars; ++j)
            {
                if (j >= 0 && j <= closePos)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}
