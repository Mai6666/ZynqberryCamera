import cv2
import numpy as np
import math

def Laplacian(in_array):
    conv_y = -in_array[0,0]  -2*in_array[0,1]   - in_array[0,2] \
           +  in_array[2,0]  +2*in_array[2,1]   + in_array[2,2]
    conv_x = -in_array[0,0]  + in_array[0,2] \
           -2*in_array[1,0]  +2*in_array[1,2] \
           -  in_array[2,0]  + in_array[2,2]
    #result = conv_y + conv_x
    result = math.sqrt( conv_y**2 + conv_x**2 )
    if result>255:
        result = 255
    elif result<0:
        result = 0
    return result

def GrayScale(in_arr):
    tmp_gs = in_arr.copy()
    for y in range(H):
        for x in range(W):
            tmp_gray = (in_arr[y,x,0] + in_arr[y,x,1] + in_arr[y,x,2])/3
            tmp_gs[pad+y, pad+x, 0] = tmp_gray
            tmp_gs[pad+y, pad+x, 1] = tmp_gray
            tmp_gs[pad+y, pad+x, 2] = tmp_gray
    return tmp_gs

def Comic(in_arr,scr):
    tmp_c = in_arr.copy()
    for y in range(H):
        for x in range(W):
            tmp_comic = (in_arr[y,x,0] + in_arr[y,x,1] + in_arr[y,x,2])
            if tmp_comic < 127:
                tmp_comic = 0
            elif tmp_comic < 192:
                tmp_comic = (scr[y,x,0] + scr[y,x,1] + scr[y,x,2])
            elif tmp_comic < 255:
                tmp_comic = 255
            tmp_c[pad+y, pad+x, 0] = tmp_comic
            tmp_c[pad+y, pad+x, 1] = tmp_comic
            tmp_c[pad+y, pad+x, 2] = tmp_comic
    return tmp_c


# Read image
screen = cv2.imread("screen.jpg")
img = cv2.imread("lena.png") # BGR order
H, W, C = img.shape
K_size = 3

## Zero padding
pad = K_size // 2
out = np.zeros((H + pad*2, W + pad*2, C), dtype=np.float)
out[pad:pad+H, pad:pad+W] = img.copy().astype(np.float)

scr = np.zeros((H + pad*2, W + pad*2, C), dtype=np.float)
scr[pad:pad+H, pad:pad+W] = screen.copy().astype(np.float)

gray = GrayScale(out)
comic = Comic(gray,scr)

for y in range(H):
    for x in range(W):
        tmp_lap = Laplacian(gray[y:y+K_size, x:x+K_size, 0])
        out[pad+y, pad+x, 0] =tmp_lap
        out[pad+y, pad+x, 1] =tmp_lap
        out[pad+y, pad+x, 2] =tmp_lap

out = out[pad:pad+H, pad:pad+W].astype(np.uint8)

# Save result

cv2.imwrite("comic.png", comic)
cv2.imwrite("out.png", out)
cv2.imshow("result", out)
cv2.waitKey(0)
cv2.destroyAllWindows()
