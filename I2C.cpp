#include "I2C.hpp"
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

bool I2C::open(const char *deviceName, unsigned char address)
{
  // Close previously open device
  close();

  // Open new device
  handle = ::open(deviceName, O_RDWR);
  if(handle<0) return(false);

  // Configure slave address
  if(ioctl(handle, I2C_SLAVE, address)<0) { close();return(false); }

  // Done
  this->address = address;
  return(true);
}

void I2C::close()
{
  if(handle>=0) { ::close(handle);handle=-1; }
}

bool I2C::write(unsigned long long data, unsigned char length) const
{
  if((handle<0) || (length>sizeof(data))) return(false);
  return(::write(handle, (const void *)&data, length)==length);
}

unsigned long long I2C::read(unsigned char length) const
{
  unsigned long long data = 0;
  if((handle<0) || (length>sizeof(data))) return(0);
  return(::read(handle, (void *)&data, length)==length? data:0);
}

bool I2C::send(unsigned char *data, unsigned short length) const
{
  struct i2c_msg messages[] =
  {
    {
      .addr  = address,    // Device address
      .flags = 0,          // 0: WRITE
      .len = length,       // Data size
      .buf = data,         // Data
    },
  };

  struct i2c_rdwr_ioctl_data ioctl_data =
  {
    .msgs = messages,      // Messages
    .nmsgs = 1,            // Number of messages
  };

  return((handle>=0) && (ioctl(handle, I2C_RDWR, &ioctl_data)>=0));
}

bool I2C::recv(unsigned char *data, unsigned short length) const
{
  struct i2c_msg messages[] =
  {
    {
      .addr  = address,    // Device address
      .flags = 1,          // 1: READ
      .len = length,       // Data size
      .buf = data,         // Data
    },
  };

  struct i2c_rdwr_ioctl_data ioctl_data =
  {
    .msgs = messages,      // Messages
    .nmsgs = 1,            // Number of messages
  };

  return((handle>=0) && (ioctl(handle, I2C_RDWR, &ioctl_data)>=0));
}
