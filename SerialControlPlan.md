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

1. 001 - Complete shutdown of all signal output. Arduino only looks for 
the activation code after this code has been given. This only affects the 
arduino used to drive the devices.
2. 002 - The activation code. Used to "reboot" arduino after previous 
code has been used.
3. 003 - Heating mode. In this mode, the arduino only dedicates power 
to the heating element.
4. 004 - Deactivate heating mode.

B. Transverse stepper motors

1. 010 - Disable the steppers.
2. 011 - Enable the steppers.
3. 012 - Rotate the steppers clockwise.
4. 013 - Rotate the steppers counterclockwise.
5. 014 - Stop rotation.

C. Heating Element

1. 020 - Disable the heating element.
2. 021 - Enable the heating element.

D. Pump

1. 030 - Stop pumping.
2. 031 - Pump forwards.
3. 032 - Pump backwards.

E. Large Linear Actuator

1. 040 - Stop movement.
2. 041 - Extend actuator.
3. 042 - Retract actuator.

F. Small Linear Actuator

1. 050 - Stop movement.
2. 051 - Extend actuator.
3. 052 - Retract acutator.
