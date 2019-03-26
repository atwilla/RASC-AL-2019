import tkinter
import serial

from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label

class CurrentSensorReadings(GridLayout):
	#super(CurrentSensorReadings, self).__init__(**kwargs)

	def __init__(self):
		super(CurrentSensorReadings, self).__init__(**kwargs)
		self.cols = 1
		self.add_widget(Label(text="Current Usage"))
		self.currentLabel = Label(text="7.3 A")
		self.add_widget(self.currentLabel)

class WeightReadings(GridLayout):

	def __init__(self):
		super(WeightReadings, self).__init__(**kwargs)
		self.cols = 1
		self.add_widget(Label(text="Current Weight on Bit"))
		self.add_widget(Label(text="87 N"))

class DrillControllApp(App):

	def build(self):
		layout = GridLayout(cols=2)
		layout.add_widget(CurrentSensorReadings())
		layout.add_widget(WeightReadings())

		return layout

DrillControllApp().run()