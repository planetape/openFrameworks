#include "testApp.h"

float scaleImage;
float imageWidth;
float imageHeight;
int px;
int py;

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);

	hearFinder.setup("cascade_oppai.xml");
    //画像データ読み込み
    myImage.loadImage("oppai2d2.jpg");
    myImageWidth = myImage.width;
    myImageHeight = myImage.height;
    //使用する画像の領域を確保
    colorImg.allocate(myImageWidth,myImageHeight);
    grayImage.allocate(myImageWidth,myImageHeight);
    grayBg.allocate(myImageWidth,myImageHeight);
    grayDiff.allocate(myImageWidth,myImageHeight);
    //変数初期化
    bLearnBakground = false;
    showCvAnalysis =false;
    threshold = 20;
    videoMode = 0;
    scalePenguin = 1.0;
    yPenguin = 0;
    //GUI
	gui.setup();
	gui.config->padding = 10;
    gui.config->gridSize.x = 220;
	gui.addSlider("SCALE", scalePenguin, 0.1, 2.0);
	gui.addSlider("Y", yPenguin, -200, 200);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    //取り込んだイメージをキャプチャ
    colorImg.setFromPixels(myImage.getPixels(),myImageWidth,myImageHeight);
    //左右反転
    //colorImg.mirror(false, true);
    //グレースケールに変換
    grayImage = colorImg;
    //顔検出
    hearFinder.findHaarObjects(grayImage);
    //カラー映像
    colorImg.draw(0, 0);
    ofNoFill();
    if(hearFinder.blobs.size() > 0) {
        for (int i=0; i<hearFinder.blobs.size();i++) {
            ofRectangle cur = hearFinder.blobs[i].boundingRect;
            
            //scaleImage = (float)cur.width*scale / myImageWidth;
            imageWidth = cur.width;
            imageHeight = cur.height;
            px = cur.x;
            py = cur.y;
            ofRect(px, py ,imageWidth, imageHeight);            
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //キー入力でモード切り替え
    switch (key){
        case 'a':
            //解析結果の表示の on / off
            showCvAnalysis ? showCvAnalysis=false : showCvAnalysis=true;
            break;            
        case 'f':
            //フルスクリーンのon/off
            ofToggleFullscreen();
            break;
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

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    float imageScaleH = ofGetHeight() / 240;
    float imageScaleW = ofGetWidth() / 320;
    if(imageScaleW > imageScaleH){
        scale = imageScaleH;
    }else{
        scale = imageScaleW;        
    }
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}