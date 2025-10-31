import serial
import time

def main():
    # Ajusta el puerto según tu sistema (ejemplo: COM3 en Windows, /dev/ttyUSB0 o /dev/tty.SLAB_USBtoUART en Mac)
    port = '/dev/tty.usbserial-110'  # Cambiado para Mac
    baudrate = 115200
    ser = serial.Serial(port, baudrate, timeout=1)

    # Valores iniciales RGB
    r, g, b = 100, 220, 200

    print('Control de LED RGB. Usa +r/-r, +g/-g, +b/-b para ajustar. q para salir.')
    while True:
        print(f'Enviando: R={r} G={g} B={b}')
        ser.write(f'{r},{g},{b}\n'.encode())
        time.sleep(0.2)
        cmd = input('Comando: ')
        if cmd == 'q':
            break
        elif cmd == '+r':
            r = min(255, r+5)
        elif cmd == '-r':
            r = max(0, r-5)
        elif cmd == '+g':
            g = min(255, g+5)
        elif cmd == '-g':
            g = max(0, g-5)
        elif cmd == '+b':
            b = min(255, b+5)
        elif cmd == '-b':
            b = max(0, b-5)
    ser.close()

if __name__ == '__main__':
    main()
