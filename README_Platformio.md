# Setting up Platformio

# Elecrow display boards (all variants)

Download the Elecrow board description here:

https://www.elecrow.com/download/product/CrowPanel/ESP32-HMI/5.0-DIS07050H/PIO-Tutorial/esp32-s3-devkitc-1-myboard.zip

Unzip the file and place the json file here:

Windows:
C:\Users\<>\.platformio\platforms\espressif32\boards

Linux:
/home/<>/.platformio\platforms\espressif32\boards

Where <> is your username.

More details are available on the Elecrow website here:

https://www.elecrow.com/wiki/CrowPanel_ESP32_7.0-inch_with_PlatformIO.html#get-started-with-platformio



# Compiling:

1. Clone this respository and the submodule(s)

    `git clone --recurse-submodules git@github.com:Rosscoetrain/CheapYellowController.git`

2. Open the folder in platformio

    For the board you are using
3. Upload from the PROJECT TASKS
4. Build Filesystem Image from the PROJECT TASKS
5. Upload Filesystem Image from the PROJECT TASKS

More details:

Platformio will collect the necessary libraries while compiling before upload.  This will only occur the first time you compile the program.


Display boards currently defined in platformio.ini

Elecrow_DIS06043H       Elecrow 4.3" 480x272 model DIS06043H resistive touch
Elecrow_DIS08070H       Elecrow 7.0" 800x480 model DIS08070H capacitive touch
Sunton 4827S043C        Sunton 4.3" 480x272 capacitive touch

