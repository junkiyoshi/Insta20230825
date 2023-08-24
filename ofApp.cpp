#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSeedRandom(39);
	ofSetColor(255);
	ofNoFill();
	for (int deg = 0; deg < 360; deg += 30) {

		ofPushMatrix();
		ofRotate(deg);

		auto base_location = glm::vec2(0, -80);
		auto target_location = glm::vec2(0, -340);
		auto distance = target_location - base_location;
		auto len = glm::length(distance);
		auto noise_seed = ofRandom(1000);

		ofBeginShape();
		for (int d = 0; d <= len; d += 1) {

			auto location = base_location + glm::normalize(distance) * d;

			auto gap = abs(len * 0.5 - d);
			auto power = gap < len * 0.35 ? 1 : ofMap(gap, len * 0.35, len * 0.5, 1, 0);

			auto noise_x = ofMap(ofNoise(noise_seed, location.x * 0.1, location.y * 0.015 + ofGetFrameNum() * 0.06), 0, 1, -45, 45);
			int x = (int)(noise_x * power) / 10 * 10;
			location += glm::vec2(x, 0);

			ofVertex(location);
		}
		ofEndShape();

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}