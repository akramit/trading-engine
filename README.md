# trading-engine


A trading engine is a platform where market orders are placed and buyers and sellers are matched for their trades. Below is the description and a program for the same.

# Types of Orders
There are two kind of orders - 
1. Limit Order - A Limit order is an order where a buyer is not willing to buy above their quoted buying price and a seller is not willing to sell below their quoted price. 

2. Market Order  - A Market order is an order where a buyer (or a seller) want to buy(or sell) at the marker price. For example - Suppose there is an MO with "BUY 150". Then, the buyer will be matched to all the sellers without considering any price margin (but giving priority to highest selling price order).

# Test Case
1. There are orders submitted - "SUB LO B price qty" or "SUB MO B qty"
2. It also supports "CXL orderId" which cancels the order i.e. remove from the order book.
2. Sellers/Buyers are mathced and orders are executed. Remaining amount of order in case of Limit Order are added to the Buy/Sell Book and in case of Market Order are cancelled. 
3. Return the total value transacted.
4. Finally, output the final Buy Book and Sell Book.

Example Test Case - 
```SUB LO B 500 10 id1
SUB MO B 100 20 id2
SUB MO S 100 13 id3
CXL iD
```

Output: 
```
0
0
0
2000
B: 150@10#id1, 2@20#id2
S: 
```
