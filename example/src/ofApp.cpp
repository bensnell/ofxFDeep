#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	model = std::make_unique<fdeep::model>(fdeep::load_model(ofToDataPath("assets/models/fldc_pi_38_1550_fdeep_model.json")));

	/////// SINGLE ////////

	cout << "Testing predict()..." << endl;
	for (int i = 0; i < 20; i++) {

		uint64_t startTime = ofGetElapsedTimeMicros();
		const auto result = model->predict(
			{ fdeep::tensor(fdeep::tensor_shape(128, 1),  {1, -1, 1,-1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1,-1, 1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 1,-1, 1,-1,-1, 1,-1, 1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1, 1, 1, 1, 1,-1, 1,-1,-1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1, 1,-1, 1,-1,-1, 1,-1,-1, 1,-1, 1,-1, 1,-1,-1,-1, 1,-1, 1,-1, 1, 1, 1, 1,-1,-1, 1}) });
			//{ fdeep::tensor(fdeep::tensor_shape(128, 1),  1) });

		uint64_t stopTime = ofGetElapsedTimeMicros();
		cout << "Time: " << double(stopTime - startTime) / 1000.0 << " ms" << endl;
		//std::cout << fdeep::show_tensors(result) << "\tin " << double(stopTime - startTime)/1000.0 << " ms" << endl;

	}


	/////// MULTI ////////

	for (int e = 1; e < 4; e++) {
		int nSamples = pow(10, e);

		cout << "Testing predict_multi() with " << nSamples << " samples ..." << endl;
		for (int i = 0; i < 20; i++) {

			auto ten = fdeep::tensor(fdeep::tensor_shape(128, 1), { 1, -1, 1,-1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1,-1, 1,-1, 1, 1,-1,-1, 1,-1,-1,-1, 1,-1, 1,-1,-1, 1,-1, 1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1, 1, 1, 1, 1,-1, 1,-1,-1,-1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1, 1,-1, 1,-1,-1, 1,-1,-1, 1,-1, 1,-1, 1,-1,-1,-1, 1,-1, 1,-1, 1, 1, 1, 1,-1,-1, 1 });
			fdeep::tensors_vec tens;
			for (int i = 0; i < nSamples; i++) {
				tens.push_back({ ten });
			}

			uint64_t startTime = ofGetElapsedTimeMicros();
			const auto result = model->predict_multi(tens, true);
			uint64_t stopTime = ofGetElapsedTimeMicros();
			cout << "Time: " << double(stopTime - startTime) / 1000.0 << " ms" << endl;
			//for (auto& r : result) {
			//	std::cout << fdeep::show_tensor5s(r) << endl;
			//}

		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){



}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 200, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
