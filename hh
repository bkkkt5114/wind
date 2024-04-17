import serial
import time

# 定义串口设备路径和波特率
serial_port = '/dev/ttyUSB0'
baud_rate = 9600

# 初始化串口连接
ser = serial.Serial(serial_port, baud_rate, timeout=1)

# 定义发送的命令帧
wind_speed_ref_frame = b'\x01\x02\x03\x04\x05\x06\x07\x08'

try:
    while True:
        print("-----------------------------------------------")
        print("Sending read request")
        
        # 等待一段时间以确保串口数据清空
        time.sleep(1)
        
        # 发送命令帧
        ser.write(wind_speed_ref_frame)
        ser.flush()
        
        # 读取8个字节的数据
        buf = ser.read(8)
        
        # 解析数据
        speed_dec_value = buf[4]
        
        print("")
        print("Wind Speed:", speed_dec_value / 10, "m/s")
        
        print("Buffer")
        print(hex(buf[0]))
        print(hex(buf[1]))
        print(hex(buf[2]))
        print(buf[3])
        print(buf[4])
        print(" !")
        print(buf[5])
        print(hex(buf[6]))
        print(hex(buf[7]))
        ser.flush()
        
        # 延迟一段时间再继续执行
        time.sleep(3)
except KeyboardInterrupt:
    ser.close()
