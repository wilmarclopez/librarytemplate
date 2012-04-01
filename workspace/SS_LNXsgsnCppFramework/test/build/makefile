include ../../build/common.mk

SRC_DIR = ../../src
TEST_DIR = ..
INC_DIR = ../../include
GTEST_DIR = ../../tools/gtest

compile-obj: 
	$(CXX) -c $(TEST_DIR)/*.cpp -I$(INC_DIR) -I$(GTEST_DIR)/include -I$(TEST_DIR) $(CXXFLAGS_DEB)

test-cov: compile-obj
	$(CXX) $(SRC_DIR)/build/*.o *.o $(GTEST_DIR)/$(GTESTMAIN) -I$(INC_DIR) -I$(GTEST_DIR)/include -I$(TEST_DIR) -o $(TESTEXE) $(LDFLAGS_DEB)
	
clean:
	rm -rf *.o *.gcno *.gcda $(TESTEXE) *.xml