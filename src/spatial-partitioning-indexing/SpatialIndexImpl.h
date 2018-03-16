//
// Created by Darshan Shetty on 31-03-2017.
//

#ifndef IN_MEMORY_SPATIAL_DB_SPATIALINDEXIMPL_H
#define IN_MEMORY_SPATIAL_DB_SPATIALINDEXIMPL_H

//Change this to point to the one in Integration team codebase
#include "../integration/spatial-index-interface.h"
#include "PointSpatialIndex.h"
#include "RectangleSpatialIndex.h"

class SpatialIndexImpl: public  SpatialIndexInterface {
private:
    PointSpatialIndex *pointIndex;
    RectangleSpatialIndex *rectangleIndex;
    bool isPointIndex = false;
public:
    PointCollection searchPoint(Rectangle rectangle,PointCollection *pointCollection)  {
        if(pointIndex != NULL) {
            return pointIndex->searchPoint(rectangle, pointCollection);
        }
        throw "Error performing Point search operation. Check error logs";
    }

    RectangleCollection searchRectangle(Rectangle rectangle, RectangleCollection *rectangleCollection)  {
        if(rectangleIndex != NULL) {
            return rectangleIndex->searchRectangle(rectangle,rectangleCollection);
        }
        throw "Error performing Rectangle search operation. Check error logs";
    }

    void createIndex(PointCollection collection)  {
        pointIndex = new PointSpatialIndex();
        pointIndex->createIndex(collection);
        isPointIndex = true;
    }

    void createIndex(RectangleCollection collection)  {
        rectangleIndex = new RectangleSpatialIndex();
        rectangleIndex->createIndex(collection);
    }

    bool update(PointCollection collection)  {
        if(pointIndex != NULL) {
            return pointIndex->update(collection);
        }
        return false;
    }

    bool update(RectangleCollection collection)  {
        if(rectangleIndex != NULL) {
            return rectangleIndex->update(collection);
        }
        return false;
    }

    bool deleteIndex()  {
        bool status = false;
        if(isPointIndex && pointIndex != NULL) {
            status = pointIndex->deleteIndex();
            delete pointIndex;
            isPointIndex = false;
            pointIndex = NULL;
        }else if(rectangleIndex != NULL) {
            status = rectangleIndex->deleteIndex();
            delete rectangleIndex;
            rectangleIndex = NULL;
        }
        return status;
    }
};
#endif //IN_MEMORY_SPATIAL_DB_SPATIALINDEXIMPL_H
