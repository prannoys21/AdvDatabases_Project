#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

// Header file for SpatialIndexInterface
#include "../integration/spatial-index-interface.h"
// to store queries results
#include <vector>
// just for output
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

#include <boost/foreach.hpp>
using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 2, bg::cs::cartesian> boostpoint;
typedef bg::model::box<boostpoint> boostbox;
typedef std::pair<boostbox, unsigned> boostvalue;

class PointDataIndex{
	private:
		bgi::rtree< boostpoint, bgi::linear<16> > rtreeObj;
	
	
	public:
		PointDataIndex() {}
    	
    	void createIndex(PointCollection points){
        	
			
			vector<Point> p;
			int sizeOfColl = points.getSize();
			vector<boostpoint> packedPoints;
			
			for(int k=0;k<sizeOfColl;k++){
				p = points.getNext();
			
				for(int i=0;i<p.size();i++){
				vector<float> vect;
				
				vect = p.at(i).getCoordinates();
				packedPoints.push_back(boostpoint(vect.at(0),vect.at(1)));

				}
			
			}

			bgi::rtree< boostpoint, bgi::linear<16> > rtreeinst(packedPoints);
			
			cout<<"##################################"<<endl<<endl;
			cout<<"Indexed "<<rtreeinst.size()<<" points"<<endl;
			rtreeObj = rtreeinst;
			
		
		}
		bool deleteIndex(){
			rtreeObj.clear();
			return true;
		}
		PointCollection searchPoint(Rectangle r){
			
			std::vector<boostpoint> query_result;

			vector<float> vect = r.getCoordinates();

			
			rtreeObj.query(bgi::intersects(boostbox(boostpoint(vect.at(0),vect.at(1)),boostpoint(vect.at(2),vect.at(3)))), std::back_inserter(query_result));
			float x1,y1;
			vector<Point> returning;
   
			PointCollection *result=new PointCollection();

			cout<<query_result.size()<<endl;
			for(int x=0;x<query_result.size();x++){
				x1 = query_result.at(x).get<0>();
				y1 = query_result.at(x).get<1>();
				
							
				Point temp(x1,y1);

				result->insert(temp);

			}

			return *result;
		}
		
		bool update(PointCollection points){
			bool r = deleteIndex();
			createIndex(points);
			return r;
		}
		
};

/////////////////////////////////////////////////////

class RectangleDataIndex{

	private:
		bgi::rtree< boostvalue, bgi::quadratic<16> > rtreeObj;
	
	
	public:
		RectangleDataIndex(){
		}
		
		
		void createIndex(RectangleCollection rects){
			
			
			
			vector<Rectangle> r;
			//if(rects!=NULL)
			vector<boostvalue> packedRectangles;
			
			int sizeOfColl = rects.getSize();
			int id=0;
			for(int k=0;k<sizeOfColl;k++){

				r = rects.getNext();
			
				for(int i=0;i<r.size();i++){
					vector<float> vect;
				
					vect = r.at(i).getCoordinates();
				
					boostbox b(boostpoint(vect.at(0), vect.at(1)), boostpoint(vect.at(2),vect.at(3)));
					packedRectangles.push_back(std::make_pair(b,id));
					
        			id++;	
				
				}

			}
			
			bgi::rtree< boostvalue, bgi::quadratic<16> > rtreeinst(packedRectangles);
			
				
			cout<<"##################################"<<endl<<endl;
			cout<<"Inserted "<<rtreeinst.size()<<" rectangles in R tree"<<endl;
			rtreeObj = rtreeinst;
			
		}
		
		bool deleteIndex(){
			rtreeObj.clear();
			return true;
		}
		
		
		RectangleCollection searchRectangle(Rectangle r){
			
			//RectangleCollection rc;
			vector<float> vect = r.getCoordinates();
			
			std::vector<boostvalue> result_s;
    		rtreeObj.query(bgi::overlaps(boostbox(boostpoint(vect.at(0),vect.at(1)),boostpoint(vect.at(2),vect.at(3)))), std::back_inserter(result_s));

    		std::vector<Rectangle> rects;

			std::vector<boostvalue> result_covered;
			

			rtreeObj.query(bgi::covered_by(boostbox(boostpoint(vect.at(0),vect.at(1)),boostpoint(vect.at(2),vect.at(3)))), std::back_inserter(result_covered));

			std::vector<boostvalue> resultfinal;
			
			int first=0,second=0;

			while(first<result_s.size() && second<result_covered.size()){


				boostvalue b1 = result_s.at(first);
				boostvalue b2= result_covered.at(second);
				if(b1.second<b2.second){

					resultfinal.push_back(b1);
					first++;

				}
				else if(b2.second<b1.second){
					resultfinal.push_back(b2);
					second++;
				}
				else{
					resultfinal.push_back(b1);
					first++;
					second++;
				}


			}

			while(first<result_s.size()){

				boostvalue b1 = result_s.at(first);
				
				resultfinal.push_back(b1);
					first++;

			}
			while(second<result_covered.size()){

				boostvalue b2= result_covered.at(second);

				resultfinal.push_back(b2);
					second++;

			}
	
    		RectangleCollection *result=new RectangleCollection();
	
			
    		BOOST_FOREACH(boostvalue const& v, resultfinal){
				float x1 = bg::get<bg::min_corner,0>(v.first); 
    			float y1 = bg::get<bg::min_corner,1>(v.first);
    			float x2 = v.first.max_corner().get<0>();
    			float y2 = v.first.max_corner().get<1>();
    		
    			Rectangle temp(x1,y1,x2,y2);
				rects.push_back(temp);

				result->insert(temp);

			}


			return *result;
		}
		
		bool update(RectangleCollection rects){
			bool r = deleteIndex();
			createIndex(rects);
			return r;
		}

};
