import tkinter
import serial
from tkinter import *

class SensorPane(Frame):
	def __init__(self, master=None, serialPort=None):
		Frame.__init__(self, master=None)

		self.digitalCore = DigitalCore(self)
		self.currentReadings = CurrentReadings(self)

		self.digitalCore.pack()
		self.currentReadings.pack()

class ControlPane(Frame):
	def __init__(self, master=None, serialPort=None):
		Frame.__init__(self, master)

		if serialPort != None:
			self.arduino = serial.Serial(serialPort, 2000000)
		else:
			self.arduino = None

		self.safetyControls = SafetyControl(self)
		self.stepperControlTrans = StepperControl(self, range(10, 15), "Transverse Stepper Control")
		self.stepperControlVert = StepperControl(self, range(60, 65), "Vertical Stepper Control")

		self.safetyControls.pack()
		self.stepperControlTrans.pack()
		self.stepperControlVert.pack()


class SafetyControl(Frame):
	def __init__(self, master=None, title="Safety Controls"):
		Frame.__init__(self, master)
		self.title = Label(self, text=title)
		# shutDown stops the Arduino from doing anything until it is lifted.
		self.shutDown = Button(self, text="Shutdown Controls")
		self.liftShutDown = Button(self, text="Lift Shutdown")
		self.heatingMode = Button(self, text="Enable Heating Mode")
		self.stopHeating = Button(self, text="Disable Heating Mode")

		self.title.pack(side=TOP)
		self.shutDown.pack(side=LEFT)
		self.liftShutDown.pack(side=LEFT)
		self.heatingMode.pack(side=LEFT)
		self.stopHeating.pack(side=LEFT)

class StepperControl(Frame):
	def __init__(self, master=None, codes=[0, 1, 2, 3], title="Stepper Control"):
		Frame.__init__(self, master)
		self.state = "normal"
		self.codes = codes
		self.arduino = self.master.arduino

		self.title = Label(self, text=title)
		self.enableDisable = Button(self, text="Enable/Disbale", command=self.switchMode)
		self.cwSwitch = Button(self, text="Step CW", command=self.driveCW)
		self.ccwSwitch = Button(self, text="Step CCW", command=self.driveCCW)
		self.stopSwitch = Button(self, text="Stop Motors", command=self.stopMotors)
		
		self.title.pack(side="top")
		self.enableDisable.pack(side="left")
		self.cwSwitch.pack(side="left")
		self.ccwSwitch.pack(side="left")
		self.stopSwitch.pack(side="left")

	def switchMode(self):


		if self.state == "normal":
			newState = "disabled"
			print(self.codes[0])
			self.arduino.write(chr(self.codes[0]).encode())

		else:
			newState = "normal"
			print(self.codes[1])
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

class DigitalCore(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		Label(self, text="Digital Core will go here").pack()

class CurrentReadings(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		Label(self, text="Current Readings will go here").pack()

class ForceReadings(Frame):
	pass

class ControlApp(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.pack(side=RIGHT)
		
		self.controlPane = ControlPane(self, serialPort=None)
		self.sensorPane = SensorPane(self, serialPort=None)

		self.controlPane.pack()
		self.sensorPane.pack()

root = ControlApp()
root.master.title('Excavation Control Program')

root.mainloop()