#ifndef Edge_Detection_H
#define Edge_Detection_H



#include <pcl/common/time.h>
#include <pcl/features/integral_image_normal.h>
#include "organized_edge_detection.h"
#include <pcl/io/io.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZRGBA PointT;

class OpenNIOrganizedEdgeDetection
{
  private:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    pcl::PointCloud<PointT> cloud_;
    boost::mutex cloud_mutex;

  public:
    OpenNIOrganizedEdgeDetection ()
      : viewer (new pcl::visualization::PCLVisualizer ("PCL Organized Edge Detection"))
    {

    }
    ~OpenNIOrganizedEdgeDetection ()
    {
    }

    boost::shared_ptr<pcl::visualization::PCLVisualizer>
    initCloudViewer (pcl::PointCloud<PointT>::ConstPtr cloud)
    {
      viewer->setSize (640, 480);
      viewer->addPointCloud<PointT> (cloud, "cloud");
      viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
      //viewer->addCoordinateSystem (0.2f, "global");
      viewer->initCameraParameters ();
      viewer->registerKeyboardCallback (&OpenNIOrganizedEdgeDetection::keyboard_callback, *this);
      viewer->resetCameraViewpoint ("cloud");


      return (viewer);
    }

    void
    keyboard_callback (const pcl::visualization::KeyboardEvent& event, void*)
    {
      double opacity;
      if (event.keyUp())
      {

      }
    }

    void
    cloud_cb_ (const pcl::PointCloud<PointT>::ConstPtr& cloud)
    {
      if (!viewer->wasStopped ())
      {
        cloud_mutex.lock ();
        cloud_ = *cloud;
        cloud_mutex.unlock ();
      }
    }

    void
    run ()
    {
      pcl::Grabber* interface = new pcl::OpenNIGrabber ();

      boost::function<void(const pcl::PointCloud<PointT>::ConstPtr&)> f = boost::bind (&OpenNIOrganizedEdgeDetection::cloud_cb_, this, _1);

      // Make and initialize a cloud viewer
      pcl::PointCloud<PointT>::Ptr init_cloud_ptr (new pcl::PointCloud<PointT>);
      viewer = initCloudViewer (init_cloud_ptr);
      boost::signals2::connection c = interface->registerCallback (f);

      interface->start ();

      //pcl::IntegralImageNormalEstimation<PointT, pcl::Normal> ne;
      //ne.setNormalEstimationMethod (ne.COVARIANCE_MATRIX);
      //ne.setNormalSmoothingSize (10.0f);
      //ne.setBorderPolicy (ne.BORDER_POLICY_MIRROR);

      //float th_dd = 0.04f;
      //int max_search = 100;
      //pcl::OrganizedEdgeFromRGBNormals<PointT, pcl::Normal, pcl::Label> oed;
      //oed.setDepthDisconThreshold (th_dd);
      //oed.setMaxSearchNeighbors (max_search);

      //oed.setEdgeType (oed.EDGELABEL_NAN_BOUNDARY | oed.EDGELABEL_OCCLUDING | oed.EDGELABEL_OCCLUDED);
      //oed.setEdgeType (oed.EDGELABEL_NAN_BOUNDARY | oed.EDGELABEL_OCCLUDING | oed.EDGELABEL_OCCLUDED | oed.EDGELABEL_HIGH_CURVATURE | oed.EDGELABEL_RGB_CANNY);

      //pcl::PointCloud<pcl::Label> labels;
      //std::vector<pcl::PointIndices> label_indices;

      while (!viewer->wasStopped ())
      {
        viewer->spinOnce ();

        if (cloud_mutex.try_lock ())
        {
          //labels.clear ();
          //label_indices.clear ();
          
          //double normal_start = pcl::getTime ();

          //if (oed.getEdgeType () & oed.EDGELABEL_HIGH_CURVATURE)
          //{
            //pcl::PointCloud<pcl::Normal>::Ptr normal_cloud (new pcl::PointCloud<pcl::Normal>);
            //ne.setInputCloud (cloud_.makeShared ());
            //ne.compute (*normal_cloud);
            //double normal_end = pcl::getTime ();
            //std::cout << "Normal Estimation took " << double (normal_end - normal_start) << std::endl;

            //oed.setInputNormals (normal_cloud);
          //}

          //double oed_start = pcl::getTime ();

          //oed.setInputCloud (cloud_.makeShared ());
          //oed.compute (labels, label_indices);

          //double oed_end = pcl::getTime ();


          // Make gray point cloud
         // for (size_t idx = 0; idx < cloud_.points.size (); idx++)
         // {
          //  pcl::uint8_t gray = pcl::uint8_t((cloud_.points[idx].r + cloud_.points[idx].g + cloud_.points[idx].b)/3);
          //  cloud_.points[idx].r = cloud_.points[idx].g = cloud_.points[idx].b = gray;
          //}

          // Show the gray point cloud
          if (!viewer->updatePointCloud (cloud_.makeShared (), "cloud"))
            viewer->addPointCloud (cloud_.makeShared (), "cloud");

          // Show edges
          //pcl::PointCloud<PointT>::Ptr occluding_edges (new pcl::PointCloud<PointT>), 
            //occluded_edges (new pcl::PointCloud<PointT>), 
            //nan_boundary_edges (new pcl::PointCloud<PointT>),
            //high_curvature_edges (new pcl::PointCloud<PointT>),
            //rgb_edges (new pcl::PointCloud<PointT>);

          //pcl::copyPointCloud (cloud_, label_indices[0].indices, *nan_boundary_edges);
          //pcl::copyPointCloud (cloud_, label_indices[1].indices, *occluding_edges);
          //pcl::copyPointCloud (cloud_, label_indices[2].indices, *occluded_edges);
          //pcl::copyPointCloud (cloud_, label_indices[3].indices, *high_curvature_edges);
          //pcl::copyPointCloud (cloud_, label_indices[4].indices, *rgb_edges);


          cloud_mutex.unlock ();
        }
      }

      interface->stop ();
    }
};

#endif

