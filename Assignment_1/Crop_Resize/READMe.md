#####################################################

Requirements:
1. Visual Studio 15;
2. OpenCV 3.2.0
3. cmake_minimum_required(VERSION 2.8.12)

######################################################

Follow the Steps Given Below to Run the Code (Windows)
1. Download the Whole Folder and Change the path to the Folder in CMD.
2. run the command in CMD (Windows): mkdir build
3. run the command in CMD (Windows): cmake -G "Visual Studio 14 2015 Win64" ..
4. run the command in CMD (Windows): cmake --build . --config Release

#######################################################

After running the above command you can locate your .exe file with the name Crop_Resize in the Release Folder

5. run the command in CMD (Windows): Crop_Resize.exe "Path to the First Image" "Path to the Second Image"
