import tkinter
import serial
from tkinter import *

class SensorPane(Frame):
	"""
	This frame contains all data recorded from the arduino boards such 
	as current readings, weight on bit, and the digital core.
	"""

	def __init__(self, master=None, serialPort=None):
		Frame.__init__(self, master=None)

		self.arduino = serialPort

		self.digitalCore = DigitalCore(self)
		self.currentReadings = CurrentReadings(self)
		self.forceReadings = ForceReadings(self)

		self.digitalCore.pack()
		self.currentReadings.pack()
		self.forceReadings.pack()

class ControlPane(Frame):
	"""
	This frame contains all controls for the devices used in the device. 
	These consist of various steppers, actuators, pump control, a heating 
	element, and a few safety measures.
	"""

	def __init__(self, master=None, serialPort=None):
		Frame.__init__(self, master)

		"""if serialPort != None:
			self.arduino = serial.Serial(serialPort, 2000000)
		else:
			self.arduino = None"""

		self.arduino = serialPort

		self.safetyControls = SafetyControl(self)
		self.stepperControlTrans = StepperControl(self, range(10, 15), "Transverse Stepper Control")
		self.stepperControlVert = StepperControl(self, range(60, 65), "Vertical Stepper Control")
		self.actuatorControlLarge = ActuatorControl(self, range(40, 43), "Large Actuator Control")
		self.actuatorControlSmall = ActuatorControl(self, range(50, 53), "Small Acutator Control")
		self.heatingControl = HeatingControl(self, [20, 21])
		self.pumpControl = PumpControl(self, range(30, 33))

		self.safetyControls.pack()
		self.stepperControlTrans.pack()
		self.stepperControlVert.pack()
		self.actuatorControlLarge.pack()
		self.actuatorControlSmall.pack()
		self.heatingControl.pack()
		self.pumpControl.pack()


class SafetyControl(Frame):
	"""
	This frame contains various safety measures for the device.
	"""

	def __init__(self, master=None, codes=range(4), title="Safety Controls"):
		Frame.__init__(self, master)

		self.title = Label(self, text=title)
		self.codes = codes
		self.arduino = self.master.arduino
		self.shutDown = False
		self.heating = False

		# shutDown stops the Arduino from doing anything until it is lifted.
		self.shutDownSwitch = Button(self, text="Shutdown Controls", command=self.toggleShutdown)
		self.liftShutDown = Button(self, text="Lift Shutdown")
		# Heating mode locks all controls and activates heating element. This ensures that 
		# we do not exceed the specified current limit (9 A).
		self.heatingSwitch = Button(self, text="Enable Heating Mode", command=self.toggleHeating)
		self.stopHeating = Button(self, text="Disable Heating Mode")

		self.title.pack(side=TOP)
		self.shutDownSwitch.pack(side=LEFT)
		#self.liftShutDown.pack(side=LEFT)
		self.heatingSwitch.pack(side=LEFT)
		#self.stopHeating.pack(side=LEFT)

	def toggleShutdown(self):
		# Send appropriate shutdown code and change button text to match.

		if self.shutDown:
			print(self.codes[1])
			self.shutDownSwitch['text'] = "Shutdown Controls"
		else:
			print(self.codes[0])
			self.shutDownSwitch['text'] = "Lift Shutdown"

		self.shutDown = not self.shutDown

	def toggleHeating(self):
		# Send appropriate heating mode code and change button text to match.

		if self.heating:
			print(self.codes[3])
			self.heatingSwitch['text'] = "Enable Heating Mode"
		else:
			print(self.codes[2])
			self.heatingSwitch['text'] = "Disable Heating Mode"

		self.heating = not self.heating

class StepperControl(Frame):
	"""
	This frame contains controls for a stepper motor or for multiple 
	stepper motors run in parallel.
	"""

	def __init__(self, master=None, codes=[0, 1, 2, 3], title="Stepper Control"):
		Frame.__init__(self, master)

		self.state = "normal"
		self.codes = codes
		self.arduino = self.master.arduino

		self.title = Label(self, text=title)
		self.enableDisable = Button(self, text="Disbale", command=self.switchMode)
		self.cwSwitch = Button(self, text="Step CW", command=self.driveCW)
		self.stopSwitch = Button(self, text="Stop Motors", command=self.stopMotors)
		self.ccwSwitch = Button(self, text="Step CCW", command=self.driveCCW)
		
		self.title.pack(side="top")
		self.enableDisable.pack(side="left")
		self.cwSwitch.pack(side="left")
		self.stopSwitch.pack(side="left")
		self.ccwSwitch.pack(side="left")

	def switchMode(self):
		"""Enable and disable the stepper."""

		if self.state == "normal":
			newState = "disabled"
			print(self.codes[0])
			self.enableDisable['text'] = "Enable"
			self.arduino.write(chr(self.codes[0]).encode())

		else:
			newState = "normal"
			print(self.codes[1])
			self.enableDisable['text'] = "Disable"
			self.arduino.write(chr(self.codes[1]).encode())


		self.cwSwitch['state'] = newState
		self.ccwSwitch['state'] = newState
		self.stopSwitch['state'] = newState
		self.state = newState

	def driveCW(self):
		print(self.codes[2])
		self.arduino.write(chr(self.codes[2]).encode())

	def driveCCW(self):
		print(self.codes[3])
		self.arduino.write(chr(self.codes[3]).encode())

	def stopMotors(self):
		print(self.codes[4])
		self.arduino.write(chr(self.codes[4]).encode())

class HeatingControl(Frame):
	"""
	This frame contains controls for the heating element.
	"""

	def __init__(self, master=None, codes=[0, 1, 2, 3], title="Heating Control"):
		Frame.__init__(self, master)

		self.arduino = self.master.arduino
		self.codes = codes
		self.state = False

		self.title = Label(self, text=title)
		self.switch = Button(self, text="Activate Heating", command=self.heatingSwitch)

		self.title.pack()
		self.switch.pack()

	def heatingSwitch(self):

		# If heating on, disable, and allow activation.
		if self.state:
			print(self.codes[0])
			self.arduino.write(chr(codes[0]).encode())
			self.switch['text'] = "Activate Heating"
		else:
			print(self.codes[1])
			self.arduino.write(chr(codes[1]).encode())
			self.switch['text'] = "Disable Heating"

		self.state = not self.state
		
class ActuatorControl(Frame):

	def __init__(self, master=None, codes=range(3), title="Actuator Control"):
		Frame.__init__(self, master)

		self.arduino = self.master.arduino
		self.title = Label(self, text=title)
		self.codes = codes

		self.extendSwitch = Button(self, text="Extend", command=self.extend)
		self.stopSwitch = Button(self, text="Stop", command=self.stop)
		self.retractSwitch = Button(self, text="Retract", command=self.retract)

		self.title.pack()
		self.extendSwitch.pack(side=LEFT)
		self.stopSwitch.pack(side=LEFT)
		self.retractSwitch.pack(side=LEFT)
		
	def extend(self):
		print(self.codes[1])
		self.arduino.write(chr(codes[2]).encode())

	def stop(self):
		print(self.codes[0])
		self.arduino.write(chr(codes[0]).encode())

	def retract(self):
		print(self.codes[2])
		self.arduino.write(chr(codes[2]).encode())

class PumpControl(Frame):

	def __init__(self, master=None, codes=range(3), title="Pump Control"):
		Frame.__init__(self, master)

		self.arduino = self.master.arduino
		self.title = Label(self, text=title)
		self.codes = codes

		self.pumpForwSwitch = Button(self, text="Pump Forward", command=self.pumpForw)
		self.stopSwitch = Button(self, text="Stop Pump", command=self.stopPump)
		self.pumpBackSwitch = Button(self, text="Pump BackWard", command=self.pumpBack)

		self.title.pack()
		self.pumpForwSwitch.pack(side=LEFT)
		self.stopSwitch.pack(side=LEFT)
		self.pumpBackSwitch.pack(side=LEFT)

	def stopPump(self):
		print(self.codes[0])
		self.arduino.write(chr(codes[0]).encode())

	def pumpForw(self):
		print(self.codes[1])
		self.arduino.write(chr(codes[1]).encode())

	def pumpBack(self):
		print(self.codes[2])
		self.arduino.write(chr(codes[1]).encode())

class DigitalCore(Frame):

	def __init__(self, master=None):
		Frame.__init__(self, master)
		Label(self, text="Digital Core will go here").pack()

class CurrentReadings(Frame):

	def __init__(self, master=None):
		Frame.__init__(self, master)
		Label(self, text="Current Readings will go here").pack()

class ForceReadings(Frame):

	def __init__(self, master=None):
		Frame.__init__(self, master)
		Label(self, text="Weight on bit readings will go here").pack()

class ControlApp(Frame):

	def __init__(self, master=None, controlPort=None, monitorPort=None):
		Frame.__init__(self, master)
		self.pack(side=RIGHT)
		
		self.controlArduino = None
		self.monitorArduino = None

		if controlPort != None:
			self.controlArduino = serial.Serial(controlPort, 2000000)

		if monitorPort != None:
			self.monitorArduino = serial.Serial(monitorPort, 2000000)

		self.controlPane = ControlPane(self, serialPort=self.controlArduino)
		self.sensorPane = SensorPane(self, serialPort=self.monitorArduino)

		self.controlPane.pack()
		self.sensorPane.pack()

root = ControlApp()
root.master.title('Excavation Control Program')

root.mainloop()