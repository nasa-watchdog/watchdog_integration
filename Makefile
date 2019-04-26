CC = g++

# compiler flags:

CFLAGS  = -lnfc -std=c++11 -pthread

# the build target executable:
TARGET = actionrecTEST

all: $(TARGET)

$(TARGET): 
	$(CC) -o $(TARGET) actionrec.cc imu.o $(CFLAGS)

clean:
	$(RM) $(TARGET)
