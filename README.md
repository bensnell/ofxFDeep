# ofxFDeep

This addon links [frugally-deep](https://github.com/Dobiasd/frugally-deep) with OpenFrameworks, allowing inference of Keras machine learning models.

This has been tested on Windows 10 with VS 2019 and OF 0.11.0

This utilizes fdeep version 0.12.0

## Usage

Clone this repo recursively to install all libraries. Then, utilize it like any other addon.

## Troubleshooting

##### Why is the folder containing external libraries called `lib` instead of `libs`? 

There is an error in the project generator that imports all c files in the libs directory, even if they have been marked in the addon_config.mk file for exclusion. So, the folder was renamed lib so it could only be found by passing its explicit path via the addon config file.

##### Conan Installation

Another method of installing FDeep is using conan. See frugally-deep's install instructions for this approach. The instructions are repeated here for reference: 

1. Install conan on your system. Open Git-Bash and run `pip install conan`. You should be using Python 3.
2. Install frugally-deep and its dependencies using Conan, as outlined [here](https://github.com/Dobiasd/frugally-deep/blob/master/INSTALL.md#installation-using-conan-cc-package-manager). Use a generator script for `visual-studio`. This will produce a property sheets file.
3. In the Visual Studio Propery Sheets window, add the generated property sheet to all configs you will be using.
4. Follow the usage instructions for fdeep outlined in its repo. 

##### JSON Errors

Openframeworks also depends on a json library, which can cause errors if the two don't share the same header macro. If this becomes a problem, change the version of json to match OF's (or vice versa), or change the macro to match the other one.