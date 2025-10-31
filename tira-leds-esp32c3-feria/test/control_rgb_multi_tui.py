import serial
import time
import curses

# Valores iniciales sugeridos
colores = [
    [0, 255, 127],   # Turquesa
    [0, 0, 255],      # Azul
    [255, 127, 0]     # Naranja
]
labels = ['Turquesa', 'Azul', 'Naranja']


def main(stdscr):
    port = '/dev/tty.usbserial-110'
    baudrate = 115200
    ser = serial.Serial(port, baudrate, timeout=1)
    field = 0  # 0: Turquesa, 1: Azul, 2: Naranja
    comp = 0   # 0: R, 1: G, 2: B
    curses.curs_set(0)
    stdscr.nodelay(False)
    stdscr.timeout(100)
    save_msg = ''
    while True:
        stdscr.clear()
        stdscr.addstr(0, 0, 'Control LED RGB (Flechas: izq/der campo, arr/aba valor, Tab línea, +/- valor, s: guardar, q: salir)')
        for i, (label, color) in enumerate(zip(labels, colores)):
            sel = curses.A_REVERSE if i == field else 0
            stdscr.addstr(2 + i, 0, f'{label:9}: ', sel)
            for j, name in enumerate(['R', 'G', 'B']):
                comp_sel = curses.A_REVERSE if (i == field and j == comp) else 0
                stdscr.addstr(2 + i, 12 + j*8, f'{name}={color[j]:3}', comp_sel)
        stdscr.addstr(6, 0, save_msg)
        stdscr.refresh()
        # Enviar todos los colores al micro
        ser.write(f'{colores[0][0]},{colores[0][1]},{colores[0][2]};{colores[1][0]},{colores[1][1]},{colores[1][2]};{colores[2][0]},{colores[2][1]},{colores[2][2]}\n'.encode())
        key = stdscr.getch()
        if key == ord('q'):
            break
        elif key == curses.KEY_DOWN:
            colores[field][comp] = max(0, colores[field][comp] - 1)
        elif key == curses.KEY_UP:
            colores[field][comp] = min(255, colores[field][comp] + 1)
        elif key == curses.KEY_RIGHT:
            comp = (comp + 1) % 3
        elif key == curses.KEY_LEFT:
            comp = (comp - 1) % 3
        elif key == 9:  # Tab
            field = (field + 1) % 3
        elif key == 353:  # Shift+Tab (KEY_BTAB)
            field = (field - 1) % 3
        elif key == curses.KEY_NPAGE or key == ord('+'):
            colores[field][comp] = min(255, colores[field][comp] + 1)
        elif key == curses.KEY_PPAGE or key == ord('-'):
            colores[field][comp] = max(0, colores[field][comp] - 1)
        elif key == ord('s'):
            # Enviar comando de guardar
            ser.write(b'SAVE\n')
            save_msg = 'Valores enviados para guardar en EEPROM.'
            time.sleep(0.5)
        time.sleep(0.05)
    ser.close()

if __name__ == '__main__':
    curses.wrapper(main)
