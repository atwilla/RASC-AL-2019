#include "HBridge.h"

class LinActuator {
	private:
		int posPin;
		int negPin;
    int powerPin;
    bool enPWM;
		HBridge *bridge;

	public:
		LinActuator(int posPin, int negPin, int powerPin) {
			this->posPin = posPin;
			this->negPin = negPin;
      this->powerPin = powerPin;
			bridge = new HBridge(posPin, negPin, powerPin);

     pinMode(powerPin, OUTPUT);
     pinMode(powerPin, HIGH);
      //bridge->turnOn();
		}

    void turnOff() {
      // Cut off power to the actuator through a relay.
      digitalWrite(powerPin, HIGH);
    }

    void turnOn() {
      // Supply power to the actuator through a relay.
      digitalWrite(powerPin, LOW);
    }

		~LinActuator() {
			delete this->bridge;
		}

		void drive(int dir) {
      // Drive actuator forward or backward.

			if (dir) {
				bridge->closePositive();
			} else {
				bridge->closeNegative();
			}
		}

		void stop() {
			bridge->stop();
		}
};
