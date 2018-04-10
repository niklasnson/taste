#include <gtest/gtest.h>
#include "client.h"
#include "message.h"
#include "inbox.h"

struct PackageTest : testing::Test {
	Inbox<Client>* inbox;
	Client* alice;

	PackageTest() {
		inbox = new Inbox<Client>();
		alice = new Client("Alice", *inbox);
	}
	virtual ~PackageTest() {
		delete alice;
		delete inbox;
	}
};


TEST_F(PackageTest, Creation) {
	ASSERT_TRUE(inbox != nullptr);
	ASSERT_TRUE(alice != nullptr);
}


// TEST_F(PackageTest, SendSome) {
//   client -> send_packages(1); 
//   std::vector<Package> compare{Package(0)}; 
//   ASSERT_EQ(server -> get_log(), compare); 
// 
//   std::vector<Package> compare2{Package(0),
//                                 Package(0), 
//                                 Package(1),
//                                 Package(2),
//                                 Package(3),
//                                 Package(4),
//                                 Package(5),
//                                 Package(6),
//                                 Package(7),
//                                 Package(8),
//                                 Package(9)}; 
//   client -> send_packages(10);
//   EXPECT_EQ(server -> get_log(), compare2); 
// 
// } 


