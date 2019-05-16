#include "HBridge.h"

class LinActuator {
	private:
		int posPin;
		int negPin;
    int powerPin;
    bool enPWM;
		HBridge *bridge;

	public:
		LinActuator(int posPin, int negPin, int powerPin, bool enPWM) {
			this->posPin = posPin;
			this->negPin = negPin;
      this->powerPin = powerPin;
      this->enPWM = enPWM;
			bridge = new HBridge(posPin, negPin, powerPin);
      bridge->turnOn();
		}

		~LinActuator() {
			delete this->bridge;
		}

		void drive(int dir, int actSpeed) {

			if (dir) {
				bridge->closePositive();
        
        if (enPWM) {
          analogWrite(powerPin, actSpeed);  
        }
        
			} else {
				bridge->closeNegative();

        if (enPWM) {
          analogWrite(powerPin, actSpeed);
        }
			}

      // Test this before using above PWM code.
			bridge->stop();
			delayMicroseconds(actSpeed);
		}

		void stop() {
			bridge->stop();
		}
};
