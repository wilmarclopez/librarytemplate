include common.mk

############################## DIRS ##############################
TOOLS_DIR = ../tools
SRC_DIR = ../src
TARGET_DIR = ../target
TEST_DIR = ../test
COV_DIR = ../cov

############################## TOOLS ##############################

compile-gtest:
	cd $(TOOLS_DIR)/gtest ; make

clean-gtest:
	cd $(TOOLS_DIR)/gtest ; make clean

compile-tools: compile-gtest
clean-tools: clean-gtest

############################## SRC ###############################


compile-src-rel:
	cd $(SRC_DIR)/build ; make release

compile-src-deb:
	cd $(SRC_DIR)/build ; make debug

compile-src-prof:
	cd $(SRC_DIR)/build ; make profile
		
clean-src:
	cd $(SRC_DIR)/build ; make clean	


############################## TARGET ###############################

build-target: compile-src-rel
	ar -rv $(TARGET_DIR)/$(TARGET) $(SRC_DIR)/build/*.o
	
clean-target:
	rm -rf $(TARGET_DIR)/*.a
	
############################## TEST ###############################

build-test-cov: compile-tools
	cd $(TEST_DIR)/build ; make test-cov

clean-test:
	cd $(TEST_DIR)/build ; make clean
	
run-test-cov: build-test-cov
	chmod +x run_test_cov.sh ; ./run_test_cov.sh
	
clean-cov:
	rm -rf $(COV_DIR) ; mkdir $(COV_DIR) 

###################################################################

release: build-target
debug: compile-src-deb compile-tools build-test-cov run-test-cov
# profile: 

all: debug release
clean: clean-src clean-target clean-test clean-target clean-cov #clean-tools
