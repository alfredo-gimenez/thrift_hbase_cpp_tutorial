client: client.cpp
	g++ client.cpp gen-cpp/Hbase.cpp gen-cpp/hbase1_constants.cpp gen-cpp/hbase1_types.cpp -lthrift
