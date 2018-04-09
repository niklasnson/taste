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
