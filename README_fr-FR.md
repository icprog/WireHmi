# WireHmi Library

## Abstract

Cette librairie permet le contrôle du côté client d'une interface homme-machine connecté par un bus I2C. Elle est prévue pour être utilisée dans un environnement Arduino (compatible aussi avec la librairie PiDuino sur cartes Pi comme Raspberry Pi ou NanoPi).

La librairie WireHmi est conçue de façon modulaire afin de pourvoir créer des objets (classes C++) correspondants à n'importe quelle solution matérielle.

Les modules disponibles sont :

* WireSlave qui correspond à la modélisation de n'importe quel esclave I2C. Toutes les classes Hmi crées par l'utilisateur seront dérivées de cette classe.  
* WireRegister qui correspond à à la modélisation de d'un registre qui contrôle une fonctionnalité dans un esclave (module). Tous les modules de fonctionnalités (WireLeds, WireKeyboard...)  fournit par la librairie WireHmi et tous ceux qui seront créés par l'utilisateur seront dérivées de cette classe.  
* WireLeds qui permet de gérer jusqu'à 8 leds (commande ON/OFF)  
* WireKeyboard qui permet de gérer un ensemble de boutons poussoirs (jusqu'à 127) avec possibilité de gérer un signal d'interruption.  
* WireBackLight qui permet de gérer l'intensité du rétroéclairage d'un LCD (ou de tout élément pouvant varier entre 0 et 255).

Associé à une librairie pour la gestion du LCD comme [LCD_ST7032](https://github.com/epsilonrt/LCD_ST7032), on dispose d'une boite à outils complète pour créer des interfaces homme-machine.

## Exemple de création de l'IHM du projet **Toueris**

Prenons l'exemple d'une interface homme-machine comme celle des modules MODBUS esclaves du projet Toueris qui dispose de :

* 3 leds
* d'un pad de navigation à (4 directions + 1 bouton poussoir) et
* d'un afficheur LCD disposant d'un rétroéclairage (à base de ST7032)

La modélisation de la classe qui permet le contrôle de cette IHM est :

		class Toueris2Hmi : public  WireSlave {
			public:
				Toueris2Hmi (int hirqPin = -1, byte slaveAddress = TOUERIS2_HMI_SLAVE_ADDR);
				bool begin();
				WireLeds led;
				WireKeyboard keyb;
				WireBackLight backlight;
		};

On y retrouve les 3 modules : WireLeds (`led`), WireKeyboard (`keyb`) et WireBackLight (`backlight`) ainsi que 2 fonctions: le constructeur `Toueris2Hmi()` et la fonction `begin()`.

En début de fichier [Toueris2Hmi.h](https://github.com/epsilonrt/WireHmi/blob/master/src/Toueris2Hmi.h), on voit la définition des constantes correspondants à la solution matérielle choisie :

		#define TOUERIS2_HMI_SLAVE_ADDR 0b0111111

qui correspond à l'adresse esclave par défaut de cette IHM.

		#define LED_REG 0
		#define LED_NB  3
		#define LED1  (1<<0)
		#define LED2  (1<<1)
		#define LED3  (1<<2)

qui décrit le numéro du registre contrôlant les leds (0) et les bits correspondants à chaque leds.

		#define BACKLIGHT_REG 1

qui décrit le numéro du registre contrôlant le rétroéclairage (1)

		#define BUT_REG 2
		#define BUT_NB  5
		#define BUT_RELEASE (1<<7)
		#define BUT_UP      1
		#define BUT_DOWN    2
		#define BUT_LEFT    3
		#define BUT_RIGHT   4
		#define BUT_CENTER  5

qui décrit le numéro du registre contrôlant les boutons poussoirs de navigation (2) et les bits correspondants à chaque boutons et celui indiquant s'il s'agit d'un appui ou d'un relachement.

L'implémentation de la classe Toueris2Hmi est très concise (fichier [Toueris2Hmi.cpp](https://github.com/epsilonrt/WireHmi/blob/master/src/Toueris2Hmi.cpp)) :

		Toueris2Hmi::Toueris2Hmi (int hirqPin, byte slaveAddress) :
			WireSlave (slaveAddress),
			led (this, LED_REG, LED_NB),
			keyb (this, BUT_REG, hirqPin),
			backlight (this, BACKLIGHT_REG) {
		}

Le constructeur qui prend en paramètre le numéro de broche d'interruption (indiquant qu'un bouton poussoir a été appuyé ou relâché) et l'adresse de notre IHM. Ce constructeur se cantonne à faire des appels aux constructeurs de la classe d'origine WireSlave et aux constructeurs des classes constituants l'interface avec les paramètres correspondant à l'IHM du projet Toueris.

		bool Toueris2Hmi::begin() {
			
			return this->led.begin() && this->keyb.begin() && this->backlight.begin();
		}

La fonction `begin()` quant à elle réalise un appel aux fonctions `begin()` de chacune des classes de composition et retourne une valeur booléenne qui correspond au ET logique de toutes les valeurs retournées.

Le sketch [Toueris2Hmi.ino](https://github.com/epsilonrt/WireHmi/blob/master/examples/Toueris2Hmi/Toueris2Hmi.ino) permet de voir un exemple complet d'utilisation de la classe Toueris2Hmi (Test de recette de l'IHM de Toueris).
