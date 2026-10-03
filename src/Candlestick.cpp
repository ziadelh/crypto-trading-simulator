#include "Candlestick.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include "CSVReader.h"
#include "OrderBook.h"
#include "DataFile.h"

Candlestick::Candlestick(std::string _date,
                         double _open,
                         double _high,
                         double _low,
                         double _close)
    : date(_date),
      open(_open),
      high(_high),
      low(_low),
      close(_close)
{
}

std::vector<OrderBookEntry> Candlestick::orders_sub = {};

int Candlestick::userOption = 0;

/** read the data file the first time it is needed, not at program start-up*/
const std::vector<OrderBookEntry>& Candlestick::getEntries()
{
    static const std::vector<OrderBookEntry> entries = CSVReader::readCSV(DATA_FILE);
    return entries;
}


std::vector<std::string> Candlestick::options = {
                                                    "Go back to main menu",
                                                    "BTC/USDT,ask",
                                                    "BTC/USDT,bid",
                                                    "DOGE/BTC,ask",
                                                    "DOGE/BTC,bid",
                                                    "DOGE/USDT,ask",
                                                    "DOGE/USDT,bid",
                                                    "ETH/BTC,ask",
                                                    "ETH/BTC,bid",
                                                    "ETH/USDT,ask",
                                                    "ETH/USDT,bid"};

/** print candle stick menu*/
void Candlestick::printCandlestickMenu()
{
    for (int i = 0; i < options.size(); ++i)
    {
        std::cout << i << ": " << options[i] << std::endl;
    }
}

/** tokenise user option*/
std::vector<std::string> Candlestick::tokenising(int userOption)
{
    std::vector<std::string> tokens;
    if (userOption > 0 && userOption < static_cast<int>(options.size()))
    {
        tokens = CSVReader::tokenise(options[userOption], ',');
        std::cout << "Product: " << tokens[0] << ", OrderType: " << tokens[1] << std::endl;
    }
    return tokens;
}

/** filter products based on tokens*/
std::vector<OrderBookEntry> Candlestick::filter_products(std::vector<std::string> tokens)
{
    Candlestick::orders_sub.clear();
    if (tokens.size() < 2)
    {
        return Candlestick::orders_sub;
    }
    std::string product = tokens[0];
    OrderBookType OrderType;
    OrderType = OrderBookEntry::stringToOrderBookType(tokens[1]);
    for (const OrderBookEntry &e : getEntries())
    {
        if (e.orderType == OrderType &&
            e.product == product)
        {
            Candlestick::orders_sub.push_back(e);
        }
    }
    return Candlestick::orders_sub;
}

/**calc the closing price */
double Candlestick::calculateClosingPrice(std::vector<OrderBookEntry> orders)
{
    double total_Value = 0.0;
    double total_Amount = 0.0;

    for (int i = 0; i < orders.size(); ++i)
    {
        double value = orders[i].price * orders[i].amount;
        total_Value += value;
        total_Amount += orders[i].amount;
    }

    double closing_price = total_Value / total_Amount;
    return closing_price;
}

/**create candlestick object */
Candlestick Candlestick::createCandlestick(std::vector<OrderBookEntry> orders, double open_price, std::string timing)
{
    std::string date = timing;
    double open = open_price;
    double high = OrderBook::getHighPrice(orders);
    double low = OrderBook::getlowPrice(orders);
    double close = Candlestick::calculateClosingPrice(orders);

    Candlestick candlestick{date,open,high,low,close};
    return candlestick;
}

/** create intervals of orderbookentry based on dates */
std::vector<OrderBookEntry> Candlestick::createIntervals(std::vector<OrderBookEntry> orders, std::string date_1, std::string date_2)
{
    std::vector<OrderBookEntry> orders_separated;

    for (int i = 0; i < orders.size(); ++i)
    {
        if (date_1 <= orders[i].timestamp && orders[i].timestamp < date_2)
        {
            orders_separated.push_back(orders[i]);
        }
    }

    return orders_separated;
}

/**create vector of candlestick objects */
std::vector<Candlestick> Candlestick::createCandlestickVector ()
{
    std::vector<OrderBookEntry> orders_1 = Candlestick::createIntervals(Candlestick::orders_sub, "2020/06/01 11:57:30", "2020/06/01 12:27:30");
    std::vector<OrderBookEntry> orders_2 = Candlestick::createIntervals(Candlestick::orders_sub, "2020/06/01 12:27:30", "2020/06/01 12:57:30");
    std::vector<OrderBookEntry> orders_3 = Candlestick::createIntervals(Candlestick::orders_sub, "2020/06/01 12:57:30", "2020/06/01 13:27:30");
    std::vector<OrderBookEntry> orders_4 = Candlestick::createIntervals(Candlestick::orders_sub, "2020/06/01 13:27:30", "2020/06/01 13:57:30");
    std::vector<OrderBookEntry> orders_5 = Candlestick::createIntervals(Candlestick::orders_sub, "2020/06/01 13:57:30", "2020/06/01 14:27:30");
    std::vector<OrderBookEntry> orders_6 = Candlestick::createIntervals(Candlestick::orders_sub, "2020/06/01 14:27:30", "2020/06/01 14:56:37");

    Candlestick candlestick_one = Candlestick::createCandlestick(orders_1, 0.0, "11:57:30 --> 12:27:30");
    Candlestick candlestick_two = Candlestick::createCandlestick(orders_2, candlestick_one.close, "12:27:30 --> 12:57:30");
    Candlestick candlestick_three = Candlestick::createCandlestick(orders_3, candlestick_two.close, "12:57:30 --> 13:27:30");
    Candlestick candlestick_four = Candlestick::createCandlestick(orders_4, candlestick_three.close, "13:27:30 --> 13:57:30");
    Candlestick candlestick_five = Candlestick::createCandlestick(orders_5, candlestick_four.close, "13:57:30 --> 14:27:30");
    Candlestick candlestick_six = Candlestick::createCandlestick(orders_6, candlestick_five.close, "14:27:30 --> 14:56:36");
    candlestick_one = Candlestick::createCandlestick(orders_1, candlestick_six.close, "11:57:30 --> 12:27:30");


    std::vector<Candlestick> Candlesticks = {candlestick_one, candlestick_two, candlestick_three, candlestick_four, candlestick_five, candlestick_six};
    return Candlesticks;
}

/** create candle stick plot*/
void Candlestick::createCandlestickPlot(std::vector<Candlestick> Candlesticks)
{
    if (Candlesticks.empty())
    {
        return;
    }
    const int graphWidth = 50;

    // scale between the lowest low and the highest high so the candles fill the width
    double minPrice = Candlesticks[0].low;
    double maxPrice = Candlesticks[0].high;
    for (const auto &candle : Candlesticks)
    {
        minPrice = std::min({minPrice, candle.open, candle.high, candle.low, candle.close});
        maxPrice = std::max({maxPrice, candle.open, candle.high, candle.low, candle.close});
    }
    double priceRange = maxPrice - minPrice;
    if (priceRange <= 0.0)
    {
        priceRange = 1.0;
    }
    auto toColumn = [&](double price)
    {
        return static_cast<int>((price - minPrice) / priceRange * (graphWidth - 1));
    };

    std::cout << "Candlestick Plot:" << std::endl;
    std::cout << "Price scale: " << minPrice << " (left) to " << maxPrice << " (right)" << std::endl;

    for (const auto &candle : Candlesticks)
    {
        std::cout << candle.date << " | ";

        if (candle.close < candle.open)
        {
            std::cout << "\033[31m";
        }
        else
        {
            std::cout << "\033[32m";
        }

        int openPos = toColumn(candle.open);
        int highPos = toColumn(candle.high);
        int lowPos = toColumn(candle.low);
        int closePos = toColumn(candle.close);

        for (int i = 0; i < graphWidth; ++i)
        {
            if (i >= lowPos && i <= highPos)
            {
                if (i == openPos || i == closePos)
                {
                    std::cout << '%';
                }
                else
                {
                    std::cout << '|';
                }
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << "\033[0m" << std::endl;
    }
}
