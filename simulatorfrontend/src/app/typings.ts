import { PolygonEditorObservable } from 'angular-cesium';

export type Area = {name: string, points: Point[], selected: boolean};

export type Point = {x: Coordinate, y: Coordinate};

export type Coordinate = number;