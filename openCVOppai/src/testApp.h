#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"
#include "ofxSimpleGuiToo.h"

#define _USE_LIVE_VIDEO

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
#ifdef _USE_LIVE_VIDEO
    ofVideoGrabber vidGrabber;
#else
    ofVideoPlayer vidPlayer;
#endif
    
    ofxCvColorImage colorImg;//オリジナルのカラー映像
    ofxCvGrayscaleImage grayImage;//グレースケールに変換後
    ofxCvGrayscaleImage grayBg;//キャプチャした背景画像
    ofxCvGrayscaleImage grayDiff;//差分画像
    ofxCvContourFinder contourFinder;//輪郭抽出のためのクラス
    ofxCvHaarFinder hearFinder;//顔検出のためのクラス
    ofImage myImage;//画像ファイル読み込み
	ofxSimpleGuiToo gui;

    int myImageWidth;
    int myImageHeight;
    bool bLearnBakground;//背景画像を登録したか
    bool showCvAnalysis;//解析結果を表示するか
    int threshold;//2値化の際のしきい値
    int videoMode;//表示する画像を選択
    float scale;//画像の縮尺率
    float scalePenguin;//ペンギン帽子の縮尺率
    int yPenguin;//ペンギン帽子のy軸

    
};
