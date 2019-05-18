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
				//bridge->closePositive();
        digitalWrite(negPin, HIGH);

        // Since this state needs relays to be off, pulse must be inverted.
        if (enPWM) {
          analogWrite(posPin, 255);  
        }
        
			} else {
				//bridge->closeNegative();
        digitalWrite(negPin, LOW);

        if (enPWM) {
          analogWrite(posPin, 0);
        }
			}

      // Test this before using above PWM code.
      //delayMicroseconds(1000);
			//bridge->stop();
      //delayMicroseconds(actSpeed);
		}

		void stop() {
			bridge->stop();
		}
};
