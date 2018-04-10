#include <gtest/gtest.h>
#include "server.h"
#include "client.h"
#include "package.h"

struct PackageTest : testing::Test {
	Server* server;
	Client* client;

	PackageTest() {
		server = new Server();
		client = new Client(*server);
	}
	virtual ~PackageTest() {
		delete server;
		delete client;
	}
};


TEST_F(PackageTest, Creation) {
	ASSERT_TRUE(server != nullptr);
}


TEST_F(PackageTest, SendSome) {
  client -> send_packages(1); 
  std::vector<Package> compare{Package(0)}; 
  ASSERT_EQ(server -> get_log(), compare); 

  std::vector<Package> compare2{Package(0),
                                Package(0), 
                                Package(1),
                                Package(2),
                                Package(3),
                                Package(4),
                                Package(5),
                                Package(6),
                                Package(7),
                                Package(8),
                                Package(9)}; 
  client -> send_packages(10);
  EXPECT_EQ(server -> get_log(), compare2); 

} 


