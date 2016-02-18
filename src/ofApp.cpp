#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = 720;
    h = w;
    winX = ofGetWindowPositionX();
    winY = ofGetWindowPositionY();
    screenX = ofGetScreenWidth();
    screenY = ofGetScreenHeight();
    
    ofSetWindowShape(w,h);
    start = false;
    lift = false;
    
    ofSetLineWidth(5);
    
    tabmtx = ofMatrix4x4::newIdentityMatrix();
    ofxTablet::start();
    ofAddListener(ofxTablet::tabletEvent, this, &ofApp::tabletMoved);
    
    //    ofSetColor(255);
//    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    ofSetBackgroundAuto(false);
    
    count = 0;
    
    filename = "scene_"+ofToString(count)+"_"+ofGetTimestampString() + ".txt";
    clear = true;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(ofGetFrameNum()<10 || clear){
        ofSetColor(255);
        ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
        clear = false;
    }
    
    ofSetColor(0);
    if(ofGetFrameNum()%10 == 0 && scenes.size()>0 && scenes[scenes.size()-1].size() > 0 ){
        if(!lift){
            scenes[scenes.size()-1][scenes[scenes.size()-1].size()-1].curveTo(ofGetMouseX(), ofGetMouseY());
        }
    }
    
    if(scenes.size()>0 && scenes[scenes.size()-1].size() > 0){
        //lines[lines.size()-1].draw();
        for(int i = 0; i< scenes[scenes.size()-1].size(); i++){
            scenes[scenes.size()-1][i].draw();
        }
    }
    
    
    if(press > 1){
        points.push_back(ofVec3f(tabX, tabY, press));
        ofDrawCircle(tabX, tabY, press );
    }
    
}
//--------------------------------------------------------------
void ofApp::tabletMoved(TabletData &data) {
    
    tabX = ofMap(data.abs_screen[0], 0,1, -winX, -winX+screenX );
    tabY = ofMap(1.0 - data.abs_screen[1], 0,1, -winY, -winY+screenY)-48; // 48 = top bar *2?
    press = (ofMap(data.pressure, 0,1, 1, 20));
    
    if(data.pressure>0){
        
        tabletLine.curveTo(ofPoint( tabX, tabY ));
        
    }
    
    cout<<ofToString(data.pressure)<<endl;
    
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    
    
    lift = true;
        
    for(int i =0; i<scenes.size(); i++){
        string fn = "scene_"+ofToString(i+1)+"_"+ofGetTimestampString() + ".txt";
        ofFile file = ofFile(fn, ofFile::WriteOnly);
        for(int j = 0; j<scenes[i].size(); j++){
            vector<ofVec3f> verts = scenes[i][j].getVertices();
            for(int k = 0; k<verts.size(); k++){
                file << ofToString(verts[k]) + "\n";
                //cout<<ofToString(verts[k])<<endl;
            }
            file << "new line \n";
        }
    }

    
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        count++;
        filename = "scene_"+ofToString(count)+"_"+ofGetTimestampString();
        
        ofFile tabFile = ofFile(filename + ".txt", ofFile::WriteOnly);
        for(int i = 0; i<points.size(); i++){
            tabFile << ofToString(points[i]) + "\n";
        }
        ofImage pix;
        pix.grabScreen(0, 0, w, h);
        ofSaveImage(pix.getPixels(), filename + ".jpg");
        points.clear();
        clear = true;
    }
    
    if(key == 's'){
        vector<ofPolyline> lineSet;
        ofPolyline newLine;
        scenes.push_back(lineSet);
        scenes[scenes.size()-1].push_back(newLine);
    }
    
    if(key == 'n'){
        ofPolyline newLine;
        scenes[scenes.size()-1].push_back(newLine);
        lift = true;
    }
    
    if(key == 'l'){
        lift = false;
    }
    
    if(key == 'z'){
        
        //lines[lines.size()-1].draw();
        for(int i = 0; i< scenes[scenes.size()-1].size(); i++){
            vector<ofVec3f> points = scenes[scenes.size()-1][i].getVertices();
            for(int p = 0; p<points.size(); p++){
                
                scenes[scenes.size()-1][i].getVertices()[p].x = ofSignedNoise(p*ofGetFrameNum()*0.001,p,i);//*ofRandom(6);
                scenes[scenes.size()-1][i].getVertices()[p].y = ofSignedNoise(p*ofGetFrameNum()*0.005,p,i);//*ofRandom(6);
            }
        }
    
    }
    
    if(key == 'p'){
        lift = true;
        
            for(int i =0; i<scenes.size(); i++){
                //string fn = ofGetTimestampString() + ".txt";
                //ofFile file = ofFile(fn, ofFile::WriteOnly);
                for(int j = 0; j<scenes[i].size(); j++){
                    vector<ofVec3f> verts = scenes[i][j].getVertices();
                    for(int k = 0; k<verts.size(); k++){
                        //file << ofToString(scenes[i][j].getVertices()[k]) + "\n";
                        cout<<ofToString(verts[k])<<endl;
                    }
                    //file << "new line";
                }
            }
        
    }
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
        ofPolyline newLine;
        lines.push_back(newLine);
        //scenes.push_back(lines);
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
