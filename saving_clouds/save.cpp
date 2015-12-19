#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std; 

const string OUT_DIR = "/home/billy/Desktop/Code/project/_newclouds"; 
unsigned int microseconds =1000000;
class SimpleOpenNIViewer 
{ 
public: 
    SimpleOpenNIViewer () : viewer ("PCL Viewer") 
    { 
                frames_saved = 0; 
                save_one = false; 
    } 

    void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud) //change to RGBA
    { 
                if (!viewer.wasStopped()) { 
                        viewer.showCloud (cloud); 

                        if( save_one ) { 
                                save_one = false; 
                                std::stringstream out; 
								out.width(3);
                                out << std::setfill('0') << frames_saved; 
                                std::string name = OUT_DIR + "cloud" + out.str() + ".pcd"; 
                                pcl::io::savePCDFileASCII( name, *cloud ); 
								//cloud push maybe ??
                        } 
                } 
    } 

    void run () 
    { 
                pcl::Grabber* interface = new pcl::OpenNIGrabber(); 

                boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f = 
                        boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1); 

                interface->registerCallback (f); 

                interface->start (); 

                char c; 

                while (!viewer.wasStopped()) 
                { 
                        usleep(microseconds);

                        //c = getchar(); 
                        //if( c == 's' ) { 
                                cout << "Saving frame " << frames_saved << ".\n"; 
                                frames_saved++; 
                                save_one = true; 
                        //} 
                } 

                interface->stop (); 
        } 

        pcl::visualization::CloudViewer viewer; 

        private: 
                int frames_saved; 
                bool save_one; 

}; 

int main () 
{ 
    SimpleOpenNIViewer v; 
    v.run (); 
    return 0; 
}
