#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/filter.h>
using namespace std; 
using namespace pcl;

int main (int argc, char** argv)
{

    string st = "clouds912/";
    string st1 = "cloud";
    string ext = ".pcd";
    string filename;

vector < PointCloud<PointXYZ>::Ptr, Eigen::aligned_allocator <PointCloud <PointXYZ>::Ptr > > sourceClouds;

	for (int i=2; i<7 ; i++)
	{

 	    stringstream ss;
		ss << i;

		filename = st+ st1 + ss.str() +ext;
		PointCloud<PointXYZ>::Ptr sourceCloud(new PointCloud<PointXYZ>);
      	io::loadPCDFile (filename, *sourceCloud );	
		sourceClouds.push_back(sourceCloud);

					
	}
/*
vector < PointCloud<PointXYZ>::Ptr, Eigen::aligned_allocator <PointCloud <PointXYZ>::Ptr > > filteredClouds;
pcl::PassThrough<pcl::PointXYZ> pass;	
	for (int i=0; i < sourceClouds.size() -1 ; i++)
	{
			PointCloud<PointXYZ>::Ptr filteredCloud(new PointCloud<PointXYZ>);
			pass.setInputCloud(sourceClouds[i]);
			pass.filter(*filteredCloud);
			filteredClouds.push_back(filteredCloud);
	}
*/
     std::vector<int> indices;
	for (int i=0; i < sourceClouds.size() -1 ; i++) //change to filter
	{
 
      pcl::removeNaNFromPointCloud(*sourceClouds[i],*sourceClouds[i], indices);
	}

    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
	for (int i=0; i < sourceClouds.size() -1 ; i++)
	{
	icp.setInputSource(sourceClouds[i]);
    icp.setInputTarget(sourceClouds[i+1]);
	pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);
	//cout << "Transform : "<< i << " and " << i+1 << endl << icp.getFinalTransformation()<< endl;
	Eigen::Matrix4f transformation = icp.getFinalTransformation ();

	std::ostringstream ss;
	ss << "cloud" << i+3 << ".txt";
	string filename = ss.str();
	ofstream myfile;
	myfile.open (filename.c_str(), std::ofstream::out | std::ofstream::app);
	myfile << icp.getFinalTransformation();
	myfile.close();
    }
/* 
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
