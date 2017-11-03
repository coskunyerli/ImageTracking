#Image Tracking

### Image Tracking with openCV and openGL written C++

##Required Libraries
- OpenCV (for tracking)
- OpenGL (for visualization)
- GLFW (to put scene into screen)
- Glad (to use OpenGL functions)


**Note: You can need to install another glad library according to your mechine**

## Compile

### Apple
- You can use `brew` to install dependent libraries
- OpenGL is in built-in library
- Glad is in the folder already

`brew install glfw`

`brew install opencv3`

###Linux

```
sudo apt-get update
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```

[You can find opencv installation](https://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html)

## Usage
`>./<Program-name> <tracking-type>`

####Example

`>./Visualization MIL`

`>./Visualization KFC`

`>./Visualization BOOSTING`


