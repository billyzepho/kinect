#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/bilateral.h>
#include <iterator>
#include <boost/filesystem.hpp>
#include <boost/iterator/filter_iterator.hpp>
namespace fs = boost::filesystem;
using namespace std; 
using namespace pcl;

int main (int argc, char** argv)
{

    string st = "clouds1512/";
    string st1 = "cloud";
    string ext = ".pcd";
    string filename;

vector < PointCloud<PointXYZ>::Ptr, Eigen::aligned_allocator <PointCloud <PointXYZ>::Ptr > > sourceClouds;

	for (int i=1; i<251 ; i++)
	{

 	    stringstream ss;
		ss << i;

		filename = st+ st1 + ss.str() +ext;
		PointCloud<PointXYZ>::Ptr sourceCloud(new PointCloud<PointXYZ>);
      	io::loadPCDFile (filename, *sourceCloud );	
		sourceClouds.push_back(sourceCloud);

					
	}


     std::vector<int> indices;
	for (int i=0; i < sourceClouds.size() -1 ; i++) //change to filter
	{
 
      pcl::removeNaNFromPointCloud(*sourceClouds[i],*sourceClouds[i], indices);
	}

    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
	Eigen::Matrix4f temp = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();
	
	for (int i=0; i < sourceClouds.size() -1 ; i++)
	{
	icp.setInputSource(sourceClouds[i]);
    icp.setInputTarget(sourceClouds[i+1]);
	pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);
	//cout << "Transform : "<< i << " and " << i+1 << endl << icp.getFinalTransformation()<< endl;
	transformation = temp * icp.getFinalTransformation ();
	temp = transformation;
	std::ostringstream ss;
	ss << "cloud" << i+2 << ".txt";
	string filename = ss.str();
	ofstream myfile;
	myfile.open (filename.c_str(), std::ofstream::out | std::ofstream::app);
	myfile << transformation;
	myfile.close();
    }

	std::ostringstream sl;
	sl << "cloud" << 1 << ".txt";
	string filenamel = sl.str();
	ofstream myfilel;
	myfilel.open (filenamel.c_str(), std::ofstream::out | std::ofstream::app);
	myfilel << Eigen::Matrix4f::Identity();
	myfilel.close();


    return 0;
}
