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

## Exemple d'utilisation d'une IHM (pour le projet **Toueris**)

L'interface homme-machine des modules MODBUS esclaves du projet Toueris dispose de :

* 5 leds
* d'un pad de navigation à (4 directions + 1 bouton poussoir) et
* d'un afficheur LCD disposant d'un rétroéclairage (à base de ST7032)

En début de fichier [Toueris2Hmi.h](https://github.com/epsilonrt/WireHmi/blob/master/src/Toueris2Hmi.h), on voit la définition de constantes décrivant la solution matérielle :

    #define LED1  0
    #define LED2  1
    #define LED3  2
    #define LED4  3
    #define LED5  4

Nous avons 5 leds, la numérotation commence à 0.

    #define LED_RED     LED1
    #define LED_GREEN1  LED2
    #define LED_GREEN2  LED3
    #define LED_YELLOW1 LED4
    #define LED_YELLOW2 LED5

On définit des constantes plus explicites correspondant aux couleurs des leds: la led N°1 est rouge, la N°2 et 3 verte ...

Puis on trouve les constantes pour la fonction clavier :

    #define KUP       1
    #define KDOWN     2
    #define KLEFT     3
    #define KRIGHT    4
    #define KCENTER   5

Nous avons 5 touches correspondants aux 4 directions du bouton de navigation et au bouton du centre.

Pour utiliser cette IHM dans un programme, il faut déclarer une variable globale de type Toueris2Hmi:

    Toueris2Hmi hmi;

Si on utilise le pad de navigation, il faut lors de cette déclaration préciser le numéro de broche Arduino utilisé par l'IHM pour signaler que des touches se trouvent dans la buffer interne (il faudra donc les lire ...).

    const int hirqPin = 2;
    Toueris2Hmi hmi (hirqPin);

Ensuite, on peut accéder :  
* à la fonction led grâce à `hmi.led`,  
* à la fonction clavier grâce à `hmi.keyb`,  
* à la fonction rétroéclairage grâce à `hmi.backlight`.

### Utilisation des leds

Comme on peut le voir dans le sketch [LedDemo.ino](https://github.com/epsilonrt/WireHmi/blob/master/examples/Toueris2Hmi/LedDemo/LedDemo.ino):

    hmi.led.set (LED1);

permet d'allumer la LED1,

    hmi.led.clear (LED1);

permet d'éteindre la LED1,

    hmi.led.toggle (LED1);

permet de basculer l'état de la LED1,

    hmi.led.get (LED1);

permet de lire l'état de la LED1,

La fonction `hmi.led.writeAll()` permet de modifier toutes les leds en même temps. Par défaut, un appel à cette fonction sans paramètre allume toutes les leds.
Si on lui passe un paramètre, celui correspond à l'état des leds. Le bit 0 de ce paramètre permet de contrôler la LED1, le bit 1, la LED2...

### Utilisation du clavier

Comme on peut le voir dans le sketch [KeyboardDemo.ino](https://github.com/epsilonrt/WireHmi/blob/master/examples/Toueris2Hmi/KeyboardDemo/KeyboardDemo.ino):

    hmi.keyb.available()

permet de tester si des touches sont disponibles à la lecture,

    key = hmi.keyb.key();

permet de lire la prochaine touche,

    hmi.keyb.released()

permet de savoir si cette touche a été relâchée et,

    hmi.keyb.pressed()

si elle a été pressée.

### Utilisation du rétroéclairage

Comme on peut le voir dans le sketch [BacklightDemo.ino](https://github.com/epsilonrt/WireHmi/blob/master/examples/Toueris2Hmi/BacklightDemo/BacklightDemo.ino):

    hmi.backlight.write (bl);

permet de modifier la valeur du rétroéclairage (entre 0 et 255), comme cette valeur est stockée en EEPROM par l'IHM, il est possible de lire la valeur actuelle grâce à :

    bl = hmi.backlight.read();

## Exemple de création d'une IHM (pour le projet **Toueris**)

Cette partie concerne les développeurs qui veulent créer une nouvelle interface. On reprends le cas de l'IHM de Toueris.

En début de fichier [Toueris2Hmi.h](https://github.com/epsilonrt/WireHmi/blob/master/src/Toueris2Hmi.h), on voit:

    #define TOUERIS2_HMI_SLAVE_ADDR 0b0111111

qui correspond à l'adresse esclave de cette IHM. Cette adresse est utilisée par défaut par le constructeur de la classe, il ne sera donc pas nécessaire de la fournir lors de l'appel.

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

L'implémentation de la classe Toueris2Hmi est très concise (fichier [Toueris2Hmi.cpp](https://github.com/epsilonrt/WireHmi/blob/master/src/Toueris2Hmi.cpp)) :

    #define LED_REG       0
    #define BACKLIGHT_REG 1
    #define KEY_REG       2

Les constantes ci-dessus correspondent aux numéros de registres I2C attribués à chaque fonction.

    #define LED_NB  5

correspond aux nombres de leds.

    Toueris2Hmi::Toueris2Hmi (int hirqPin, byte slaveAddress) :
      WireSlave (slaveAddress),
      led (this, LED_REG, LED_NB),
      keyb (this, KEY_REG, hirqPin),
      backlight (this, BACKLIGHT_REG) {
    }

Le constructeur prend en paramètre le numéro de broche indiquant qu'une touche peut être lue et éventuellement l'adresse de notre IHM. 
Ce constructeur se cantonne à faire des appels aux constructeurs de la classe d'origine WireSlave et aux constructeurs des classes constituants l'interface avec les constantes définies précédement.

    bool Toueris2Hmi::begin() {
      
      return this->led.begin() && this->keyb.begin() && this->backlight.begin();
    }

La fonction `begin()` quant à elle réalise un appel aux fonctions `begin()` de chacune des classes de composition et retourne une valeur booléenne qui correspond au ET logique de toutes les valeurs retournées.

------
