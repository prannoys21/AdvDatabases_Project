# Spatial Indexing

## PR Quad Tree and MX-CIF Quad Tree

You can find usage details of interfaces available for Spatial Data Indexing in this document.
There are two indexes constructed that extend SpatialIndexInterface. - 

* PointSpatialIndex
	* Uses Point Region Quadtree to index data from the Point table
* RectangleSpatialIndex 
	* Uses MX-CIF Quadtree to index data from the Rectangle table.
* SpatialIndexImpl
    * A wrapper class for Point, Rectangle Index that user would interact with

## Notes:

### Rectangles Intersect Logic

* According to the present scenario, if 2 rectangles touch each other then we should return it as part of the search operation. 
	* But in this case we will have to check all the rectangles that touch a given rectangle. This operation consumes a lot of time as in some cases we may have to check all the rectangles.
	* We are still working on efficiently solving this problem and in the process we may have to have multiple discussions with the class and the professor.

* As of now our spatial indexing for rectangle returns only those rectangles if it is completely inside the given rectangle.
	* Our implementation of spatial indexing for rectangles work for majority of the test cases, however output of few test cases are not as expected. 
	* We are working on these test cases and we will be pushing the changes shortly.

### Images for reference:

Figure 1: Bounding Box Structure 
![Bounding Box Structure](https://github.com/nakulchawla09/advances-quadtree/blob/master/new/advdbSpatialTest/Test/Images/BoundingBoxStructure.png)

Figure 2: Structure of Quadtree Node
![Structure of Quadtree Node](https://github.com/nakulchawla09/advances-quadtree/blob/master/new/advdbSpatialTest/Test/Images/StructureOfQuadtreeNode.png)

Figure 3: Points Visualization in PR Quadtree
![Points Visualization in Quadtree](https://github.com/nakulchawla09/advances-quadtree/blob/master/new/advdbSpatialTest/Test/Images/TestCase1PointsVisualization.png)

Figure 4: Insertion of Points Visualization in PR Quadtree for Classical Algorithm
![Insertion of Points Visualization in PR Quadtree for Classical Algorithm](https://github.com/magic679/In-Memory-Spatial-DB/blob/spatial-indexing-dev/src/spatial-partitioning-indexing/spatialTests/Images/report-pr-1-samat.png)

Figure 5: Insertion of Points Visualization in PR Quadtree for Modified Algorithm
![Insertion of Points Visualization in PR Quadtree for Modified Algorithm](https://github.com/magic679/In-Memory-Spatial-DB/blob/spatial-indexing-dev/src/spatial-partitioning-indexing/spatialTests/Images/report-pr-1.png)

Figure 6: Rectangles Visualization in MXCIF Quadtree
![Rectangles Visualization in Quadtree](https://github.com/nakulchawla09/advances-quadtree/blob/master/new/advdbSpatialTest/Test/Images/TestCaseRectangulesVisualization.png)

Figure 7: Insertion of Rectangles Visualization in MXCIF Quadtree for Classical Algorithm
![Insertion of Rectangles Visualization in MXCIF Quadtree for Classical Algorithm](https://github.com/magic679/In-Memory-Spatial-DB/blob/spatial-indexing-dev/src/spatial-partitioning-indexing/spatialTests/Images/report-mxcif-1-samat.png)

Figure 8: Insertion of Rectangles Visualization in MXCIF Quadtree for Modified Algorithm
![Insertion of Rectangles Visualization in MXCIF Quadtree for Modified Algorithm](https://github.com/magic679/In-Memory-Spatial-DB/blob/spatial-indexing-dev/src/spatial-partitioning-indexing/spatialTests/Images/report-mxcif-1.png)

Figure 9: Results for Cache Conscious PR Quad Tree
![Results for Cache Conscious PR Quad Tree](https://github.com/magic679/In-Memory-Spatial-DB/blob/spatial-indexing-dev/src/spatial-partitioning-indexing/spatialTests/Images/report-pr-memory.png)

Figure 10: Results for Cache Conscious MXCIF Quad Tree
![Results for Cache Conscious MXCIF Quad Tree](https://github.com/magic679/In-Memory-Spatial-DB/blob/spatial-indexing-dev/src/spatial-partitioning-indexing/spatialTests/Images/report-mxcif-memory.png)



## Instructions to run
This code was designed to be run as a module inside an object-oriented Spatial database that handled Points and Rectangles, required search to be done in compliance with SpatialIndexInterface.

However, this code can also be run as an individual module, which we have done for our testing purposes as well. 
The following command builds our module with the dependent interfaces. It should be executed in the In-Memory-Spatial-DB folder. We have tested this on a Windows 7 machine using g++ compiler version 6.1.0.

`g++ -std=c++0x src/spatial-partitioning-indexing/spatialIndexingRectTest.cpp src/integration/catalog.cpp src/data-storage/data-storage.cpp src/integration/geometry.cpp`

This will generate the execute `a.out` containing our test cases for RectangleSpatialIndex. By including `src/spatial-partitioning-indexing/spatialIndexingPointTest.cpp` instead of `src/spatial-partitioning-indexing/spatialIndexingRectTest.cpp`, the executable would contain tests for PointSpatialIndex. Please refer to these test files to understand how our indexing module can be integrated into your implementation.

## Function Definition

### SpatialIndexImpl contains the following functions:
`PointCollection search(Rectangle bounds, PointCollection *points)`

>Search the query rectangle provided and return all points satisfying the query

>>Input Paramaters
>>>bounds - Diagonal Coordinates of the query rectangle. Assumes that the getCoordinates function returns (x1,y1) and (x2,y2) in order
>>>points - Reference to the points present in database

>> Returns
>>> PointCollection - Collection of points satisfying the query


---		

`RectangleCollection searchRectangle(Rectangle bounds, RectangleCollection *rectangles)`
>Search the query rectangle provided and return all rectangles satisfying the query

>>Input Paramters
>>>bounds - Diagonal Coordinates of the query rectangle. Assumes that the getCoordinates function returns (x1,y1) and (x2,y2) in order
>>>rectangles - Reference to the rectangles present in database

>>Returns
>>>RectangleCollection - Collection of rectangles satisfying the query

---	

`void createIndex(PointCollection points)`

>Creates Point Spatial Data Index for the given set of points

>>Input Paramters
>>>points - Collection of points to be indexed

>>Returns
>>>void

---	

`void createIndex(RectangleCollection rectangles)`

>Creates Rectangle Spatial Data Index for the given set of rectangles

>>Input Paramters
>>>rectangles - Collection of rectangles to be indexed

>>Returns
>>>void

---

`bool update(PointCollection points)`

>Updates the Point Spatial Data index created. This method deletes existing index structure and constructs it for given set of points

>>Input Paramters
>>>points - Collection of points to be indexed

>>Returns
>>>bool - sucess status of the update operation

---	
	
`bool update(RectangleCollection rectangles)`
>Updates the Rectangle Spatial Data index created. This method deletes existing index structure and constructs it for given set of rectangles

>>Input Paramters
>>>rectangles - Collection of rectangles to be indexed
>>Returns
>>>bool - sucess status of the update operation

---	

`bool deleteIndex()`

>Deletes index structure for Point Spatial data
>>Returns
>>>bool - success status of the delete operation

---		
