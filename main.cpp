#include <iostream>
#include <string>
#include <sstream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/passthrough.h>

using namespace std; 


int main (int argc, char** argv)
{
    string st = "clouds912/";
    string st1 = "cloud";
    string ext = ".pcd";
    string filename;
    string filename2;
    string customcloud;
	for (int i=2; i<35 ; i++)
	{
	if(i!=31){
 	        stringstream ss;
		stringstream cs;
		ss << i;
		cs = st1 + ss.str();
		cout << st1 +ss.str() <<endl;
		filename = st1 + ss.str() +ext;
		filename2 = st+ st1 + ss.str() +ext;
		customcloud = st1 + ss.str();
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr  customcloud (new pcl::PointCloud<pcl::PointXYZRGB>);
      //  pcl::io::loadPCDFile (filename2, *cloud );	
	}	
	}

/*   pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile ("clouds912/cloud2.pcd", *cloud1);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile ("clouds912/cloud3.pcd", *cloud2);

pcl::PointCloud<pcl::PointXYZRGB>::Ptr outputcloud1 (new pcl::PointCloud<pcl::PointXYZRGB>);
pcl::PointCloud<pcl::PointXYZRGB>::Ptr outputcloud2 (new pcl::PointCloud<pcl::PointXYZRGB>);
pcl::PassThrough<pcl::PointXYZRGB> pass; // can do this without parameters
pass.setInputCloud(cloud1);
pass.filter(*outputcloud1);
pass.setInputCloud(cloud2);
pass.filter(*outputcloud2);
    
    pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> icp;
    icp.setInputSource(outputcloud1);
    icp.setInputTarget(outputcloud2);
    pcl::PointCloud<pcl::PointXYZRGB> Final;
    icp.align(Final);
    std::cout << "has converged:" << icp.hasConverged() << " score: " <<
    icp.getFitnessScore() << std::endl;
    std::cout << icp.getFinalTransformation() << std::endl;

	//pcl::io::savePCDFileASCII ("filtered2.pcd", *outputcloud2);
        //pcl::io::savePCDFileASCII ("final.pcd", Final);

*/
    return 0;
}
