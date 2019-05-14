#ifndef PUMP_H
#define PUMP_H
#include "Relay.h"

class Pump {
	private:
		Relay *posRelay;
		Relay *negRelay;

	public:
		Pump(int posRelayPin, int negRelayPin) {
			// Assumes posRelay is placed at positive terminal of motor 
			// and negRelay at negative terminal.
			this->posRelay = new Relay(posRelayPin);
			this->negRelay = new Relay(negRelayPin);
		}

		~Pump() {
			delete posRelay;
			delete negRelay;
		}

		void pumpForwards() {
			// Forward pumping is default state;
			posRelay->deactivate();
			negRelay->deactivate();
		}

		void pumpBackwards() {
			// Reverse polarity of voltage across motor.
			posRelay->activate();
			negRelay->activate();
		}

		void stop() {
			// Mismatching states results in an open circuit.
			posRelay->deactivate();
			negRelay->activate();
		}
};

#endif