import serial
import minimalmodbus
import time

def init(serial_port):
    # 初始化串口
    return serial.Serial(serial_port, 9600, timeout=1)

def modify_address(serial_port, address):
    instrument = minimalmodbus.Instrument(serial_port, 1)  # 使用預設地址1初始化儀器對象
    instrument.serial.baudrate = 9600
    instrument.serial.timeout = 1
    
    # 將新的地址寫入到風向儀中
    instrument.write_register(0x00, address, functioncode=6)

def read_wind_speed(serial_port, address):
    instrument = minimalmodbus.Instrument(serial_port, address)
    instrument.serial.baudrate = 9600
    instrument.serial.timeout = 1
    
    # 讀取風速寄存器的值，假設風速寄存器地址是0x01
    wind_speed = instrument.read_register(0x01, functioncode=3)
    return wind_speed

if __name__ == "__main__":
    serial_port = '/dev/ttyUSB0'  # 修改為樹莓派上的串口
    address = 1  # 修改為風向儀的地址

    # 初始化串口
    ser = init(serial_port)

    # 修改風向儀地址
    modify_address(ser, address)

    try:
        while True:
            # 讀取風速
            wind_speed = read_wind_speed(ser, address)

            print("WindSpeed: {} m/s".format(wind_speed))
            time.sleep(0.5)  # 等待0.5秒再次讀取風速

    except KeyboardInterrupt:
        ser.close()  # 當用戶按下Ctrl+C時，關閉串口連接
