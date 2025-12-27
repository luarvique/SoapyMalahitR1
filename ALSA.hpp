#ifndef ALSA_HPP
#define ALSA_HPP

#include <alsa/asoundlib.h>

class ALSA
{
  public:
    ALSA(): handle(0) {}
    ~ALSA() { close(); }

    bool open(const char *deviceName, unsigned int rate, unsigned int bufferSize, unsigned int periodSize);
      // Open given ALSA device.

    void close();
      // Close previously open ALSA device.

    bool isOpen() const { return(!!handle); }
      // Check if device is open.

    unsigned int read(void *data, unsigned int samples);
      // Read given number of samples from the open device.

    unsigned int getChunkSize() const { return(periodSize); }
      // Return current chunk size.

  private:
    snd_pcm_t *handle;
    unsigned int rate;
    snd_pcm_uframes_t periodSize;
    snd_pcm_uframes_t bufferSize;
};

#endif // ALSA_HPP
