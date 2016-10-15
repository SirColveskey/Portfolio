"""
Name: Benjamin Cooper - bjc12b
Date: 7-22-2016
Assignment: Python Assignment 5 - sine_plotter.py
Purpose: As an introdution to the Matplot and Qt(or another GUI)
this program creates a plotting window for the sine function
with editable variables. There is heavy referencing from plot_test_5.py:
http://www.cs.fsu.edu/~carnahan/cis4930/plot_test_5.py
"""
#Imports copied from class example
import sys, os, random
from PyQt5 import QtWidgets, QtGui, QtCore

import matplotlib
matplotlib.use('QT5Agg')
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas   
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar  
from matplotlib.figure import Figure
import numpy as np

"""the function: y(x) = A * sin(2piFx + phi)"""

class AppForm(QtWidgets.QMainWindow):
	def __init__(self, parent=None):
		self.freq = 1
		self.amp = 1
		self.phi = 0
		QtWidgets.QMainWindow.__init__(self, parent)
		self.setWindowTitle("Let's plot the sine function!")
		self.create_main_frame()
		self.init_draw()
	
	def init_draw(self):
		"""Initialization plot"""
		t = np.arange(0,5,.01)
		self.axes.plot(t,np.sin(2*np.pi*t))
		self.axes.axis([0,2,-1.5,1.5])
		self.canvas.draw()

	def on_draw(self):
		"""Draw creates a new plot based upon available data"""
		self.amp = float(self.ampbox.text())
		self.freq = float(self.freqbox.text())
		self.phi = float(self.phasebox.text())
		t = np.arange(0,5,.01)
		self.axes.plot(t,self.amp * np.sin(2*np.pi*self.freq*t+self.phi))
		self.canvas.draw()

	def clear(self):
		"""Clear function resets axis and removes all the plots"""
		self.axes.clear()
		self.axes.axis([0,2,-1.5,1.5])
		self.canvas.draw()

	def create_main_frame(self):
		"""Sets up all the Qt space"""
		#Initialization, mimicked from class example
		self.main_frame = QtWidgets.QWidget()
		self.fig = Figure()
		self.canvas = FigureCanvas(self.fig)
		self.canvas.setParent(self.main_frame)
		self.axes = self.fig.add_subplot(111)
		self.mpl_toolbar = NavigationToolbar(self.canvas, self.main_frame)
		#Layout Declarations
		vbox = QtWidgets.QVBoxLayout()
		hbox = QtWidgets.QHBoxLayout()
		hbox1 = QtWidgets.QHBoxLayout()
		hbox2 = QtWidgets.QHBoxLayout()
		hbox3 = QtWidgets.QHBoxLayout()
		#Addition of canvas and toolbar
		vbox.addWidget(self.canvas)
		vbox.addWidget(self.mpl_toolbar)
		#Button declaration and arrangement
		plot_button = QtWidgets.QPushButton("Plot Sine Wave",self)
		plot_button.clicked.connect(self.on_draw)
		clear_button = QtWidgets.QPushButton("Clear",self)
		clear_button.clicked.connect(self.clear)
		hbox.addWidget(plot_button)
		hbox.addWidget(clear_button)
		#Labels for text boxes
		label1 = QtWidgets.QLabel("Amplitude: ")
		label2 = QtWidgets.QLabel("Frequency: ")
		label3 = QtWidgets.QLabel("Phase: ")
		#Text boxes for variables
		self.ampbox = QtWidgets.QLineEdit("1")
		self.freqbox = QtWidgets.QLineEdit("1")
		self.phasebox = QtWidgets.QLineEdit("0")
		#hbox filling
		hbox1.addWidget(label1)
		hbox2.addWidget(label2)
		hbox3.addWidget(label3)
		hbox1.addWidget(self.ampbox)
		hbox2.addWidget(self.freqbox)
		hbox3.addWidget(self.phasebox)
		#hbox addition and arrangement
		vbox.addLayout(hbox1)
		vbox.addLayout(hbox2)
		vbox.addLayout(hbox3)
		vbox.addLayout(hbox)

		self.main_frame.setLayout(vbox)
		self.setCentralWidget(self.main_frame)

app = QtWidgets.QApplication(sys.argv)
form = AppForm()
form.show()
app.exec_()
