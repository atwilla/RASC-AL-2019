import tkinter
import serial
from tkinter.ttk import Frame, Button, Style

class ControlApp(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.grid()
		self.addWidgets()

	def addWidgets(self):
		self.exitButton = Button(self, text="Exit Program", 
			command=self.quit)
		self.exitButton.grid()

root = ControlApp()
root.master.title('Excavation Control Program')
root.master.geometry("1000x500")
root.mainloop()