swig -lua -c++ fingerprint.i
gcc -O2 -fPIC -march=native -mavx2 -shared -o fingerprint.so fingerprint_wrap.cxx fingerprint.c -lstdc++ -lm -lluajit
