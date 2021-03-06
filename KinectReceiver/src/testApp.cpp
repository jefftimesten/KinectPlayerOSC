#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	//we run at 60 fps!
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
    
    cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << endl;
    cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << endl;
    cout << "CELL_SIZE: " << CELL_SIZE << endl;
    cout << "GRID_WIDTH: " << GRID_WIDTH << endl;
    cout << "GRID_HEIGHT: " << GRID_HEIGHT << endl;
    cout << "NUM_CELLS: " << NUM_CELLS << endl;
        

    int port = 12345;
    receiver.setup( port );

    
    bPlaying = false;
    
    
	//
	// Initialize the cells
	//
	for(int i=0; i<NUM_CELLS; i++) {
		p1[i] = 0;
		p2[i] = 0;
	}
}

//--------------------------------------------------------------
void testApp::update(){

    if(bPlaying) 
    {
        string line = datafile.getNextLine();
        if(line!="")
        {
            vector<string> updates = ofSplitString(line, ",", true, true);
            for(int i=0; i<updates.size(); i++)
            {
                int packed = ofToInt(updates[i]);
                int n = packed >> 8;
                p1[n] = packed & 0x0000FF;
                p2[n] = p1[n];
            }
        }
    }
    
    while( receiver.hasWaitingMessages() )
	{
		ofxOscMessage m;
		receiver.getNextMessage( &m );
        if(m.getAddress()=="/p1")
        {
            vector<string> updates = ofSplitString(m.getArgAsString(0), ",", true, true);
            for(int i=0; i<updates.size(); i++)
            {
                int packed = ofToInt(updates[i]);
                int n = packed >> 8;
                p1[n] = packed & 0x0000FF;
            }
        }
        
        if(m.getAddress()=="/p2")
        {
            vector<string> updates = ofSplitString(m.getArgAsString(0), ",", true, true);
            for(int i=0; i<updates.size(); i++)
            {
                int packed = ofToInt(updates[i]);
                int n = packed >> 8;
                p2[n] = packed & 0x0000FF;
            }
        } 
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    int size=8;
	for(int y=0; y < GRID_HEIGHT; y++)
	for(int x=0; x < GRID_WIDTH; x++)
	{
		int i = y * GRID_WIDTH + x;
        
        if(p1[i]!=0)
        {
            ofSetColor( p1[i], p1[i], p1[i] );
            ofRect(x*size, y*size, size, size);
        }
        
        if(p2[i]!=0)
        {
            ofSetColor( p2[i], p2[i], p2[i] );
            ofRect((x+GRID_WIDTH)*size, y*size, size, size);
        }
	}

    ofSetColor(255);
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

    switch(key) {
        case 'o':
        case 'O': {
            ofFileDialogResult result = ofSystemLoadDialog();
            datafile = ofBufferFromFile(result.getPath());
            datafile.resetLineReader();
            bPlaying = true;
        } break;
        case 'c':
        case 'C':
            
            break;
    }
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

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
