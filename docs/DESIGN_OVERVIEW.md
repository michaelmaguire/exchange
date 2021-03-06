# Basic design today

We propose a set of processes distributed around a UDP multicast 'bus'.  Input nodes on the edge of the system will accept order inputs from external sources (such as, our test app or our CSV reader) and introduce orders into the system by serializing the orders as UDP message packets.  


![Initial system](/docs/Today_UDP_multicast_exchange_diagram.jpeg)


The design of the system effectively represents an inversion of the traditional database-centered approach from decades ago.  Rather a massive central (Oracle?) database with applications each making queries, we have a decentralized cluster of applications circulating binary sync message amonsgt themselves, filtering and acting on only those relevant to themselves.

Currently Google Protobufs was chosen to encode message data for UDP packet transmission, but different, possibly more efficient packet formats could we switched to in the future thanks to a 4 byte little-endian packet "magic" identifier and 4 byte version number prefixed into each packet (always version your formats!).

For modularity, simplicity and performance (avoiding interthread communication bottlenecks and complexity), the order book for an individual security is individual processes.  That is, to run an order book for `IBM`, we arrange for an instance of the order book application to be fired up.  

That application instance would listen on the multicast bus for orders for that symbol, ignoring all others. 

To also deal in `APPL` or `MMM` we would fire up an order book application for each of those symbols.

When an order for its symbol comes in, the order book application instance would incorporate the new order into its order book, updating its internal order book structures as necessary.

To deal with the loss-ful nature of UDP, sequence numbers in packages can be used to ensure recovery in the case of loss.  Nodes will ensure they they see every number in the sequence, and report an error if they miss a packet.  As a future implementation detail discussed below, Bus Message Cache Server nodes would listen to the bus and be ready to accept TCP-based catch-up requests when nodes notice that they have fallen behind and missed a packet.

If orders cross and a trade is made, the order book application instance would broadcast this to the multicast bus.

Nodes on the bus interested in trade results (including possibly the input edge node which first issued the order) can listen for these trade notifications and take action.

In our case we have an output edge node writing to the console.


# Possible enhancements

Input edge nodes could be expanded to support a variety to external connectors.  For example a FIX input connected could be added to allow connectivity from banks and other financial institutions.  

A standards-based FIX input connector would also immediately make available a plethora of off-the-shelf FIX exchange testing tools for end-to-end testing.

Rather than a single UDP multicast bus, we could choose to use multiple UDP multicast buses in order to avoid overloading.  For instance, order input could be handled on one bus, which trade confirmation notices could be passed on a different bus. 

Additionally, to protect system integrity, a decision might be made that one 'request' multicast channel is available for all nodes to advertise and make order requests, but authoritative commands will only be issued by a central 'bus manager' node to another multicast command channel.  The bus manager node would verify order integrity of a message received on the 'request' channel before re-publishing the message on the command channel.  Order book processing nodes would only heed orders sent by the bus manager on the command channel.

Several kinds of database nodes would listen on the bus for all messages and store them appropriately.  

A database technology with native support for our protobuf packets such as MongoDB could be used to store each message.  This would provide replay functionality for testing parallel QA systems, as well as compliance support for understanding issues that arise.

Other database nodes might filter for orders in order to collate them into a SQL database with rows for each order which get updated as the order progresses through its stages towards completion.  Similarly this might be done for trade confirmations.  These databases would be useful for batch and interactive queries of order status.

In terms of hardware implementation, a separate, dedicated network card could be used for the multicast bus communication.  Indeed, separate physical cards could be used for order versus trade confirmation channels.

![Possible enhancements](/docs/Possible_UDP_multicast_exchange_diagram.jpeg)
