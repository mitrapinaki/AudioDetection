CINC    = -Iinclude
SRC     = src
BIN     = bin
CC      = g++ -std=c++11 -g -Wall -O3 -Wno-unused-result $(CINC)

all: ${BIN}/fingerprint

${BIN}/fingerprint: $(SRC)/Fingerprint.cpp $(SRC)/Wav.cpp $(SRC)/main.cpp 
	mkdir -p ${BIN}
	$(CC) -o $(BIN)/fingerprint $(SRC)/Fingerprint.cpp $(SRC)/Wav.cpp $(SRC)/main.cpp -lfftw3

clean:
	rm -f *.BAK *.o core *~* *.a 
	rm -f $(BIN)/fingerprint
	
