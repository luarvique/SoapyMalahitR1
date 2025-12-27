#ifndef I2C_HPP
#define I2C_HPP

class I2C
{
  public:
    I2C(): handle(-1) {}
    ~I2C() { close(); }

    bool open(const char *deviceName, unsigned char address);
      // Open given I2C device.

    void close();
      // Close previously open I2C device.

    bool isOpen() const { return(handle>=0); }
      // Check if device is open.

    bool write(unsigned long long data, unsigned char length) const;
      // Write given number of bytes to the open device.

    unsigned long long read(unsigned char length) const;
      // Read given number of bytes from the open device.

    bool send(unsigned char *data, unsigned short length) const;
    bool recv(unsigned char *data, unsigned short length) const;
      // Perform ioctl(I2C_RDWR) on the open device.

  protected:
    unsigned char address;

  private:
    int handle;
};

#endif // I2C_HPP
