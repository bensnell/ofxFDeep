#pragma once

#include "ofMain.h"
#include "ofxRemoteUIServer.h"
#include "ofxOpenCv.h"

// The Target Plan for this calibration protcol is a json document with extension .plan
// and the following elements:
// (1) key "calibration_targets" to a list of at least 3 positions with physical
// space (x, y, z) coordinates in meters. Usually, these targets are on the floor.
// (2) key "calibration_square" to a list of three unique indices {1,2,3} of the preceding 
// targets. Using the right hand rule, vector{[1]-[0]}.cross(vector{[2]-[0]}).norm() is the 
// z direction. This entry is needed because otherwise, there is not enough information to
// know which way is up

// The Calibration File contains the information to transform virtual raw to virtual real
// coordinates. The file is in json format with extension .calibration and contains the elements:
// (1) key "calibration_transformation_matrix" to a 4x4 transformation matrix

// The Substrate Plan contains geometric information defining the projection surface in a json format
// with extension .plan :
// (1) key "substrate_outline" corresponds to a list of real space XY plane vertices defining the
// projection surface from a top-down view
// (2) key "substrate_heights" corresponds to a list of low and high heights at normalized
// parameters along the outline

enum CALIBRATION_MODE {
	CALIBRATION_MANUAL = 0,
	CALIBRATION_AUTOMATED
};

// This tool transforms virtual raw coordinates to virtual real coordinates
class ofxCalibrationTool {
public:

	ofxCalibrationTool();
	~ofxCalibrationTool();

	void setupParams();
	void setup();

	// Update this tool with the tool center point used for calibration
	// Use either of these (not both)
	void update(glm::vec3 _tcp);
	void update(glm::mat4x4 _tcpFrame);


	void loadTargetPlan(string _tpFilename = "");
	bool isTargetPlanLoaded();
	string getTargetPlanName();

	// Begin the calibration process
	bool isReadyToCalibrate(string& err);
	bool isReadyToCalibrate();
	void beginCalibrationProtocol();
	void resetCalibrationProtocol();
	void stopCalibrationProtocol();
	bool isCalibrating();
	void lockTarget();

	string getStatus();
	void drawStatus(int x = 0, int y = 0);

	//void clearCalibration();

	// -----

	// Load a Calibration File
	void loadCalibrationFile(string _calFilename = "");
	bool isCalibrationLoaded();
	string getCalibrationFileName();
	// Transform virtual raw to real
	glm::mat4x4 getMapped(glm::mat4x4 in);
	void map(glm::mat4x4& inOut);
	glm::vec3 getMapped(glm::vec3 in);
	void map(glm::vec3& inOut);

	// -----

	void drawDebug();

	glm::vec3 getZAxis();
	glm::vec3 getYAxis();
	glm::vec3 getXAxis(); 

	string getCalibrationModeName();
	string getProgressString();
	string getTaskString();

private:

	bool bCalibrating = false;

	CALIBRATION_MODE mode = CALIBRATION_MANUAL;

	string tpFilename = "targets.plan";
	string calFilename = "raw2real.calibration";

	// Last tcp observed
	glm::vec3 tcp;
	glm::mat4x4 tcpFrame;
	float lastObservationTime = -1;

	//bool bLockOnStatic = false;
	//float lockTime = 10;
	//float lockDeviance = 0.02; // meters 

	// Json helper
	ofJson js;

	vector<glm::vec3> realTargets; // (physical) real space
	vector<int> square;
	int currentTargetIndex = 0;
	vector<glm::vec3> rawTargets; // (virtual) raw space

	glm::mat4x4 transMat; // transformation matrix
	// Ref: http://www.songho.ca/opengl/gl_transform.html
	//
	// Variable names and order of accessing raw data (stored in columns):
	//	m_0		m_4		m_8		m_12
	//	m_1		m_5		m_9		m_13
	//	m_2		m_6		m_10	m_14
	//	m_3		m_7		m_11	m_15
	//
	// 2D Access indices:
	//	[0][0]	[1][0]	[2][0]	[3][0]
	//	[0][1]	[1][1]	[2][1]	[3][1]
	//	[0][2]	[1][2]	[2][2]	[3][2]
	//	[0][3]	[1][3]	[2][3]	[3][3]
	//
	// Relevant Values:
	// X-Axis		(m_0, m_1, m_2)
	// Y-Axis		(m_4, m_5, m_6)
	// Z-Axis		(m_8, m_9, m_10)
	// Translation	(m_12, m_13, m_14)

	void saveCalibration(string _filepath, glm::mat4x4& _mat);



	// Functions that help finding a rigid body transformation from one
	// point set to another


	// Calculate a transformation
	bool calculateTransformation(vector<glm::vec3>& testPoints, vector<glm::vec3>& refPoints, glm::mat4x4& outTransMat);

	// ** Helper Functions **
	// These functions are taken from
	// https://stackoverflow.com/questions/21206870/opencv-rigid-transformation-between-two-3d-point-clouds/48829595
	cv::Mat_<double> FindRigidTransform(const cv::Mat_<cv::Vec3d>& points1, const cv::Mat_<cv::Vec3d>& points2);
	cv::Vec3d CalculateMean(const cv::Mat_<cv::Vec3d>& points);


	// Apply the calculated transformation to geometry
	glm::mat4x4 applyTransformation(glm::mat4x4& frame, glm::mat4x4& transMat);
	glm::vec3 applyTransformation(glm::vec3& point, glm::mat4x4& transMat);

	bool bCalibrationLoaded = false;
};



// Helpers for converting transformation matrices to usable components
glm::vec3 getTranslation(glm::mat4x4& a);
glm::vec3 getXAxis(glm::mat4x4& a);
glm::vec3 getYAxis(glm::mat4x4& a);
glm::vec3 getZAxis(glm::mat4x4& a);
void ofTransformAndRotate(glm::mat4x4& a);
