import serial
import dearpygui.dearpygui as dpg

ser = serial.Serial('COM4', 9600, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)

dpg.create_context()
dpg.create_viewport()
dpg.setup_dearpygui()

def scan_callback():
	dpg.set_value("progressBar", value=1)

with dpg.window(label="Control tornamesa"):
    dpg.add_button(tag="scanButton",label="Empezar escaneo", callback=scan_callback)
    dpg.add_progress_bar(tag="progressBar",label="progress")

dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()
