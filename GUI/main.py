import tkinter
import serial
from tkinter import *

class SensorPane(Frame):
	pass

class ControlPane(Frame):
	def __init__(self, master=None, serialPort="/dev/ttyACM0"):
		Frame.__init__(self, master)

		self.arduino = serial.Serial(serialPort, 2000000)
		self.stepperControlTrans = StepperControl(self, range(10, 15), "Transverse Stepper Control")
		self.stepperControlVert = StepperControl(self, range(60, 65), "Vertical Stepper Control")

		self.stepperControlTrans.pack()
		self.stepperControlVert.pack()

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

root.mainloop()