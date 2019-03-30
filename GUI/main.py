import tkinter
import serial
from tkinter import *

class SensorPane(Frame):
	pass

class ControlPane(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.pack()

		self.stepperControl = StepperControl(self)
		self.stepperControl.pack()

class StepperControl(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.state = "normal"

		self.enableDisable = Button(self, text="Enable/Disbale", command=self.switchMode)
		self.cwSwitch = Button(self, text="Step CW", command=self.driveCW)
		self.ccwSwitch = Button(self, text="Step CCW", command=self.driveCCW)
		self.stopSwitch = Button(self, text="Stop Motors", command=self.stopMotors)
		
		self.enableDisable.pack(side="left")
		self.cwSwitch.pack(side="left")
		self.ccwSwitch.pack(side="left")
		self.stopSwitch.pack(side="left")

	def switchMode(self):


		if self.state == "normal":
			newState = "disabled"
			print(100)

		else:
			newState = "normal"
			print(101)

		self.cwSwitch['state'] = newState
		self.ccwSwitch['state'] = newState
		self.stopSwitch['state'] = newState
		self.state = newState

	def driveCW(self):
		print(102)

	def driveCCW(self):
		print(103)

	def stopMotors(self):
		print(104)

class DigitalCore(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		Label(self, text="Digital Core will go here", bg="white").pack()

class CurrentReadings(Frame):
	pass

class ForceReadings(Frame):
	pass

class ControlApp(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.pack(expand=1, fill=BOTH)
		
		self.controlPane = ControlPane(self)

		self.controlPane.pack()


root = ControlApp()
root.master.title('Excavation Control Program')

while True:
	root.update_idletasks()
	root.update()