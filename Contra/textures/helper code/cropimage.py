from PIL import Image
director="D:/temp_img"
# Load the image
img = Image.open(r'D:\ContraCE108\Contra\textures\croppedMap1.png')

import os



# loop through each file in the directory
for filename in os.listdir(director):
    # check if the file is an image file
    if filename.endswith('.jpg') or filename.endswith('.png'):
        # construct the full path to the file
        filepath = os.path.join(director, filename)
        # delete the file
        os.remove(filepath)


# Define the size of the parts
part_size = 32

# Crop the top part separately if it doesn't have the same height as the parts
if img.height % part_size != 0:
    top_part_height = img.height % part_size
    top_part = img.crop((0, 0, img.width, top_part_height))
else:
    top_part_height = 0
    top_part = None

# Calculate the number of rows and columns needed to cover the entire image
num_cols = img.width // part_size
num_rows = (img.height - top_part_height) // part_size

# Crop the image into parts and store them in a list
parts = []
for row in range(1, num_rows+1):
    for col in range(num_cols):
        x0 = col * part_size
        y0 = top_part_height + (row - 1) * part_size
        x1 = x0 + part_size
        y1 = y0 + part_size
        part = img.crop((x0, y0, x1, y1))
        parts.append(part)

# Keep track of which parts have been replaced
replaced_parts = {}

# Compare each part with all the other parts to find similarities
for i, part1 in enumerate(parts):
    if i in replaced_parts:
        # Skip this part if it has already been replaced
        continue
    for j, part2 in enumerate(parts):
        if i == j:
            continue
        if j in replaced_parts:
            # Skip this part if it has already been replaced
            continue
        # You can use histogram comparison or other techniques here to check for similarities
        if part1.histogram() == part2.histogram():
            # Replace the similar part with the first occurrence of that part
            img.paste(parts[i], (j % num_cols * part_size, top_part_height + j // num_cols * part_size))
            replaced_parts[j]=i
print(len(replaced_parts.keys()))
_str=""
for i in range(num_cols*num_rows):
    if i not in replaced_parts.keys():
        _str=_str+f" {i}"
        parts[i].convert('RGB').save(f'{director}/{i}.png', 'PNG')
    else:
     _str=_str+f" {replaced_parts[i]}"
input_str=_str[1:]
# split the input string into a list of numbers
num_list = input_str.split()

# get the unique numbers in the list and sort them
unique_nums = sorted(set(num_list))

# create a dictionary mapping each unique number to its index
num_index_dict = {num: i for i, num in enumerate(unique_nums)}

# convert each number in the list to its corresponding index
index_list = [num_index_dict[num] for num in num_list]

# join the index list into a string
output_str = " ".join(str(index) for index in index_list)

print(len(output_str.split()))
with open(f"{director}/mapping.txt","w") as f:
    f.write(output_str)   
# If there's a top part, add it to the beginning of the parts list
if top_part is not None:
    parts.insert(0, top_part)
    #top_part.convert('RGB').save(f'D:/temp_img/-1.png', 'PNG')
## Save the modified image to a file
##img.save(r'D:\ContraCE108\Contra\textures\1GB.png')



from PIL import Image
import os


# set the output image dimensions
num_cols = 10  # number of images per row
img_size = 32  # assuming images are 32x32
num_rows = -(-len(os.listdir(director)) // num_cols)  # calculate the number of rows
width, height = num_cols * img_size, num_rows * img_size

# create a new blank image to merge the images into
result = Image.new('RGB', (width, height))

# get a list of image filenames in the directory and sort them by name
image_filenames = sorted([f for f in os.listdir(director) if f.endswith('.png') ])

# set initial x and y coordinates
x, y = 0, 0

# loop through the sorted image filenames
for i, filename in enumerate(image_filenames):
    # open the image file
    image = Image.open(os.path.join(director, filename))
    
    # resize the image to 32x32
    #image = image.resize((img_size, img_size))
    
    # paste the image onto the result image
    result.paste(image, (x, y))
    
    # increment the x coordinate
    x += img_size
    
    # if we have pasted num_cols images in a row, move to the next row
    if i % num_cols == num_cols - 1:
        x = 0
        y += img_size

# save the merged image
result.save(f'{director}/merged.png')
