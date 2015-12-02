#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/passthrough.h>

//using namespace std; 


int 
main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile ("../icpclouds/cloud1.pcd", *cloud1);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile ("../icpclouds/cloud5.pcd", *cloud2);

pcl::PointCloud<pcl::PointXYZ>::Ptr outputcloud1 (new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr outputcloud2 (new pcl::PointCloud<pcl::PointXYZ>);
pcl::PassThrough<pcl::PointXYZ> pass; // can do this without parameters
pass.setInputCloud(cloud1);
pass.filter(*outputcloud1);
pass.setInputCloud(cloud2);
pass.filter(*outputcloud2);
    
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(outputcloud1);
    icp.setInputTarget(outputcloud2);
    pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);
    std::cout << "has converged:" << icp.hasConverged() << " score: " <<
    icp.getFitnessScore() << std::endl;
    std::cout << icp.getFinalTransformation() << std::endl;

    return 0;
}
