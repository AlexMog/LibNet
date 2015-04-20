## Synopsis

LibNet is a network Framework-library, that is imagined to simplify the creation of networking programs.
It was first imagined for the mmo developpement framework "Highlands Framework", and is now opensource and public.
The library is simple and fast to use, and is adapted for every type of protocol (text, binary, ...)

## Features
   - TCP and UDP socket management
   - TCP asynchronous built-in server and client.
   - Multiple protocol type support.
   - Multiple languages supported (currently, we are working on a C# version and a java version).
   - A Packet object to manage multiple datas packet.
   - Encapsulated functions turned to Java-Like Objects (Mutex, CondVar, Thread, Selector, ...).
   - A complete documentation.
   - Simple to use.
   - Trying to be very optimized.
   - Simple to install (using CMake).
   - Windows (not yet), Mac and Linux compatible.

## Code Example
Here is an example of the creation of a server.

```C++
#include <mognetwork/TcpASIOServer.hh>

int main(void)
{
	mognetwork::TcpASIOServer server(4242, Binary);

	server.start();

	return 0;
}
```

You can find more examples in the [test directory](https://github.com/AlexMog/LibNet/tree/master/test/)

## Motivation

We created this project at first to our project "Highlands Framework". Then, because we really like the OpenSource community and world, we decided to set that library as an OpenSource project.
The library is going to be adapted to C#, Java, and mabe more languages.

## Installation

You can find an installation guide in the wiki!

## Getting support

You can get support by simply contacting me (moghra_a [ @ ] epitech.eu).
If you find an issue, please use the [issues tracker](https://github.com/AlexMog/LibNet/issues)

## API Reference

The documentation can be found [there.](http://alexmog.labs-epimars.eu/projets/mognetwork-doc/doc/html/index.html)


## Contribute

LibNet is an open-source project, and it needs your help to go on growing and improving.
If you want to get involved and suggest some additional features, file a bug report or submit a patch, you can fork this repository and ask for a pull request. You can alsow contact me for more informations!

