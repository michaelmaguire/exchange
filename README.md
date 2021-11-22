# exchange

A small experiment with an exchange system using C++ and boost ASIO which implements a series of order book handlers arranged around a UDP multicast bus.

# Building

Apologies, but I have a Mac so I built this on my Mac.  I used Eclipse CDT as my IDE and build environment.

I used homebrew to get dependencies:

```
brew install gtest
brew install gdb
brew install boost
brew install protobuf
```

As it turns out brew uses clang to compile, which means that attempt to build with g++ while using homebrew causes standard library incompatibilies.  So I have built with:

```
Apple clang version 13.0.0 (clang-1300.0.29.3)
Target: x86_64-apple-darwin20.6.0
Thread model: posix
```


# Design

See [DESIGN_OVERVIEWER](docs/DESIGN_OVERVIEW.md)

This program is designed to leverage a distributed UDP multicast bus for order management.

Rather than having a single instance of the executable manage order books for all symbols, I chose to design the system to hang one order book handling instance off the bus per security.  With proper containerization, this should not be onerous to distribute.  One could consolidate books into a single executable instance but in my view this would a pessimization in terms of scaling and complexity.

Input connectors, order books and console trade reporting are each their own process.

For rapid prototyping in order to re-use connectivity classes, I've used the same binary, which supports being invoked in 4 different modes:

# Running

```
michaelmaguire@Michaels-Mac-mini exchange % ./exchange/Debug/exchange
[2021-11-22 03:52:49.422661] [0x000000010b4b6e00] [info]    In main() setting UDP multicast port[1234]

Missing mode
Allowed options:
  -h [ --help ]         produce help message
  --test                run tests
  --client              run in client mode reading CSV
  --filename arg        path to .CSV for --client mode
  --book                run in order book mode on symbol --symbol
  --symbol arg          symbol to run order book for --book mode
  --output              run in output logger more
  --port arg (=1234)    set multicast UDP port
```

With more time, I would move common functionality into separate library packages, so that each mode of this program would have its own binary.


First start up an output mode instance for console output from the system:

```
michaelmaguire@Michaels-Mac-mini exchange % ./exchange --output
```

Then start up an instance for every symbol your exchange should handle:

```
michaelmaguire@Michaels-Mac-mini exchange % ./exchange --book --symbol AAPL &
michaelmaguire@Michaels-Mac-mini exchange % ./exchange --book --symbol IBM &
michaelmaguire@Michaels-Mac-mini exchange % ./exchange --book --symbol VAL
```

Finally run the CSV reading client against your `inputFile.csv`:

```
michaelmaguire@Michaels-Mac-mini exchange % ./exchange --client --filename inputFile.csv
```

Note that with proper network configuration, you should need to start all of these instances on the same machine.







