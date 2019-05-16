#ifndef HBRIDGE_H
#define HBRIDGE_H
#include "Relay.h"

class HBridge {
	private:
		Relay *posRelay;
		Relay *negRelay;
    int powerPin;

	public:
		HBridge(int posRelayPin, int negRelayPin, int powerPin) {
			// Assumes posRelay is placed at positive terminal of motor 
			// and negRelay at negative terminal.
			this->posRelay = new Relay(posRelayPin);
			this->negRelay = new Relay(negRelayPin);
      this->powerPin = powerPin;
      this->turnOff();
			this->stop();
		}

		~HBridge() {
			delete posRelay;
			delete negRelay;
		}

		void closePositive() {
			// Cause positive voltage polarity
      turnOn();
			posRelay->deactivate();
			negRelay->deactivate();
		}

		void closeNegative() {
			// Cause negative voltage polarity
      turnOn();
			posRelay->activate();
			negRelay->activate();
		}

		void stop() {
			// Mismatching states results in an open circuit.
     // Cut off power to the relays.
			turnOff();
		}

    void turnOn() {
      digitalWrite(powerPin, HIGH);
    }

    void turnOff() {
      digitalWrite(powerPin, LOW);
    }
};

#endif
