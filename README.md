# ofxCalibrationTool
Calibrate Virtual Raw to Virtual Real Spaces.

This tool allows you to calibrate a virtual space to a real space, so that virtual coordinates and orientations can be transformed into physical ones. Let me use an example to further describe its usefulness:

### Example of Use
Say, for example, you setup a Vive tracking system in front of a large flat-screen television, in hopes of turning this screen into a sort of touchscreen. Once everything is mapped correctly, you should be able to use the vive controller to "paint" on the tv screen. But how do you know how to map the Vive's coordinates to the screen's coordinates?

The Vive system outputs coordinates, but these exist in a virtual coordinate space that has no relation to the physical coordinate space of your room. In order to transform these virtual coordinates into physical coordinates, we can use this tool.

### Step 1: Define Target Plan
In order to map coordinates to physical space, we first need to define the coordinate system of the physical room. Decide where the origin and the direction of the X/Y/Z axes (assuming right handedness) will exist in this room and lay out 3 or more crosses on the floor. Measure and record the location of these "targets" relative to the origin and record them into a target.plan file (see specs in the header file for this addon and/or reference the provided example file in bin > data). In addition, record the indicies of those targets that define a "calibration square."

### Step 2: Program Your Application

Basic usage (using [ofxRemoteUI](https://github.com/armadillu/ofxRemoteUI) for GUI params) follows:

In a header file `ofApp.h`:

```c++
#include "ofxCalibrationTool.h"
#include "ofxRemoteUIServer.h"

class ofApp: public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void ofApp::keyPressed(int key);
    
    // The calibration tool object
    ofxCalibrationTool ctool;
    
    // For drawing
    ofEasyCam;
}
```

In a cpp file `ofApp.cpp`:

```c++
void ofApp::setup() {
    
    // Setup the addon's parameters
    RUI_SETUP();
    ctool.setupParams();
    RUI_LOAD_FROM_XML();
    
    // Load the target file if calibrating from scratch
    ctool.loadTargetPlan("targets.plan");
    
    // Load the calibration file if this has already been calibrated
    ctool.loadCalibrationFile("raw2real.cal");
}

void ofApp::update() {
    
    // Update the tool with the most recent raw coordinate info of the primary
    // tracker object
    glm::vec3 trackerPosition(0,0,0); // for example
    ctool.update(trackerPosition);
}

void ofApp::draw() {
    
    // Draw the status of this tool while active
    ctool.drawStatus();
    
    // Draw the state of the system (for debugging)
    cam.setUpAxis(ctool.getZAxis());
    cam.begin();
    ctool.drawDebug();
    cam.end();
}

void ofApp::keyPressed(int key) {
    
    // Start calibrating
    if (key == 'b') ctool.beginCalibrationProtocol();

	// Lock onto a target
    if (key == 'l') ctool.lockTarget();
}
```



### Step 3: Begin Calibration Protocol

Using this addon, begin the protocol. The addon will load the target file and ask you to move the designated tracker/controller to the locations defined by each of the targets. Press 'l' to lock onto the target once you have aligned the tracker with the target. Once complete, a raw2real.calibration file will be saved to the data folder, containing the best fit transformation matrix of virtual to real coordinate conversions.

Now, you can reload this file in and transform virtual to physical coordinates. However, mapping physical coordinates to screen coordinates poses another challenge, addressed by the addon [ofxSubstrateMapper](https://github.com/bensnell/ofxSubstrateMapper).
