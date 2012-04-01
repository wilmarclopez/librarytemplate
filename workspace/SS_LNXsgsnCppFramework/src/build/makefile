include ../../build/common.mk

SRC_DIR = ..
INC_DIR = ../../include

release:
	$(CXX) -c $(SRC_DIR)/*.cpp -I$(INC_DIR) $(CXXFLAGS_REL)

debug:
	$(CXX) -c $(SRC_DIR)/*.cpp -I$(INC_DIR) $(CXXFLAGS_DEB)

# profile:
		
clean:
	rm -rf *.o *.gcno *.gcda *.xml *.gcov  #!(makefile)
