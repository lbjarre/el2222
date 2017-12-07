
# mport the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera

import time
import cv2

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (320, 240)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(320, 240))
camera.awb_mode = "off"
camera.awb_gains = (1.10 , 2.40)

# allow the camera to warmup
time.sleep(0.1)
h_low = 0
s_low = 111 
v_low = 35
h_high = 18
s_high = 255
v_high = 149
# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
    image = frame.array


    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    circles = cv2.HoughCircles(gray_image, cv2.HOUGH_GRADIENT, 0.5, 10)

    # show the frame
    if circles != None:
        for i in range(0,len(circles[0])):
            x = circles[0][i][0]
            y = circles[0][i][1]
            r = circles[0][i][2]
            if int(hsv_image[x][y][0]) < h_high and int(hsv_image[x][y][0]) > int(h_low):
                if int(hsv_image[x][y][1]) < s_high and int(hsv_image[x][y][1]) > s_low:
                    if int(hsv_image[x][y][2]) < v_high and int(hsv_image[x][y][2]) > v_low:
                        cv2.circle(image,(x,y),r,(0,255,0))

    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF

    # clear the stream in preparation for the next frame
    rawCapture.truncate(0)
    
    # if the `q` key was pressed, break from the loop
    if key == ord("q"):
        break


