#ifndef GPIO_HPP
#define GPIO_HPP

#include <gpiod.h>

class GPIO
{
  public:
    GPIO(const char *chipName = "gpiochip0")
    { initialize(chipName); }

    ~GPIO()
    { uninitialize(); }

    bool reset() const;
      // Hard-reset STM chip.

    bool waitForSTM() const;
      // Wait until STM becomes ready.

  private:
    struct gpiod_chip *chip = 0;

    gpiod_line *rst_line;

    bool initialize(const char *chipName);
    void uninitialize();

    gpiod_line *busy_line;
};

#endif // GPIO_HPP
