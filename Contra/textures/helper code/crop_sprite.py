image_path=r'D:\ContraCE108\Contra\textures\192883.png'
import cv2
import numpy as np

# Load the PNG image
_img = cv2.imread(image_path, cv2.IMREAD_UNCHANGED)
img=np.copy(_img)
height,width,_=img.shape
# Get the alpha channel of the image
alpha_channel = img[:,:,3]
unfinished_parts=[]
finished_parts=[]

cur_part=None
def isTransparent(y,x):
    return alpha_channel[y,x]==0
for y in range(height):
    x=0
    cur_line=[]
    while x<width:
        if(isTransparent(y,x)):
                if(cur_part==None):
                    pass
                else:
                    cur_line.append(cur_part)
                    cur_part=None         

        else:
            if(cur_part==None):
                cur_part=[(y,x)]
            else:
                cur_part.append((y,x))   
        x=x+1
    #check if there is stiff part left
    if(cur_part!=None):
        cur_line.append(cur_part)
        cur_part=None
    #link if linked and add if not
    for i in range(len(cur_line)):
        _,x_cur=cur_line[i][0]
        flag=False
        for j in range(len(unfinished_parts)):
            _,x_start=unfinished_parts[j][-1][0]
            _,x_end=unfinished_parts[j][-1][-1]
            #print(x_start,x_end,_)
            if(x_start<=x_cur<=x_end):
                flag=True
                unfinished_parts[j].append(cur_line[i])
                break
        if(flag==False):
            unfinished_parts.append([cur_line[i]])
    if y==height-1:
        for i in unfinished_parts:
            finished_parts.append(i)
    remove_list=[]
    for i in range(len(unfinished_parts)):
        flag=False
        for j in range(len(unfinished_parts[i][-1])):
            y,x=unfinished_parts[i][-1][j]
            if(isTransparent(y+1,x)==False):
                flag=True
                break
        if(flag==False):
            remove_list.append(i)
    for i in remove_list:
        finished_parts.append(unfinished_parts[i])
    unfinished_parts=[unfinished_parts[i] for i in range(len(unfinished_parts)) if i not in remove_list]
cur_parr=101
y_start,x_start=finished_parts[cur_parr][0][0]
y_end,x_end=finished_parts[cur_parr][-1][0]
for i in finished_parts[cur_parr]:
    _,x_temp_start=i[0]
    _,x_temp_end=i[-1]
    if(x_temp_start<x_start):
        x_start=x_temp_start
    if(x_temp_end>x_end):
        x_end=x_temp_end
print(img[x_start:x_end+1,y_start:y_end+1].shape)
a=img[y_start:y_end+1,x_start:x_end+1]
cv2.imshow("abc",a)
cv2.waitKey()

        


