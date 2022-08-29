import dearpygui.dearpygui as gui

gui.create_context()
gui.create_viewport()

with gui.window(tag="Primary window") :
    with gui.tab_bar() :
        with gui.tab(label="tab1") :
            for i in range(100) :
                with gui.child_window(height=50) :
                    gui.add_text(str(i))
        with gui.tab(label="tab2") :
            for i in range(100) :
                with gui.child_window(height=50) :
                    gui.add_text(str(i))

gui.setup_dearpygui()
gui.show_viewport()
gui.set_primary_window("Primary window", True)
gui.start_dearpygui()
gui.destroy_context()
