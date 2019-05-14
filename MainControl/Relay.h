#ifndef RELAY_H
#define RELAY_H

class Relay {
	private:
		int inputPin;

	public:
		Relay(int inputPin) {
			// Activate given pin. Keep relay at normally clsoed position.
			this->inputPin = inputPin;
			pinMode(inputPin, OUTPUT);
			digitalWrite(inputPin, HIGH);
		}

		void activate() {
			// Connect normally open port, break normally closed port.
			digitalWrite(inputPin, LOW);
		}

		void deactivate() {
			// Connect normally closed port, break normally open port.
			digitalWrite(inputPin, HIGH);
		}
};

#endif