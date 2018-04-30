import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "../../.."

    ofApp {
        name: { return FileInfo.baseName(path) }

        files: [
            'src/app/ofAppiOSWindow.h',
            'src/app/ofAppiOSWindow.mm',
            'src/app/ofxiOSApp.h',
            'src/core/ofxiOSAppDelegate.h',
            'src/core/ofxiOSAppDelegate.mm',
            'src/core/ofxiOSEAGLView.h',
            'src/core/ofxiOSEAGLView.mm',
            'src/core/ofxiOSViewController.h',
            'src/core/ofxiOSViewController.mm',
            'src/events/ofxiOSAccelerometer.mm',
            'src/events/ofxiOSAlerts.h',
            'src/events/ofxiOSAlerts.mm',
            'src/events/ofxiOSAlertsListener.h',
            'src/gl/EAGLView.h',
            'src/gl/EAGLView.m',
            'src/gl/ES1Renderer.h',
            'src/gl/ES1Renderer.m',
            'src/gl/ES2Renderer.h',
            'src/gl/ES2Renderer.m',
            'src/gl/ESRenderer.h',
            'src/main.cpp',
            'src/ofApp.cpp',
            'src/ofApp.h',
            'src/ofxiOS.h',
            'src/ofxiOSConstants.h',
            'src/ofxiOSExtensions.h',
            'src/ofxiPhone.h',
            'src/ofxtvOS.h',
            'src/sound/AVSoundPlayer.h',
            'src/sound/AVSoundPlayer.m',
            'src/sound/SoundEngine.cpp',
            'src/sound/SoundEngine.h',
            'src/sound/SoundInputStream.h',
            'src/sound/SoundInputStream.m',
            'src/sound/SoundOutputStream.h',
            'src/sound/SoundOutputStream.m',
            'src/sound/SoundStream.h',
            'src/sound/SoundStream.m',
            'src/sound/ofxOpenALSoundPlayer.cpp',
            'src/sound/ofxOpenALSoundPlayer.h',
            'src/sound/ofxiOSSoundPlayer.h',
            'src/sound/ofxiOSSoundPlayer.mm',
            'src/sound/ofxiOSSoundStream.h',
            'src/sound/ofxiOSSoundStream.mm',
            'src/sound/ofxiOSSoundStreamDelegate.h',
            'src/sound/ofxiOSSoundStreamDelegate.mm',
            'src/tvOS/ofxtvOSAppDelegate.h',
            'src/tvOS/ofxtvOSAppDelegate.mm',
            'src/tvOS/ofxtvOSViewController.h',
            'src/tvOS/ofxtvOSViewController.mm',
            'src/utils/ofxiOSCoreLocation.h',
            'src/utils/ofxiOSCoreLocation.mm',
            'src/utils/ofxiOSCoreMotion.h',
            'src/utils/ofxiOSCoreMotion.mm',
            'src/utils/ofxiOSEventAdapter.h',
            'src/utils/ofxiOSEventAdapter.mm',
            'src/utils/ofxiOSExternalDisplay.h',
            'src/utils/ofxiOSExternalDisplay.mm',
            'src/utils/ofxiOSExtras.h',
            'src/utils/ofxiOSExtras.mm',
            'src/utils/ofxiOSImagePicker.h',
            'src/utils/ofxiOSImagePicker.mm',
            'src/utils/ofxiOSKeyboard.h',
            'src/utils/ofxiOSKeyboard.mm',
            'src/utils/ofxiOSMapKit.h',
            'src/utils/ofxiOSMapKit.mm',
            'src/utils/ofxiOSMapKitDelegate.h',
            'src/utils/ofxiOSMapKitDelegate.mm',
            'src/utils/ofxiOSMapKitListener.h',
            'src/utils/ofxiPhoneExtras.h',
            'src/video/AVFoundationVideoGrabber.h',
            'src/video/AVFoundationVideoGrabber.mm',
            'src/video/AVFoundationVideoPlayer.h',
            'src/video/AVFoundationVideoPlayer.m',
            'src/video/ofxiOSVideoGrabber.h',
            'src/video/ofxiOSVideoGrabber.mm',
            'src/video/ofxiOSVideoPlayer.h',
            'src/video/ofxiOSVideoPlayer.mm',
        ]

        of.addons: [
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
                                // will compile OF only once for all your projects
                                // otherwise compiled per project with qbs

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
