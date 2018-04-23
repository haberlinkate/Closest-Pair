#ifndef PROGRAM2_H
#define PROGRAM2_H

#include "metrics.h"
#include <algorithm>
#include <cmath>

template <typename T>
std::pair<Point<T>, Point<T> > closestPair( vector<Point<T> > v){

  int size = v.size();

  //If size is less than 3, return brute force pair
  if(size <= 3)
  {
    return closestPairBF(v);
  }

  //Otherwise use efficient algorithm
  else
  {
    //Sort increasing on x
    vector<Point<T>> sX = sortOnX(v);

    //Find middle index mid using ceiling
    int mid;
    if(size%2 == 0)
      mid = size/2;
    else
      mid = (size/2) + 1;

    //Find middle value m
    T m = sX[mid].x;

    //Split vector in half
    vector<Point<T>> lX, rX;
    for(int i = 0; i < mid; i++)
      lX.push_back(sX[i]);
    for(int i = mid + 1; i < size; i++)
      rX.push_back(sX[i]);

    //Recursively find closest paris left and right subsets
    std::pair<Point<T>, Point<T>> pl = closestPair(lX);
    std::pair<Point<T>, Point<T>> pr = closestPair(rX);

    //Set d to minimum distance
    T dl = dist(pl.first, pl.second);
    T dr = dist(pr.first, pr.second);
    T d = std::min(dl, dr);

    //Update closest pair
    if(d = dl)
    {
      v[0] = pl.first;
      v[1] = pl.second;
    }
    else
    {
      v[0] = pr.first;
      v[1] = pr.second;
    }


    //If point is within +- d from m, store in new vector
    vector<Point<T>> sY;
    for(int i = 0; i < size; i ++)
    {
      if(abs(sX[i].x - m) < d)
      {
        sY.push_back(sX[i]);
      }
    }
    sY = sortOnY(sY);

    //For each point in sY, see if points are closer than dsq
    T dsq = d * d;
    for(int i = 0; i < sY.size() - 1; i ++)
    {
      int k = i + 1; 
      while(k <= sY.size() && pow((sY[k].y - sY[i].y), 2) < dsq)
      {
        T nd = dist(sY[k], sY[i]);

        if(nd < dsq)
        {
          dsq = nd;
          v[0] = sY[k];
          v[1] = sY[i];
        }
        k += 1;
      }
    }
  }

  return std::pair<Point<T>, Point<T> > (v[0], v[1]);
 
}

/*Sort in increasing order on the x-coordinates*/
template<typename T>
vector<Point<T>> sortOnX(vector<Point<T>> v)
{
  for(int i = 0; i < v.size(); ++i)
  {
    int smallestIndex = i;

    for(int j = i+1; j < v.size(); ++j)
    {
      if(v.at(smallestIndex).x > v.at(j).x)
        smallestIndex = j;
    }
    
    if(smallestIndex != i)
    {
      Point<T> temp = v.at(i);
      v.at(i) = v.at(smallestIndex);
      v.at(smallestIndex) = temp;
    }
  }
  return v;
}

/*Sort in increasing order on the y-coordinates*/
template <typename T>
vector<Point<T>> sortOnY( vector<Point<T>> v)
{
  for(int i = 0; i < v.size(); ++i)
  {
    int smallestIndex = i;

    for(int j = i+1; j < v.size(); ++j)
    {
      if(v.at(smallestIndex).y > v.at(j).y)
        smallestIndex = j;
    }

    if(smallestIndex != i)
    {
      Point<T> temp = v.at(i);
      v.at(i) = v.at(smallestIndex);
      v.at(smallestIndex) = temp;
    }
  }
  return v;
}

#endif //PROGRAM2_H
