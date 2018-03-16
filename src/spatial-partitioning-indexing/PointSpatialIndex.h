//
// Created by Darshan Shetty on 19-03-2017.
//

#ifndef IN_MEMORY_SPATIAL_DB_POINTSPATIALINDEX_H
#define IN_MEMORY_SPATIAL_DB_POINTSPATIALINDEX_H

#include "quadTreeLib.h"
#include "prQuadTree.h"
#include "../integration/spatial-index-interface.h"
#include "qPoint.h"

class PointSpatialIndex: public  SpatialIndexInterface {
private:
    prQuadTree *prTree;
    qPoint* convertPoint(Point p) {
        return new qPoint(p.getCoordinates()[0],p.getCoordinates()[1],p.getId());
    }
public:
    PointSpatialIndex() {}
    PointCollection searchPoint(Rectangle bounds, PointCollection *pointCollection){
        PointCollection *result = new PointCollection();
        float x1 = bounds.getCoordinates()[0];
        float y1 = bounds.getCoordinates()[1];
        float x2 = bounds.getCoordinates()[2];
        float y2 = bounds.getCoordinates()[3];
        bool xResult = (x1 - x2) > ((fabs(x1) < fabs(x2) ? fabs(x2) : fabs(x1)) * numeric_limits<double>::epsilon());
        float minx = xResult ? x2 : x1;
        bool yResult = (y1 - y2) > ((fabs(y1) < fabs(y2) ? fabs(y2) : fabs(y1)) * numeric_limits<double>::epsilon());
        float miny = yResult ? y2 : y1;
        float width = fabs(x2-x1);
        float height = fabs(y2-y1);
        vector<qPoint>iPoints = prTree->queryRange(minx,miny,width,height);
        vector<Point> points;
        int i=0;
        for(qPoint point : iPoints) {
            //points.push_back(pointCollection->getById(point.getId()));
            result->insert(pointCollection->getById(point.getId()));
        }
        //result = new PointCollection("PointIndexCollection","Point",TYPE_POINT,points);
        if(!points.empty()){
            points.clear();
        }
        if(!iPoints.empty()){
            iPoints.clear();
        }
        return *result;
    }
    RectangleCollection searchRectangle(Rectangle,RectangleCollection*){
        throw "Method Not Supported";
    }
    void createIndex(PointCollection points){
        vector<Point> allPoints = points.getNext(points.getSize());
        vector<qPoint*> qPoints;
        for (std::vector<Point>::iterator point = allPoints.begin() ; point != allPoints.end(); ++point){
            qPoints.push_back(convertPoint(*point));
        }
        qBoundingBox *box = qBoundingBox::getQBoundingBoxCooridinates(qPoints);
        prTree = new prQuadTree(box,8);
        vector<Point> pointVector = points.getNext(points.getSize());
        for (std::vector<Point>::iterator point = pointVector.begin() ; point != pointVector.end(); ++point)
            prTree->insert(convertPoint(*point));
    }
    void createIndex(RectangleCollection){
        throw "Method Not Supported";
    }
    bool update(PointCollection points){
        bool result = true;
        try {
            prTree->deleteRoot();
            createIndex(points);
        } catch( const char *msg) {
            result = false;
        }
        return result;
    }
    bool update(RectangleCollection){
        throw "Method Not Supported";
    }
    bool deleteIndex(){
        bool result = true;
        try {

            prTree->deleteRoot();

        } catch(const char *msg){
            result = false;
        }
        return result;
    }
};
#endif //IN_MEMORY_SPATIAL_DB_POINTSPATIALINDEX_H