#ifndef BOOK_DEF
#define BOOK_DEF

#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "entry-data.h"

class Book
{
public:
    void addEntryToBook(const EntryData& entry) noexcept
    {
        std::unique_lock<std::mutex> lock(book_look);
        bookStream.push(entry);
        lock.unlock();
        book_consumer.notify_one();
    }

    EntryData getEntryFromBook() noexcept
    {
        std::unique_lock<std::mutex> lock(book_look);
        while (bookStream.empty())
        {
            book_consumer.wait(lock);
        }
        EntryData data = bookStream.front();
        bookStream.pop();
        return data;
    }

private:
    void popFront() noexcept
    {
        std::unique_lock<std::mutex> lock(book_look);
        bookStream.pop();
    }

    mutable std::mutex book_look;
    std::queue<EntryData> bookStream{};
    std::condition_variable book_consumer;
};

#endif