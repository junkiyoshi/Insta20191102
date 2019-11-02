#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh_list.clear();

	auto range = 120;
	auto span = 240;
	for (int x = -ofGetWidth() * 0.5; x <= ofGetWidth() * 0.5; x += span) {

		for (int y = -ofGetHeight() * 0.5; y <= ofGetHeight() * 0.5; y += span) {

			for (int z = -ofGetHeight() * 0.5; z <= ofGetHeight() * 0.5; z += span) {

				ofMesh mesh;
				mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
				for (int i = 0; i < 4; i++) {

					auto location = glm::vec3(
						x + ofMap(ofNoise(ofRandom(10000), this->noise_seed), 0, 1, -range * 0.5, range * 0.5),
						y + ofMap(ofNoise(ofRandom(10000), this->noise_seed), 0, 1, -range * 0.5, range * 0.5),
						z + ofMap(ofNoise(ofRandom(10000), this->noise_seed), 0, 1, -range * 0.5, range * 0.5));
					mesh.addVertex(location);
				}

				for (int i = 0; i < mesh.getVertices().size(); i++) {

					mesh.addIndex(i);
					mesh.addIndex((i + 1) % mesh.getVertices().size());
				}

				int hue = ofRandom(255);
				ofColor color;
				for (int i = 0; i < 4; i++) {
				
					color.setHsb((hue + i * 100) % 255, 200, 255);
					mesh.addColor(color);
				}

				this->mesh_list.push_back(mesh);
			}
		}
	}

	if (ofGetFrameNum() % 60 < 45) {

		this->noise_seed += ofMap(ofGetFrameNum() % 60, 0, 45, 0.03, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	for (auto& mesh : this->mesh_list) {

		mesh.draw();
		for (int i = 0; i < mesh.getVertices().size(); i++) {

			ofSetColor(mesh.getColor(i));
			ofDrawSphere(mesh.getVertex(i), 6);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}