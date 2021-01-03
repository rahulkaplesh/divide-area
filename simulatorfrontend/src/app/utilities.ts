import { Cartesian3 } from 'angular-cesium';
import { Cartographic } from 'cesium';
import { Point } from './typings';

export function convertCartesianPointsToDegrees(cartesianPoints: Cartesian3[]): Point[] {
  let points: Point[] = [];
  cartesianPoints.map((cartesianPoint) => {
    let pos: Cartographic = Cesium.Cartographic.fromCartesian(cartesianPoint);
    points.push({x: (pos.longitude / Math.PI * 180), y: (pos.latitude / Math.PI * 180)});
  })
  return points;
}

export function convertDegreesToCartesianPoints(points: Point[]): Cartesian3[] {
  let cartesians: Cartesian3[] = [];
  points.map((point) => {
    let cartesian: Cartesian3 = Cesium.Cartesian3.fromDegrees(point.x, point.y);
    cartesians.push(cartesian);
  })
  return cartesians;
}