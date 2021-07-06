#include <gtest/gtest.h>
#include "book.h"
#include "orders.h"
#include "analyzer.h"

EntryData askEntry1 = {"28800538", 'A', "b", 'S', 44.26, 100};
EntryData bidEntry1 = {"28800562", 'A', "c", 'B', 44.10, 100};
EntryData updateEntry1 = {"28800744", 'R', "b", '\0', 0, 100};
EntryData bidEntry2 = {"28800758", 'A', "d", 'B', 44.18, 157};
EntryData askEntry2 = {"28800773", 'A', "e", 'S', 44.38, 100};
EntryData updateEntry2 = {"28800796", 'R', "d", '\0', 0, 157};
EntryData bidEntry3 = {"28800812", 'A', "f", 'B', 44.18, 157};
EntryData askEntry3 = {"28800974", 'A', "g", 'S', 44.27, 100};

TEST(analyzer, analyzeAsk)
{
    int targetSize = 200;
    OutputData data;
    Book tradeBook;
    Asks asks(targetSize);

    tradeBook.addEntryToBook(askEntry1);
    Analyzer<Action::add>::execute(askEntry1, asks);
    ASSERT_EQ(tradeBook.getEntryFromBook(), askEntry1);

    data = Analyzer<Action::analyze>::execute(askEntry1, asks);
    ASSERT_EQ(data.action, PrintAction::dontPrint);

    tradeBook.addEntryToBook(updateEntry1);
    Analyzer<Action::update>::execute(updateEntry1, asks);
    ASSERT_EQ(tradeBook.getEntryFromBook(), updateEntry1);

    data = Analyzer<Action::analyze>::execute(updateEntry1, asks);
    ASSERT_EQ(data.action, PrintAction::dontPrint);

    tradeBook.addEntryToBook(askEntry2);
    Analyzer<Action::add>::execute(askEntry2, asks);
    ASSERT_EQ(tradeBook.getEntryFromBook(), askEntry2);
    
    data = Analyzer<Action::analyze>::execute(askEntry2, asks);
    ASSERT_EQ(data.action, PrintAction::dontPrint);

    tradeBook.addEntryToBook(askEntry3);
    Analyzer<Action::add>::execute(askEntry3, asks);
    ASSERT_EQ(tradeBook.getEntryFromBook(), askEntry3);
    
    data = Analyzer<Action::analyze>::execute(askEntry3, asks);
    ASSERT_EQ(data.action, PrintAction::printValue);
    std::string type{data.type};
    std::string printout = data.timeStamp + " " + type + " " + Output<PrintAction::trim>::trimZeros(data.value);
    ASSERT_EQ(printout, "28800974 B 8865.00");
}

TEST(analyzer, analyzeBid)
{
    int targetSize = 200;
    Book tradeBook;
    OutputData data;
    Bids bids(targetSize);

    tradeBook.addEntryToBook(bidEntry1);
    Analyzer<Action::add>::execute(bidEntry1, bids);
    ASSERT_EQ(tradeBook.getEntryFromBook(), bidEntry1);

    data = Analyzer<Action::analyze>::execute(bidEntry1, bids);
    ASSERT_EQ(data.action, PrintAction::dontPrint);

    tradeBook.addEntryToBook(bidEntry2);
    Analyzer<Action::add>::execute(bidEntry2, bids);
    ASSERT_EQ(tradeBook.getEntryFromBook(), bidEntry2);

    data = Analyzer<Action::analyze>::execute(bidEntry2, bids);
    ASSERT_EQ(data.action, PrintAction::printValue);

    std::string type{data.type};
    std::string printout = data.timeStamp + " " + type + " " + Output<PrintAction::trim>::trimZeros(data.value); 
    ASSERT_EQ(printout, "28800758 S 8832.56");

    tradeBook.addEntryToBook(updateEntry2);
    Analyzer<Action::update>::execute(updateEntry2, bids);
    ASSERT_EQ(tradeBook.getEntryFromBook(), updateEntry2);

    data = Analyzer<Action::analyze>::execute(updateEntry2, bids);
    ASSERT_EQ(data.action, PrintAction::printNA);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}