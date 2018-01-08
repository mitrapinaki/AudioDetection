Audio Fingerprinting and Recognition in C++
===============================================

Features:
-----
- audio Fingerprinting and Recognition

Dependencies:
-----

- fftw3:
    Under Debian/Ubuntu, please run `apt-get install libfftw3-dev`.

Compile & Run:
-----

- `make` to produce one excutive file in ./bin/ 
- in ./bin/ the Samplestream.wav is present, do not remove the file.
- the audio to be verified should be .wav format with sample rate 8000hz
- to run => `cd bin`, `./fingerprint` and it'll prompt to enter file to be matched.
- The output will show the deviation and the result

Unit Test Case:
------

- Under 'Test' folder unit test cases are present
- run 'make' to build the test case
- run 'test' to execute


