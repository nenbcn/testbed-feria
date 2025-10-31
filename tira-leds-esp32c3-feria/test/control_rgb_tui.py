import serial
import time
import curses

def main(stdscr):
    port = '/dev/tty.usbserial-110'
    baudrate = 115200
    ser = serial.Serial(port, baudrate, timeout=1)
    r, g, b = 100, 220, 200
    field = 0  # 0: R, 1: G, 2: B
    fields = ['R', 'G', 'B']
    curses.curs_set(0)
    stdscr.nodelay(False)
    stdscr.timeout(100)
    while True:
        stdscr.clear()
        stdscr.addstr(0, 0, 'Control LED RGB (Flechas: mover/cambiar, q: salir)')
        for i, name in enumerate(fields):
            if i == field:
                stdscr.addstr(2, i*10, f'{name}={ [r,g,b][i] }', curses.A_REVERSE)
            else:
                stdscr.addstr(2, i*10, f'{name}={ [r,g,b][i] }')
        stdscr.refresh()
        ser.write(f'{r},{g},{b}\n'.encode())
        key = stdscr.getch()
        if key == ord('q'):
            break
        elif key == curses.KEY_RIGHT:
            field = (field + 1) % 3
        elif key == curses.KEY_LEFT:
            field = (field - 1) % 3
        elif key == curses.KEY_UP:
            if field == 0:
                r = min(255, r+1)
            elif field == 1:
                g = min(255, g+1)
            elif field == 2:
                b = min(255, b+1)
        elif key == curses.KEY_DOWN:
            if field == 0:
                r = max(0, r-1)
            elif field == 1:
                g = max(0, g-1)
            elif field == 2:
                b = max(0, b-1)
        time.sleep(0.05)
    ser.close()

if __name__ == '__main__':
    curses.wrapper(main)
