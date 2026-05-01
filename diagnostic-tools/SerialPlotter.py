import serial
import time
from rich.console import Console
from rich import print
import pyqtgraph as pg


cs = Console(stderr=True)

app = pg.mkQApp()
win = pg.GraphicsLayoutWidget()
plot = win.addPlot()
curve = plot.plot()

plot.setYRange(0, 1300)      # fix y axis
plot.enableAutoRange(False)  # disable auto scaling


try:
    port = "/dev/ttyACM1"
    ser = serial.Serial(port=port, baudrate=115200, timeout=1)
except serial.serialutil.SerialException:
    cs.print(f"[bold red]Error:[/] Unable to connect to serial port {port}", style="white on red")
    exit(-1)

time.sleep(2)

data = []

def update():
    curve.setData(data[-200:])

timer = pg.QtCore.QTimer()
timer.timeout.connect(update)
timer.start(10)  # ms
win.show()


try:
    while True:
        if ser.in_waiting > 0:
            buf = ser.readline().decode('utf-8').rstrip()
            if len(buf) == 0 or buf[0] != ">": continue
            buf = [int(x, 16) for x in buf.split(",")[1:]]
            print(buf)
            data.append(buf[2])
            app.processEvents()
except KeyboardInterrupt:
    pass
except Exception as e:
    print(e)
finally:
    ser.close()