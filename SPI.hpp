#ifndef SPI_HPP
#define SPI_HPP

class SPI
{
  public:
    SPI(): handle(-1) {}
    ~SPI() { close(); }

    bool open(const char *deviceName, unsigned int speed = 10000000);
      // Open given SPI device.

    void close();
      // Close previously open SPI device.

    bool isOpen() const { return(handle>=0); }
      // Check if device is open.

    bool sendrecv(unsigned char *dataTx, unsigned short lenTx, unsigned char *dataRx, unsigned short lenRx) const;
      // Send and receive given number of bytes from the device.

    bool sendrecv(unsigned char *dataTx, unsigned char *dataRx, unsigned short length) const;
      // Send and receive given number of bytes from the device.

    bool send(unsigned char *data, unsigned short length) const;
      // Send given number of bytes to the device.

    bool recv(unsigned char *data, unsigned short length) const;
      // Receive given number of bytes from the device.

  private:
    unsigned int speed;
    int handle;
};

#endif // SPI_HPP
