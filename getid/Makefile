OBJS     = getid.o ../GPIO.o ../STM.o ../SPI.o
CXXFLAGS = -O3 -I..
LIBS     = -lgpiod

getid: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)

