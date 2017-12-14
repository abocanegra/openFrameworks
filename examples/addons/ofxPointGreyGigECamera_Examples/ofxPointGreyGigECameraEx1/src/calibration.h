#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

class GigECalibration{

    public:
        GigECalibration(){
            active = true;
            camera = 0;
        }

        virtual ~GigECalibration(){

        }

        void setup(ofImage cam) {
            camImage = cam;
            calibration.setFillFrame(false);
            FileStorage settings(ofToDataPath("settings.yml"), FileStorage::READ);
            if(settings.isOpened()) {
                int xCount = settings["xCount"], yCount = settings["yCount"];
                calibration.setPatternSize(xCount, yCount);
                float squareSize = settings["squareSize"];
                calibration.setSquareSize(squareSize);
                CalibrationPattern patternType;
                switch(settings["patternType"]) {
                    case 0: patternType = CHESSBOARD; break;
                    case 1: patternType = CIRCLES_GRID; break;
                    case 2: patternType = ASYMMETRIC_CIRCLES_GRID; break;
                }
                calibration.setPatternType(patternType);
                sprintf(
                        calibrationFile,
                        "calibration-cam_%u.yml",
                        camera
                    );

            }

            imitate(undistorted, camImage);
            imitate(previous, camImage);
            imitate(diff, camImage);

            lastTime = 0;

            //active = true;
        }

            void update(ofImage cam) {
                camImage = cam;
                Mat camMat = toCv(camImage);
                Mat prevMat = toCv(previous);
                Mat diffMat = toCv(diff);

                absdiff(prevMat, camMat, diffMat);
                camMat.copyTo(prevMat);

                diffMean = mean(Mat(mean(diffMat)))[0];

                float curTime = ofGetElapsedTimef();
                if(active && curTime - lastTime > timeThreshold && diffMean < diffThreshold) {
                    if(calibration.add(camMat)) {
                        cout << "re-calibrating" << endl;
                        calibration.calibrate();
                        if(calibration.size() > startCleaning) {
                            calibration.clean();
                        }
                        calibration.save(calibrationFile);
                        lastTime = curTime;
                    }
                }

                if(calibration.size() > 0) {
                    calibration.undistort(toCv(camImage), toCv(undistorted));
                    undistorted.update();
                }

        }

        void draw(int camW, int camH) {
            ofSetColor(255);
            camImage.draw(100, 100,camW/2, camH/2);
            undistorted.draw(camW/2+100, 100, camW/2,camH/2);

            if(active){
                ofDrawBitmapString("Calibration Active",ofGetWidth()-200,20);
            }else{
                ofDrawBitmapString("Calibration Inactive",ofGetWidth()-200,20);
            }
            ofDrawBitmapString(calibrationFile,ofGetWidth()-200,35);

            stringstream intrinsics;
            intrinsics << "fov: " << toOf(calibration.getDistortedIntrinsics().getFov()) << " distCoeffs: " << calibration.getDistCoeffs();
            drawHighlightString(intrinsics.str(), 10, 20, yellowPrint, ofColor(0));
            drawHighlightString("movement: " + ofToString(diffMean), 10, 40, cyanPrint);
            drawHighlightString("reproj error: " + ofToString(calibration.getReprojectionError()) + " from " + ofToString(calibration.size()), 10, 60, magentaPrint);
            for(int i = 0; i < calibration.size(); i++) {
                drawHighlightString(ofToString(i) + ": " + ofToString(calibration.getReprojectionError(i)), 10, 80 + 16 * i, magentaPrint);
            }
        }

        bool reset(){
            calibration.reset();
            ofLog(OF_LOG_NOTICE,"Calibration Reset");
            return true;
        }
        bool active;
        uint64_t camera;
        char calibrationFile[22];
   protected:
        const float diffThreshold = 2.5; // maximum amount of movement
        const float timeThreshold = 1; // minimum time between snapshots
        const int startCleaning = 10; // start cleaning outliers after this many samples

        ofImage camImage;
        ofImage undistorted;
        ofPixels previous;
        ofPixels diff;
        float diffMean;

        float lastTime;
        Calibration calibration;
};
