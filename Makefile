INC_DIR:= .
EXE:= main
SRC_DIR:= .
SRCS:= $(wildcard $(SRC_DIR)/*.cc)
#LIBS:= -lboost_regex -lpthread
CXXFLAGS:= -std=c++11 
$(EXE):$(SRCS)
	clang++ -Wall -g -o $@ $^  $(LIBS) $(addprefix -I, $(INC_DIR)) $(CXXFLAGS)
clean:
	rm main
