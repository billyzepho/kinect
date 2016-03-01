#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/common/time.h>
#include <iostream>
#include <vector>

using namespace std; 
using namespace pcl;

vector<boost::shared_ptr<PointCloud<PointXYZ>  > > sclouds;

class SimpleOpenNIProcessor
{
public:

  void cloud_cb_ (const PointCloud<PointXYZ>::ConstPtr &cloud)
  {

    static unsigned count = 0;
    static double last = pcl::getTime ();
   // if (++count == 30)
    //{
      double now = pcl::getTime ();
      std::cout << "distance of center pixel :" << cloud->points [(cloud->width >> 1) * (cloud->height + 1)].z << " mm. Average framerate: " << double(count)/double(now - last) << " Hz" <<  std::endl;
      count = 0;
      last = now;
    //}
	sclouds.push_back(cloud);
  }
  
  void run ()
  {
    // create a new grabber for OpenNI devices
    Grabber* interface = new OpenNIGrabber();

    // make callback function from member function
    boost::function<void (const boost::shared_ptr<const pcl::PointCloud<pcl::PointXYZ> >&)> f =
      boost::bind (&SimpleOpenNIProcessor::cloud_cb_, this, _1);

    // connect callback function for desired signal. In this case its a point cloud with color values
    boost::signals2::connection c = interface->registerCallback (f);

    // start receiving point clouds
    interface->start ();

    // wait until user quits program with Ctrl-C, but no busy-waiting -> sleep (1);
    while (true)
       boost::this_thread::sleep (boost::posix_time::seconds (1));

    // stop the grabber
    interface->stop ();
  }
};

int main ()
{

  SimpleOpenNIProcessor v;
  v.run ();
  return (0);
}
