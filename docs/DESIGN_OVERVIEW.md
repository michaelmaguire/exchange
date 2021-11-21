# Basic design today

A set of processes are arranged around a UDP multicast 'bus'.  Input nodes on the edge of the system will accept order inputs from external sources (such as other financial institutions or an exchanges trading web front end) and introduce orders into the system by serializing the orders as UDP message packets.  


![Initial system](/docs/Today_UDP_multicast_exchange_diagram.jpeg)

Currently Google Protobufs was chosen to encode message data for UDP package transmission, but different, possibly more efficient packet formats could we switched to in the future thanks to a 4 byte little-endian packet "magic" identifier and 4 byte version number prefixed into each packet (always version your formats!).

For modularity, simplicity and performance (avoiding interthread communication bottlenecks and complexity), the order book for an individual security is individual processes.  That is, to run an order book for `IBM`, we arrange for an instance of the order book application to be fired up.  

That application instance would listen on the multicast bus for orders for that symbol, ignoring all others. 

To also deal in `APPL` or `MMM` we would fire up an order book application for each of those symbols.

When an order for its symbol comes in, the order book application instance would incorporate the new order into its order book, updating its internal order book structures as necessary.

If orders cross and a trade is made, the order book application instance would broadcast this to the multicast bus.

Nodes on the bus interested in trade results (including possibly the input edge node which first issued the order) can listen for these trade notifications and take action.

In our case we have an output edge node writing to the console.


# Possible enhancements

![Possible enhancements](/docs/Possible_UDP_multicast_exchange_diagram.jpeg)
