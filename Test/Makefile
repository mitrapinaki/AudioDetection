CINC    = -I ../include
SRC     = ../src
CC      = g++ -std=c++11 -g -Wall -O3 -Wno-unused-result $(CINC)

all: test

test: $(SRC)/Fingerprint.cpp $(SRC)/Wav.cpp TestMain.cpp 
	$(CC) -o test $(SRC)/Fingerprint.cpp $(SRC)/Wav.cpp TestMain.cpp -lfftw3

clean:
	rm -f *.BAK *.o core *~* *.a 
	rm -f test
	
