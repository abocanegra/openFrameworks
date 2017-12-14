#pragma once

#include "ofMain.h"
#include "ofThread.h"
#include "ofxCv.h"
#include "ofxPointGreyGigECamera.h"
#include "calibration.h"

class threadPointGreyGigECamera : public ofThread {

    public:
        threadPointGreyGigECamera() {
            TdeviceID        = 0;
            TsetToColor      = false;
            TbUseTexture     = false;
            T_pixelFmt       = "PIXEL_FORMAT_MONO8";
            TabsFrameRate    = 30;
            TcamZoom         = 4;
            camSetup         = false;
            TtotalNumCameras = 1;
            Tcalibration     = 0;
            TcalActive       = false;
            TsetCamWidth     = 1920;
            TsetCamHeight    = 1200;
            TxOffset         =0;
            TyOffset         =0;
            TresetCalibration = false;
        }

         /// Start the thread.
        void start()
        {
            if(!camSetup){
                setupCamera();
            }
            startThread();
           // iter = 0;
        }

        bool setupCamera(){
            if(lock()){
                cam.deviceID =      TdeviceID;
                cam.setToColor =    TsetToColor;
                cam.bUseTexture =   TbUseTexture;
                cam._pixelFmt =     T_pixelFmt;
                cam.absFrameRate =  TabsFrameRate;
                cam.camWidth =      TsetCamWidth;
                cam.camHeight =     TsetCamHeight;
                cam.xOffset =       TxOffset;
                cam.yOffset =       TyOffset;
                cam.setup();
                TcamWidth =         cam.camWidth;
                TcamHeight =        cam.camHeight;
                TcamWidthRatio =    ofGetWidth()/TcamWidth; //1
                TcamHeightRatio =   ofGetHeight()/TcamHeight; //0.1

                if(TcamWidthRatio < 1 || TcamHeightRatio < 1){
                    if(TcamWidthRatio < TcamHeightRatio){
                        TfullScaledWidth = (TcamWidth * TcamWidthRatio);
                        TfullScaledHeight = (TcamHeight * TcamWidthRatio);
                    }else{
                        TfullScaledWidth = (TcamWidth * TcamHeightRatio);
                        TfullScaledHeight = (TcamHeight * TcamHeightRatio);
                    }
                }else{
                    TfullScaledWidth = TcamWidth;
                    TfullScaledHeight = TcamHeight;
                }

                /*Set up matrix for Feed Locations at different zoom levels*/
                //TotalNumberCameras
                for(uint64_t i=1; i<=16; i++){
                    if(i==1){
                        TzL = 1;
                    }else if(i >1 && i <=4){
                        TzL = 2;
                    }else if(i>4 && i <=9){
                        TzL = 3;
                    }else if(i>9 && i<=16){
                        TzL = 4;
                    }
                    //By Camera
                    for(int j=0; j<i; j++){
                        int cols = ofGetWidth()/(TfullScaledWidth/TzL);
                        int rows = ofGetHeight()/(TfullScaledHeight/TzL);
                        int currCol = ((j)*(TfullScaledWidth/TzL))/TfullScaledWidth;
                        int currRow = ((j)*(TfullScaledHeight/TzL))/TfullScaledHeight;
                        camCoord[i][j][0]=TfullScaledWidth/TzL;
                        camCoord[i][j][1]=TfullScaledHeight/TzL;
                        camCoord[i][j][2]=(j%cols)*camCoord[i][j][0];
                        camCoord[i][j][3]=currRow*camCoord[i][j][1];
                   }
                }
                camIsColor  = cam.isSetToColor();
                camSetup = true;
                if(Tcalibration){
                    TcalActive = true;
                    camCal.camera = TdeviceID;
                    camCal.active = TcalActive;
                    camCal.setup(camImage);
                }
            }
            unlock();
            return camSetup;
        }
       /// Signal the thread to stop.  After calling this method,
        /// isThreadRunning() will return false and the while loop will stop
        /// next time it has the chance to.
        void stop()
        {
            //cam.~ofxPointGreyGigECamera();
            camSetup = false;
            stopThread();
        }

        /// Our implementation of threadedFunction.
        void threadedFunction()
        {
            while(isThreadRunning())
            {
                // Attempt to lock the mutex.  If blocking is turned on,
                if(lock())
                {
                    cam.update();
                    camCal.active = TcalActive;
                    if(TresetCalibration){
                        camCal.reset();
                        TresetCalibration = false;
                    }
                    // called if lock() returned true above.
                    unlock();
                }
                else
                {
                    // If we reach this else statement, it means that we could not
                    // lock our mutex, and so we do not need to call unlock().
                    // Calling unlock without locking will lead to problems.

                    // ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
                }
            }
     }

        void draw()
        {

            if(lock())
            {
                camImage = cam.drawImage();
                if(Tcalibration){
                    camCal.update(camImage);
                    camCal.draw(camCoord[TtotalNumCameras][TdeviceID][0], camCoord[TtotalNumCameras][TdeviceID][1]);
                }else{
                    if(TbUseTexture){
                        camImage.draw(camCoord[TtotalNumCameras][TdeviceID][2], camCoord[TtotalNumCameras][TdeviceID][3], camCoord[TtotalNumCameras][TdeviceID][0],  camCoord[TtotalNumCameras][TdeviceID][1]);
                    }
                }
                TcamInfo = cam.drawInfo();
                ofSetHexColor(0xffffff);
                ofDrawBitmapString(TcamInfo, camCoord[TtotalNumCameras][TdeviceID][2] + 15,camCoord[TtotalNumCameras][TdeviceID][3] +25);
                unlock();
            }
            else
            {
                // If we reach this else statement, it means that we could not
                // lock our mutex, and so we do not need to call unlock().
                // Calling unlock without locking will lead to problems.

                // ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
            }
        }

        bool        Tcalibration;
        bool        TcalActive;
        bool        TresetCalibration;
        uint64_t	TdeviceID;
        bool        TsetToColor;
        bool        TbUseTexture;
        string      T_pixelFmt;
        float       TcamWidth;
        float       TcamHeight;
        uint64_t    TabsFrameRate;
        uint64_t    TcamZoom;
        uint64_t    TzL;
        bool        camSetup;
        uint64_t    TtotalNumCameras;
        //int iter;
        string      TcamInfo;
        uint64_t    TsetCamWidth;
        uint64_t    TsetCamHeight;
        uint64_t    TxOffset;
        uint64_t    TyOffset;
    protected:
        bool       camIsColor;
        uint64_t   TcamCornerX;
        uint64_t   TcamCornerY;
        float      TcamWidthRatio;
        float      TcamHeightRatio;
        float      TfullScaledWidth;
        float      TfullScaledHeight;
        int        camCoord[16][16][4];

        FlyCapture2::ofxPointGreyGigECamera cam;
        GigECalibration        camCal;
        ofImage                camImage;
};
