# Summary

The serial control system will work by the connected computer sending a 
variety of codes, one at a time, to the arduino. Each code will correspond 
to a change in a variable from true to false or vice versa; there will be 
different codes for changing a specific variable from false to true and 
true to false to avoid mixups. The arduino board will check all involved 
variables and perform the corresponding action if they are found to be 
true. It is beneficial to use this "code-switch" method as opposed to a 
constant serial signal because the latter could cause delays in operations 
and require more resources from the computer.

The following devices will require codes:

1. Transverse stepper motors (x axis; treated as a unit)
2. Vertical stepper motor
3. Heating element
4. Pump
5. Large linear actuator
6. Small linear actuator

Additionally, there will be a code that signals a complete stop in 
the arduion sending signals for safety and emergency stop in the event of 
unexpected current consumption.

# Codes

A. Safety Codes

1. 000 - Complete shutdown of all signal output. Arduino only looks for 
the activation code after this code has been given.
2. 001 - The activation code. Used to "reboot" arduino after previous 
code has been used.
3. 002 - Heating mode. In this mode, the arduino only dedicates power 
to the heating element.
4. 003 - Deactivate heating mode.

B. Transverse stepper motors

1. 100 - Disable the steppers.
2. 101 - Enable the steppers.
3. 102 - Rotate the steppers clockwise.
4. 103 - Rotate the steppers counterclockwise.

C. Heating Element

1. 200 - Disable the heating element.
2. 201 - Enable the heating element.

D. Pump

1. 300 - Disable the pump.
2. 301 - Pump forwards.
3. 302 - Pump backwards.

E. Large Linear Actuator

1. 400 - Disable actuator.
2. 401 - Extend actuator.
3. 402 - Retract actuator.

F. Small Linear Actuator

1. 500 - Disable actuator.
2. 5X1 - Extend actuator. X = speed setting.
3. 5X2 - Retract actuator. X = speed setting.