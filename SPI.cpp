#include "SPI.hpp"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

bool SPI::open(const char *deviceName, unsigned int speed)
{
  // Close previously open device
  close();

  // Open new device
  handle = ::open(deviceName, O_RDWR);
  if(handle<0) return(false);

  // Set speed
  this->speed = speed;

  // Done
  return(true);
}

void SPI::close()
{
  if(handle>=0) { ::close(handle);handle=-1; }
}

bool SPI::send(unsigned char *data, unsigned short length) const
{
  return(sendrecv(data, 0, length));
}

bool SPI::recv(unsigned char *data, unsigned short length) const
{
  return(sendrecv(0, data, length));
}

bool SPI::sendrecv(unsigned char *dataTx, unsigned char *dataRx, unsigned short length) const
{
  return(sendrecv(dataTx, length, dataRx, length));
}

bool SPI::sendrecv(unsigned char *dataTx, unsigned short lenTx, unsigned char *dataRx, unsigned short lenRx) const
{
  struct spi_ioc_transfer xfer[2];
  unsigned short length;

  // Determine common length
  lenTx  = dataTx? lenTx : 0;
  lenRx  = dataRx? lenRx : 0;
  length = !lenTx? lenRx : !lenRx? lenTx : lenTx<lenRx? lenTx : lenRx;
  if(!length) return(true);

  // Update remaining lengths
  lenTx = lenTx>length? lenTx - length : 0;
  lenRx = lenRx>length? lenRx - length : 0;

  memset(&xfer[0], 0, sizeof(xfer));
  xfer[0].speed_hz = speed;
  xfer[0].rx_buf   = (unsigned long)dataRx;
  xfer[0].tx_buf   = (unsigned long)dataTx;
  xfer[0].len      = length;
  xfer[1].speed_hz = speed;
  xfer[1].rx_buf   = (unsigned long)(lenTx? dataTx + length : 0);
  xfer[1].tx_buf   = (unsigned long)(lenRx? dataRx + length : 0);
  xfer[1].len      = lenTx>lenRx? lenTx : lenRx;

  length = (lenTx || lenRx)? 2 : 1;
  return(ioctl(handle, SPI_IOC_MESSAGE(length), &xfer) >= 0);
}
