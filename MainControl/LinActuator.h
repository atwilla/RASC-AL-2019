#include "HBridge.h"

class LinActuator {
	private:
		int posPin;
		int negPin;
    int powerPin;
		HBridge *bridge;

	public:
		LinActuator(int posPin, int negPin, int powerPin) {
			this->posPin = posPin;
			this->negPin = negPin;
      this->powerPin = powerPin;
			bridge = new HBridge(posPin, negPin, powerPin);
      bridge->turnOn();
		}

		~LinActuator() {
			delete this->bridge;
		}

		void drive(int dir, int pulseDelay) {

			if (dir) {
				bridge->closePositive();
			} else {
				bridge->closeNegative();
			}

			//bridge->stop();
			//delayMicroseconds(pulseDelay);
		}

		void stop() {
			bridge->stop();
		}
};
