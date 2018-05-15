# WireHmi Library

## Abstract

This library allows the client-side control of a human-machine interface (HMI) connected by an I2C bus. It is intended to be used in an Arduino environment (also compatible with the [PiDuino library](https://github.com/epsilonrt/piduino) on Pi boards such as Raspberry Pi or NanoPi).

The WireHmi library is designed in a modular way to create objects (C ++ classes) corresponding to any hardware solution.

The available modules are:

* `WireSlave` which corresponds to the modeling of any I2C slave. All HMI classes created by the user will be derived from this class.  
* `WireRegister` which corresponds to the modeling of a register that controls a functionality in a slave (module). All feature modules (`WireLeds`, `WireKeyboard` ...) supplied by the WireHmi library and all those that will be created by the user will be derived from this class.  
* `WireLeds` that can manage up to 8 LEDs (ON / OFF control).  
* `WireKeyboard` which allows to manage a set of push buttons (up to 127) with possibility to manage an interruption signal.  
* `WireBackLight` that manages the backlight intensity of an LCD (or any element that can vary between 0 and 255).

Associated with a library for the management of the LCD like [LCD_ST7032](https://github.com/epsilonrt/LCD_ST7032), one has a complete toolbox to create any HMI.

## Example of creation of the HMI of the **Toueris** project

Take the example of a human-machine interface like that of the MODBUS slave modules of the Toueris project which has:

* 3 leds  
* a navigation pad with (4 directions + 1 push button) and  
* an LCD display with a backlight (based on ST7032)  

The modeling of the class that allows the control of this HMI is:

		class Toueris2Hmi : public  WireSlave {
			public:
				Toueris2Hmi (int hirqPin = -1, byte slaveAddress = TOUERIS2_HMI_SLAVE_ADDR);
				bool begin();
				WireLeds led;
				WireKeyboard keyb;
				WireBackLight backlight;
		};

There are 3 modules: WireLeds (`led`), WireKeyboard (` keyb`) and WireBackLight (`backlight`) as well as 2 functions: the `Toueris2Hmi()` constructor and the `begin()` function.

At the beginning of the file [Toueris2Hmi.h](https://github.com/epsilonrt/WireHmi/blob/master/src/Toueris2Hmi.h), we see the definition of the constants corresponding to the material solution chosen:

		#define TOUERIS2_HMI_SLAVE_ADDR 0b0111111

which corresponds to the default slave address of this HMI.

		#define LED_REG 0
		#define LED_NB  3
		#define LED1  (1<<0)
		#define LED2  (1<<1)
		#define LED3  (1<<2)

which describes the number of the register controlling the LEDs (0) and the bits corresponding to each leds.

		#define BACKLIGHT_REG 1

which describes the number of the register controlling the backlight (1)

		#define BUT_REG 2
		#define BUT_NB  5
		#define BUT_RELEASE (1<<7)
		#define BUT_UP      1
		#define BUT_DOWN    2
		#define BUT_LEFT    3
		#define BUT_RIGHT   4
		#define BUT_CENTER  5

which describes the number of the register controlling the navigation push buttons (2) and the bits corresponding to each button and the one indicating whether it is a press or a release.

The implementation of the `Toueris2Hmi` class is very concise (file [Toueris2Hmi.cpp](https://github.com/epsilonrt/WireHmi/blob/master/src/Toueris2Hmi.cpp):

		Toueris2Hmi::Toueris2Hmi (int hirqPin, byte slaveAddress) :
			WireSlave (slaveAddress),
			led (this, LED_REG, LED_NB),
			keyb (this, BUT_REG, hirqPin),
			backlight (this, BACKLIGHT_REG) {
		}

The constructor that takes parameter interrupt pin number (indicating that a push button was pressed or released) and the address of our HMI. This constructor is confined to making calls to the constructors of the original `WireSlave` class and class constructors that compose the interface with the parameters corresponding to the HMI of the Toueris project.

		bool Toueris2Hmi::begin() {
			
			return this->led.begin() && this->keyb.begin() && this->backlight.begin();
		}

The `begin()` function performs a call to the `begin()` functions of each of the composition classes and returns a Boolean value that corresponds to the logical AND of all returned values.

The sketch [Toueris2Hmi.ino](https://github.com/epsilonrt/WireHmi/blob/master/examples/Toueris2Hmi/Toueris2Hmi.h) allows to see a complete example of use of the class `Toueris2Hmi` (Recipe test of the HMI of Toueris).

-------
