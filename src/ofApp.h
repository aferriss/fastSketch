#pragma once

#include "ofMain.h"
#include "ofxTablet.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void tabletMoved(TabletData &data);
        vector<vector<ofPolyline> > scenes;
        vector<ofPolyline> lines;
        ofPolyline p;
        bool start;
        bool lift;
    
        ofMatrix4x4 tabmtx;
    
        ofPolyline tabletLine;
    
    int winX, winY, screenX, screenY, w, h, tabX, tabY, count;
    float press;
    
    string filename;
    vector<ofVec3f> points;
    bool clear;
};
