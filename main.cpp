#include <iostream>
#include <string>
#include <sstream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/passthrough.h>

using namespace std; 
using namespace pcl;

int main (int argc, char** argv)
{
    string st = "clouds912/";
    string st1 = "cloud";
    string ext = ".pcd";
    string filename;
    string filename2;

vector < PointCloud<PointXYZ>::Ptr, Eigen::aligned_allocator <PointCloud <PointXYZ>::Ptr > > sourceClouds;

	for (int i=2; i<35 ; i++)
	{
		if(i!=31){

 	    stringstream ss;
		ss << i;

		filename2 = st+ st1 + ss.str() +ext;
		PointCloud<PointXYZ>::Ptr sourceCloud(new PointCloud<PointXYZ>);
      	io::loadPCDFile (filename2, *sourceCloud );	
         //  sourceClouds.push_back(sourceCloud);

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
