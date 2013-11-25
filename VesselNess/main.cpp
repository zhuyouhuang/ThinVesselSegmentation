// VesselNess.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_DEPRECATE

#include "stdafx.h"
#include "VesselDetector.h"
#include "Validation.h"
#include "Kernel3D.h"
#include "Viewer.h"
#include "RingsDeduction.h"
#include "Image3D.h"
#include "ImageProcessing.h"
#include "Vesselness.h"

#include "MinSpanTree.h"

#include "GLViewer.h"
#include "GLViewerExt.h"
#include "GLViwerWrapper.h"



void plot_histogram_in_matlab(void) {
	smart_assert( 0, "Deprecated!" );
	//cout << "Plotting Histogram of data in Matlab. " << endl;
	//// loading data
	//Image3D<short> im_data;
	//bool flag = im_data.loadData( "data/vessel3d.data", Vec3i(585,525,200), true, true );
	//if( !flag ) return;
	//// calculating histogram
	//Mat_<double> hist, range;
	//IP::histogram( im_data, range, hist, 1024 );
	//MLVier::plot( range, hist );
}



void compute_vesselness(void){
	Image3D<short> image_data;

	string data_name = "data15";

	bool flag = image_data.load( "data/"+data_name+".data" );
	if( !flag ) return;
	
	Data3D<Vesselness> vn;
	VD::compute_vesselness( image_data.getROI(), vn, 
		/*sigma from*/ 0.5f,
		/*sigma to*/   3.5f,
		/*sigma step*/ 1.5f );
	
	string vn_name = "output/" + data_name + ".float4.vesselness";
	vn.save( "output/" + data_name + ".res.vesselness" );
	Viewer::MIP::Multi_Channels( vn, vn_name );
} 

void compute_vesselness_whole_data(void){
	// laoding data
	Data3D<short> im_short;
	bool falg = im_short.load( "data/vessel3d.data" );
	if(!falg) return;
	
	// compute vesselness
	Data3D<Vesselness_All> vn_all;
	vn_all.resize( im_short.get_size() );
	VD::compute_vesselness( im_short, vn_all, 
		/*sigma from*/ 0.5f,
		/*sigma to*/   5.5f,
		/*sigma step*/ 1.0f );
	vn_all.save( "data/vessel3d.5.vn_all" );

	Data3D<Vesselness_Sig> vn_sig( vn_all );
	vn_sig.save( "data/vessel3d.5.vn_sig" );

	Data3D<float> vn_float; 
	vn_sig.copyDimTo( vn_float, 0 );
	vn_float.save( "data/vessel3d.5.vn_float" );
	
	GLViewer::MIP( vn_float );
}


void compute_min_span_tree(void) {
	Image3D<short> image_data;
	bool falg = image_data.load( "data/roi16.partial.data" );
	if( !falg ) return;

	Image3D<unsigned char> image_data_uchar;
	IP::normalize( image_data.getROI(), short(255) );
	image_data.getROI().convertTo( image_data_uchar );
	
	// Computer Min Span Tree
	Graph< MST::Edge_Ext, MST::LineSegment > tree;
	MinSpanTree::build_tree_xuefeng( "data/roi16.partial.linedata.txt", tree, 15000 );
	// Visualize Min Span Tree on Max Intensity Projection
	GLViewerExt::draw_min_span_tree_init( tree );
	GLViewerExt::save_video_int( "output/video.avi", 20, 18 );
	GLViewer::MIP( image_data_uchar.getROI().getMat().data, 
		image_data_uchar.SX(),
		image_data_uchar.SY(),
		image_data_uchar.SZ(), 
		GLViewerExt::draw_min_span_tree, // drawing min span tree
		NULL );                             // NOT saving video
		// GLViewerExt::save_video );       // saving video

}

void compute_min_span_tree_vesselness(void) {
	Image3D<float> vn;
	Image3D<Vesselness_Sig> vn_sig;

	vn_sig.load( "data/roi16.partial.float5.vesselness" );
	vn_sig.copyDimTo( vn, 0 );

	Image3D<unsigned char> image_data_uchar;
	IP::normalize( vn, float(255) );
	vn.getROI().convertTo( image_data_uchar );
	
	// Computer Min Span Tree
	Graph< MST::Edge_Ext, MST::LineSegment > tree;
	MinSpanTree::build_tree_xuefeng( "data/roi16.partial.linedata.txt", tree, 150 );
	// Visualize Min Span Tree on Max Intensity Projection
	GLViewerExt::draw_min_span_tree_init( tree );
	GLViewerExt::save_video_int( "output/video.avi", 20, 18 );
	GLViewer::MIP( image_data_uchar.getROI().getMat().data, 
		image_data_uchar.SX(),
		image_data_uchar.SY(),
		image_data_uchar.SZ(), 
		GLViewerExt::draw_min_span_tree, // drawing min span tree
		NULL );                             // NOT saving video
		// GLViewerExt::save_video );       // saving video

}


//#define _FILE_OFFSET_BITS  64
#include <stdio.h>
#include <Windows.h>

int main(int argc, char* argv[])
{
	compute_vesselness_whole_data();

	return 0;


	/////////////////////////////////////////////////////////////////////////////////////
	//// For tuning parameters
	//flag = image_data.loadROI( ps.file );
	//if( !flag ) return 0;
	//static const int NUM_S = 4;
	//float sigma[] = { 0.3f, 0.5f, 0.7f, 1.5f };
	//// float sigma[] = { 0.5f, 1.5f, 2.5f };
	//int margin = (int) sigma[NUM_S-1]*6 + 20;
	//Vec3i size = image_data.getROI().get_size() - 2* Vec3i(margin, margin, margin);
	//size[0] *= NUM_S;
	//Data3D<Vesselness_All> vn_temp(size);
	//for( int i=0; i<NUM_S; i++ ){ 
	//	VD::compute_vesselness( image_data.getROI(), vn_all, sigma[i], 3.1f, 100.0f );
	//	vn_all.remove_margin( Vec3i(margin+30,margin,margin), Vec3i(margin,margin,margin) );
	//	int x,y,z;
	//	for(z=0;z<vn_all.SZ();z++ ) for(y=0;y<vn_all.SY();y++ ) for(x=0;x<vn_all.SX();x++ ) {
	//		vn_temp.at( x + i*vn_all.SX(), y, z ) = vn_all.at( x, y, z );
	//	}
	//}
	//Viewer::MIP::Multi_Channels( vn_temp, data_name+".vesselness" );
	//return 0;

	//
	//if( bool minimum_spinning_tree = false ) { 	
	//	Data3D<Vesselness_Sig> res_mst;
	//	IP::edge_tracing_mst( vn_all, res_mst, 0.55f, 0.065f  );
	//	// res_dt.save( data_name + ".dir_tracing.vesselness" );
	//	Viewer::MIP::Multi_Channels( res_mst, data_name + ".mst" );
	//	return 0;
	//} else {
	//	Data3D<Vesselness_Sig> res_nms; // result of non-maximum suppression
	//	IP::non_max_suppress( vn_all, res_nms );
	//	res_nms.save( data_name + ".non_max_suppress.vesselness" );
	//	// Viewer::MIP::Multi_Channels( res_nms, data_name + ".non_max_suppress" ); // Visualization using MIP
	//	//return 0;

	//	Data3D<Vesselness_Sig> res_rns_et;
	//	IP::edge_tracing( res_nms, res_rns_et, 0.55f, 0.055f );
	//	res_rns_et.save( data_name + ".edge_tracing.vesselness" );
	//	Viewer::MIP::Multi_Channels( res_rns_et, data_name + ".edge_tracing"); // Visualization using MIP
	//}
	//
	//
	//
	//return 0;

	///////////////////////////////////////////////////////////////
	// Ring Recuction by slice
	////////////////////////////////////////////////////////////////
	////Get a clice of data
	//Mat im_slice = image_data.getByZ( 55 );
	//Mat im_no_ring;
	//for( int i=0; i<5; i++ ) {
	//	Validation::Rings_Reduction_Polar_Coordinates( im_slice, im_no_ring, 9 );
	//	im_slice = im_no_ring;
	//}

	////////////////////////////////////////////////////////////////
	// Plotting About Eigenvalues
	////////////////////////////////////////////////////////////////
	//// Visualization of the Eigenvalues
	// Validation::Eigenvalues::plot_1d_box();
	// Validation::Eigenvalues::plot_2d_tubes();
	// Validation::Eigenvalues::plot_2d_ball();
	// Validation::Eigenvalues::plot_3d_tubes();
	// Validation::BallFittingModels::cylinder();
	
	//// Draw Second Derivative of Gaussian on top of the Box function 
	// Validation::box_func_and_2nd_gaussian::plot_different_size();
	// Validation::box_func_and_2nd_gaussian::plot_different_pos();

	return 0;
}
