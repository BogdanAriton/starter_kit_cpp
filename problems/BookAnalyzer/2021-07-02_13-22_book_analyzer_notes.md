You have 3000 $

# BUYING!
    You want to buy ZING shares

    How do you do that?
        - You go to your trading account and set the following BID (when you BID you will try to buy thing at a certain price)

    ! BUY 100 ZING @ 30
        
        The above translates into:
            - I want to BUY
            - Price is lower or equal to 30
            - 100 units
    
        Other prospectors:

    ! BUY 200 ZING @ 31

        This guy is outbidding you because his price is higher and he will buy shares before you.
        Why? Because the person who sells will go to the highest price first and then sell, until the number of shares in the BID is exhausted

    ! BUY 300 ZING @ 29

        Well, now this guy will be the last out of the three of you to actually buy.
        Why? Because the poor sucker is trying to save 1 buck/share at the cost of time.
        He may have to adjust while the price gets higher and higher.

# SELLING!
    How does selling work?
    Well you can take a look in the list of BUYers - which are the current offers right now and pick the highest price.

    Here is Mark and he has 225 shares and he want to sell everything as fast as possible with the best price possible.
    He will pick the highest price out of the 3 which is 31 and sell 225 - how many shares there are available at that price which is 200 = and the remainder 25 will go to the next bidder which is you with 30 $ - and you want to buy 100 so he will sell you 100 - (225 - 200) and you still have 75 share that you need to buy.

    This kind of gets translated into the following:
    SELL 225 ZING @ 31
    SELL 25 ZING @ 30 

New scenario:
    You are the seller now, and you're trying to get 4500$.
    You know that ZING shares value have risen by 50% making them now 45$/share.
    So you can sell 100 shares for 45$ each.

    SELL 100 ZING @ 45 - this is you ASK

    Like the last time sellers are also in competition.
    Aside from your ask there are other sellers:

    SELL 50  ZING @ 44
    SELL 400 ZING @ 46

    Since you're somewhere in the middle you're going to have to wait until the seller before you has ran out of shares.

    IF this guys Jim comes in and wants to buy shares from ZING will buy first at the lowest price and then buy the rest from you.
    So just as before we can think about a BID like this:

    BUY 100 ZING @ 44
    The 44 guys will be sold out and the rest 50 will be bought at 45 which is your price and you will still have 50 Shares not sold.

# Limit order book - or in short Book
    It's the set of all standing bids and asks - which are all buyers and sellers that currently are waiting to transact.

    You can get this information feed from the stock market in a form of a log that constantly gets updated in real time.
    The updates will tell you about adding an order to the book or reducing the size of an order in a book (down to maximum 0 that would mean it will be removed)


# The problem:
    Write up a program that takes one command line argument called: target-size.