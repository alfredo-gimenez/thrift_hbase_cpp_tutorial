#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <boost/lexical_cast.hpp>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "gen-cpp/Hbase.h"

using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace apache::hadoop::hbase::thrift;

int main(int argc, char** argv)
{
    /* Connection to the Thrift Server */
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    HbaseClient client(protocol);

    try {
        transport->open();

        vector<string> tables;
        client.getTableNames(tables);

        cout << "Tables: " << endl;
        for(int i=0; i<tables.size(); i++) {
            cout << tables[i] << endl;
        }
    } catch (const TException &tx) {
        cerr << "Error: " << tx.what() << endl;
    }
}
