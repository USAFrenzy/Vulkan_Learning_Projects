# Vulkan_Learning_Projects #

[Change Log](https://github.com/USAFrenzy/Vulkan_Learning_Projects/wiki/Change-Log)

This Repository Will Be Updated As I Add More Projects To It.

The Main Goal Of This Repo Is Primarily For Me To Mess Around With Vulkan In An Attempt To Learn \
About Graphics APIs That Offer Full Control. In Essence, I Would Love To Incorporate Vulkan Into \
The Redemption Engine Project As Well As Take The Knowledge Learned Here And Apply It To Learning \
DirectX. This Is Pretty Much In Hopes Of Using The Combined Knowledge For Graphics Layers In Other \
Applications And The DirectX Specifically As A Starting Point For Applying That To The Dynamic \
Weather Effects Mod I'm Very Slowly Working On. 

***________________________________________________________________________________________________________________*** \
If You Are Someone That Stumbled Upon This Repo And Would Like To Play Around With \
The Code Base Or See What Has So Far Been Created/Implemented, Then Read On Below \
***________________________________________________________________________________________________________________*** 

### To Get Started ###
- You will need to have already installed CMake and added it to your environment path ([CMake Download Page](https://cmake.org/download))
- Once CMake has been downloaded, create a folder to clone this repo into and open up a command prompt in that folder
    - run ```git clone https://github.com/USAFrenzy/Vulkan_Learning_Projects.git```
    - run ```git submodule update --init --recursive``` to fully install dependancy libraries
    - run ```git submodule update --recursive --remote``` to get the most recent source of those libraries
- Now simply run ```cmake -B build -S .``` To Generate The Project Files
    - The Generated Files Will Be Under The Build Folder
    - Use The Build Generater That CMake Was Configured For To Build The Project
    - i.e. If You Have Visual Studio Installed, Then Under The Build Folder Will
      Be A ```Vulkan Learning Projects.sln``` file. Simply Open This In VS and 
      Configure It - Then Hit Build 



## Current Progress ##
Validation Layer Support 
![](https://github.com/USAFrenzy/Vulkan_Learning_Projects/blob/main/Resources/Vulkan_Project_Progress_02.gif)

Basic Window Creation And Cursor/Window Movement Logging
![](https://github.com/USAFrenzy/Vulkan_Learning_Projects/blob/main/Resources/Vulkan_Project_Progress_01.gif)
