#ifndef BOOK_PARSER
#define BOOK_PARSER

#include <iostream>
#include <sstream>
#include <queue>
#include "book.h"
#include "analyzer.h"

struct InputParser
{
    EntryData getEntry(const std::string &line)
    {
        std::stringstream tokens(line);
        EntryData entry;
        tokens >> entry.timeStamp;
        tokens >> entry.action;
        tokens >> entry.orderID;
        if (entry.action == static_cast<char>(Action::add))
        {
            tokens >> entry.type;
            tokens >> entry.price;
            tokens >> entry.size;
        }
        else if (entry.action == static_cast<char>(Action::update))
        {
            tokens >> entry.size;
        }

        return entry;
    }
};

#endif