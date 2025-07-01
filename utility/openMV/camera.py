import sensor, time, math, pyb

ball_presence = pyb.ADC(pyb.Pin('P6'))

uart = pyb.UART(3,19200)

thresholds = [(55, 100, -128, 35, 38, 127),    # YELLOW
              (48, 62, -11, 8, -45, -10)] # BLUE

# cx = 160-blob.cx()
# cy = 120-blob.cy()

camcx = 160 # 178
camcy = 120 # 130

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

pyb.LED(1).on()
pyb.LED(2).on()
pyb.LED(3).on()

while(True):
    clock.tick()

    yellowFound = False
    blueFound = False

    img = sensor.snapshot()
    img.draw_cross(camcx, camcy)

    blobYellow = [(0, 0, 0)]
    blobBlue = [(0, 0, 0)]

    for blob in img.find_blobs(thresholds, pixels_threshold=200, area_threshold=200, merge=True):
        img.draw_cross(blob.cx(),blob.cy())
        img.draw_cross(camcx,camcy);
        img.draw_line(camcx,camcy,blob.cx(),blob.cy())
        if (blob.code() == 1):
            img.draw_rectangle(blob.rect(), (255, 255, 0))
            blobYellow += [(blob.area(), blob.cx(), blob.cy())]
            yellowFound = True

        if (blob.code() == 2):
            img.draw_rectangle(blob.rect(), (0, 0, 255))
            blobBlue += [(blob.area(), blob.cx(), blob.cy())]
            blueFound = True


        blobYellow.sort(reverse = True)
        blobBlue.sort(reverse = True)

        # YELLOW GOAL
        if (yellowFound):
            area = blobYellow[0][0]
            cx = camcx-blobYellow[0][1]
            cy = camcy-blobYellow[0][2]
            ang = int((math.atan2(cx, cy) * 180 / math.pi) - 90)
            if (ang < 0):
                ang += 360
            data = "Y" + str(ang) + "-" + str(area) + "y"
        else:
            data = "Y999-999y"

    uart.write(data)
    print(data)

    # BLUE GOAL
    if (blueFound):
        area = blobBlue[0][0]
        cx = 160-blobBlue[0][1]
        cy = 120-blobBlue[0][2]
        ang = int((math.atan2(cx, cy) * 180 / math.pi) - 90)
        if (ang < 0):
            ang += 360
        data = "B" + str(ang) + "-" + str(area) + "b"
    else:
        data = "B999-999b"

    uart.write(data)
    print(data)

    # BALL
    data = "P" + str(ball_presence.read()) + "p"
    uart.write(data)
    #print(data)
