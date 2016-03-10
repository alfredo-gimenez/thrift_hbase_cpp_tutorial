# Thrift C++ Example

This project shows how to use Thrift from C++ in a simple example.

Thrift allows different languages to communicate to a common server. HBase includes a Thrift server and the necessary bindings to connect to it and perform HBase operations--if you can do it throught the HBase shell, you can probably do it through Thrift.

## Install Thrift

Thrift is available on [Spack](https://github.com/LLNL/spack). You can also download prebuilt binaries at https://thrift.apache.org/.

## Generate Thrift C++ Bindings for HBase

The first step is to use Thrift to generate the C++ headers and code that we have to use from our client code. 

Thrift takes in a Thrift Definition File, usually `something.thrift` and generates bindings for different languages. Because HBase includes a Thrift server, they also include a Thrift Definition File for its included Thrift server.

The HBase Thrift Definition File can be found in the HBase installation, possibly `$MY_HBASE_INSTALLATION_PATH/include/thrift/`. There are actually two files there, `hbase1.thrift` and `hbase2.thrift`. They provide slightly different interfaces to HBase. In this tutorial, we use `hbase1.thrift`.

To generate the C++ bindings:

```sh
thrift --gen cpp /path/to/hbase1.thrift
```

This will create a directory `gen-cpp` wherever you ran the command, containing the necessary C++ bindings to the HBase Thrift server.

## Compiling With Generated C++ Thrift Bindings

To compile the generated code, we just need to make sure we compile the `*.cpp` files in `gen-cpp` and link the Thrift library.

We can do this by making a `main` skeleton in `client.cpp` and compile it using:

```sh
g++ client.cpp gen-cpp/*.cpp -lthrift
```

If that works, we can move on to the actual code.

## Creating an HBase Thrift Client

In `client.cpp` we need the following headers:

```cpp
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include <boost/lexical_cast.hpp> // Thrift requires boost shared pointers

#include "gen-cpp/Hbase.h" // Include the generated HBase header
```

In addition we need to use Thrift namespaces:

```cpp
using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace apache::hadoop::hbase::thrift;
```

And now we can use the API!

See `client.cpp` in this repository for a simple example.

## Starting the HBase Server

First, the HBase server has to be running for the client to connect to it.

On an installed, running instance of HBase, that just requires the following command:

```sh
hbase thrift start &
```

Which will start a Java process. Verify that it is running using:

```sh
jps
```

You should see `ThriftServer` in there.

Now, compile and run `client.cpp`. You should get a list of HBase tables, similar to what you get from the `list` command in an hbase shell.

## Advanced 

To do more than just list tables, look at the functions in `gen-cpp/Hbase.h`, particularly the member functions of the `HbaseClient` class.
