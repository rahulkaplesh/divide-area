declare var require: any

const myaddon = require('node-loader!./build/Release/DividePolygon.node')

export interface Polygon {
    myMethod(arg: string): number
}

export var Polygon: {
    new(): Polygon
} = myaddon.Polygon