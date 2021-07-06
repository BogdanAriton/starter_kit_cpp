#include <iostream>
#include <string>
#include <thread>

#include "arg-parser.h"
#include "book.h"
#include "input-parser.h"
#include "analyzer.h"


void analyzeBookAdd(const EntryData& data, Asks&, Bids&);
void analyzeBookUpdate(const EntryData& data, Asks&, Bids&);

int main(int argc, char* argv[])
{
    ArgParser argParser;
    if (!argParser.isInputValid(argc, argv)) return 0;

    Book tradeBook;
    /* The producer thread will add entries to the book 
       and notify a consumer to start working */
    std::thread producer([&]() {
            std::string line;
            InputParser parser;
            while (std::getline(std::cin, line))
            {
                EntryData entry = parser.getEntry(line);
                if (entry.isEmpty()) continue;
                tradeBook.addEntryToBook(entry);
                line.clear();
            }
            // an empty entry indicates last line in the book
            tradeBook.addEntryToBook({});
        });

    /* The consumer thread will take an entry from the book 
       and start analysis */
    std::thread consumer([&](){
        Asks asks(argParser.getTargetSize());
        Bids bids(argParser.getTargetSize());
        while (true)
        {
            EntryData data = tradeBook.getEntryFromBook();
            if (data.isEmpty()) break;
            else
            {
                if (data.action == static_cast<char>(Action::add)) analyzeBookAdd(data, asks, bids); 
                else if (data.action == static_cast<char>(Action::update)) analyzeBookUpdate(data, asks, bids);
            }
        }
    });

    consumer.join();
    producer.join();

    return 0;
};

/* Checks if a give entry is either an ask or a bid
   Adds the entry to the coresponding book
   Runs analysis on the book.
 */
void analyzeBookAdd(const EntryData& entry, Asks& asks, Bids& bids)
{
    if (entry.type == static_cast<char>(Type::ask))
    {
        Analyzer<Action::add>::execute(entry, asks);
        Output<PrintAction::print>::print(Analyzer<Action::analyze>::execute(entry, asks));
    }
    else if (entry.type == static_cast<char>(Type::bid))
    {
        Analyzer<Action::add>::execute(entry, bids);
        Output<PrintAction::print>::print(Analyzer<Action::analyze>::execute(entry, bids));
    }
}

/* Checks if a give entry is either an ask or a bid
   Updates the entry to the coresponding book
   Runs analysis on the book.
 */
void analyzeBookUpdate(const EntryData& entry, Asks& asks, Bids& bids)
{
    if (asks.isEntryPresent(entry.orderID))
    {
        Analyzer<Action::update>::execute(entry, asks);
        Output<PrintAction::print>::print(Analyzer<Action::analyze>::execute(entry, asks));
    }
    else if (bids.isEntryPresent(entry.orderID))
    {
        Analyzer<Action::update>::execute(entry, bids);
        Output<PrintAction::print>::print(Analyzer<Action::analyze>::execute(entry, bids));
    }
}