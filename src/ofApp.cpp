#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(720,720);
    start = false;
    lift = false;
    
    ofSetLineWidth(5);
    ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    
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
