CXXFLAGS= -std=c++11 -pthread 
CPP_FILES := $(wildcard *.cpp)
H_FILES := $(wildcard *.h)

all: clean neuralDriver

neuralDriver:
	g++ -o neuralDriver $(CPP_FILES) $(H_FILES) $(CXXFLAGS) 2> errorLog

clean:
	@echo $(STOP)
	@echo "cleaning..."
	@rm -f neuralDriver `ls|grep \~`
	@echo "Done"

