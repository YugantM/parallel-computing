UNAME_S := $(shell uname -s)

CXXFLAGS=-I./ -pthread -g -std=c++11
LDFLAGS=-lpthread

ifeq ($(UNAME_S),Linux)
	CXXFLAGS += -fopenmp
	LDFLAGS += -lgomp
endif
ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += -Xpreprocessor -fopenmp
	LDFLAGS += -lomp
endif

src_common = utils.cpp
src = $(src_common) \
		main.cpp

obj = $(src:.cpp=.o)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

all: nbody

nbody: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)


clean:
	rm -f $(obj) nbody

.PHONY: all clean
