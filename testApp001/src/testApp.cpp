#include "testApp.h"
#define NUM 5000//ボールの数を定義
float loc_x[NUM];
float loc_y[NUM];
float speed[NUM];
float decs[NUM];
float speed_x[NUM];
float speed_y[NUM];
float radius[NUM];
int red[NUM];
int green[NUM];
int blue[NUM];

float _fps;
float _gravity;
float _friction;
int _num;

float gravity;
float friction;
int num;
float color[4];
bool mouse_pressed;//マウスクリックされているか
bool _reset;
//--------------------------------------------------------------
void testApp::setup(){
	//ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);//背景色の設定
	ofSetFrameRate(100);//フレームレート
	ofSetCircleResolution(64);//円の解像度
	ofEnableAlphaBlending();
	mouse_pressed = false;
	
	//NUMの数だけ初期値生成
	for (int i=0; i<NUM; i++) {
		loc_x[i] = ofRandom(10, ofGetWidth()-10);
		loc_y[i] = ofRandom(10, ofGetHeight()-10);
		
		speed[i] = ofRandom(2, 8);
		decs[i] = ofRandom(0, 360);
		
		speed_x[i] = speed[i] * cos(decs[i]/180.0f*PI);
		speed_y[i] = speed[i] * sin(decs[i]/180.0f*PI);
		radius[i] = ofRandom(speed[i], speed[i]+1);
		red[i] = ofRandom(0, 255);
		green[i] = ofRandom(0, 255);
		blue[i] = ofRandom(0, 255);
	}
	
	_gravity = 0.0;
	_friction = 1.0;
	_num = 5000;
	gravity = 0.0;
	friction = 1.0;
	num = 5000;
	_fps = 100.0;
	_reset = false;

	gui.setup();
	gui.config->padding = 10;
    gui.config->gridSize.x = 220;
	gui.addSlider("FPS", _fps, 0, 100.0);
	gui.addSlider("GRAVITY", gravity, -0.1, 0.1);
	gui.addSlider("FRICTION", friction, 0.9, 1.0);
	gui.addSlider("PARTICLE", num, 1, 5000);
	//gui.addColorPicker("COLOR", color);
	gui.addButton("RESET", _reset);
	
	 
}

//--------------------------------------------------------------
void testApp::update(){
	//NUMの数だけループ
	for (int i = 0; i<_num; i++) {
		
		if (mouse_pressed) {
//			speed_x[i] = (mouseX - loc_x[i])/8.0;
//			speed_y[i] = (mouseY - loc_y[i])/8.0;
		}
		//重力・摩擦
		speed_x[i] = speed_x[i] * _friction;
		speed_y[i] = speed_y[i] * _friction;
		speed_y[i] = speed_y[i] + _gravity;

		
		loc_x[i] += speed_x[i];
		loc_y[i] += speed_y[i];
		
		if (loc_x[i] < 0) {
			loc_x[i] = 0;
			speed_x[i] = speed_x[i] *-1;
		}
		if (loc_x[i] > ofGetWidth()) {
			loc_x[i] = ofGetWidth();
			speed_x[i] = speed_x[i] *-1;
		}
		if (loc_y[i] <0) {
			loc_y[i] = 0;
			speed_y[i] = speed_y[i] *-1;
		}
		if (loc_y[i] > ofGetHeight()) {
			loc_y[i] = ofGetHeight();
			speed_y[i] = speed_y[i] *-1;
		}
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
//		ofSetColor(0, 0, 0,100);
//		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	for (int i=0; i<_num; i++) {
		ofSetColor(red[i], green[i], blue[i],150);
		ofCircle(loc_x[i], loc_y[i], radius[i]);
	}
	gui.draw();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //キー入力でモード切り替え
    switch (key){
        case 'f':
            //フルスクリーンのon/off
            ofToggleFullscreen();
			
        case 'g':
            //Gui表示のon/off
            gui.toggleDraw();
			ofEnableAlphaBlending();
            break;
			
    }
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	mouse_pressed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	mouse_pressed = false;
	if (_reset) {
		gravity = 0.0;
		friction = 1.0;
		num = 5000;
		_fps = 100.0;
		_reset = false;
		for (int i=0; i<num; i++) {
					speed_x[i] = speed[i] * cos(decs[i]/180.0f*PI);
					speed_y[i] = speed[i] * sin(decs[i]/180.0f*PI);
		}
	}
	
	_gravity = gravity;
	_friction = friction;
	_num = num;
	ofSetFrameRate(_fps);
	
}


//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}