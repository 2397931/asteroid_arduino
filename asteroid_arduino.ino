
#include <Arduino.h>
#include <Bounce2.h>
#include <MicroOscSlip.h>
#include <Chrono.h>

Bounce2::Button but0;

MicroOscSlip<128> monOsc(&Serial);

Chrono chronoPot;

// Déclaration de la fonction
void traiterMessageOsc(MicroOscMessage &message);

void setup() {
    Serial.begin(115200);

    pinMode(3, OUTPUT);
}

void loop() {

    // ACQUISITION DES MESSAGES
    monOsc.onOscMessageReceived(traiterMessageOsc);

    // SI LE CHRONO DÉPASSE 20 MILLISECONDES
    if (chronoPot.hasPassed(20)) {

        // REPARTIR LE CHRONO
        chronoPot.restart();

        // LECTURE DE LA BROCHE ANALOGIQUE A3
        int valeur = analogRead(3);

        // ENVOYER LA VALEUR
        monOsc.sendInt("/photo", valeur);
    }
}

// FONCTION APPELÉE LORSQU'UN MESSAGE OSC EST REÇU
void traiterMessageOsc(MicroOscMessage &message) {

    // VÉRIFIER L'ADRESSE ET LE TYPE DU MESSAGE
    if (message.checkOscAddressAndTypeTags("/lumiere", "i")) {

        // RÉCUPÉRER L'ENTIER
        int valeur = message.nextAsInt();

        // ASSIGNER LA VALEUR À LA DEL
        digitalWrite(3, valeur);
    }
}
