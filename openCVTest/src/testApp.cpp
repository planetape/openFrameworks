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
#ifdef _USE_LIVE_VIDEO
    //カメラから映像を取り込んで表示
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320, 240);
#else
    //カメラ不使用の場合ムービーファイル読み込み再生
    vidPlayer.loadMovie("sample.mov");
    vidPlayer.play();
#endif
    //使用する画像の領域を確保
    colorImg.allocate(320,240);
    grayImage.allocate(320,240);
    grayBg.allocate(320, 240);
    grayDiff.allocate(320, 240);
    //画像データ読み込み
    myImage.loadImage("penguin.png");
    myImageWidth = 320;
    myImageHeight = 552;
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
    bool bNewFrame = false;
#ifdef _USE_LIVE_VIDEO
    vidGrabber.grabFrame();
    bNewFrame = vidGrabber.isFrameNew();
#else
    vidPlayer.idleMovie();
    bNewFrame = vidPlayer.isFrameNew();
#endif
    //フレームが切り替わったときのみ画像解析
    if(bNewFrame){
        //取り込んだイメージをキャプチャ
        colorImg.setFromPixels(vidGrabber.getPixels(),320,240);
        //左右反転
        colorImg.mirror(false, true);
        //グレースケールに変換
        grayImage = colorImg;
        //顔検出
        hearFinder.findHaarObjects(grayImage);
        if(hearFinder.blobs.size() > 0) {
            ofRectangle cur = hearFinder.blobs[0].boundingRect;
            
            scaleImage = (float)cur.width*scale / myImageWidth;
            imageWidth = (float)cur.width*scale*scalePenguin;
            imageHeight = myImageHeight*scaleImage*scalePenguin;
            px = cur.x*scale+(float)cur.width*scale/2 - imageWidth / 2;
            py = cur.y*scale+(float)cur.height*scale/2 - imageHeight / 2 + yPenguin;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
//モードきりかえ
    
    
    switch (videoMode) {
        case 1:
            //グレースケール映像
//            grayImage.draw(0, 0,ofGetWidth(),ofGetHeight());
            grayImage.draw(0, 0);
            break;
        default:
            //カラー映像
            colorImg.draw(0, 0,320*scale,240*scale);
            //colorImg.draw(40, 40,480,360);
            break;
    }
    
    ofNoFill();

    //画像表示
    if(hearFinder.blobs.size() > 0) {
        if(showCvAnalysis){
            myImage.draw(px, py ,imageWidth, imageHeight);
        }else{
            ofRect(px, py ,imageWidth, imageHeight);            
        }
    }
    gui.draw();
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