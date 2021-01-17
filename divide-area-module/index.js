const testAddon = require('./build/Debug/DividePolygon.node');

var obj = testAddon.Polygon();

obj.addPoint(-105.92465373906462, 37.624575781768556);
obj.addPoint(-105.24117845203885, 45.43920852350181);
obj.addPoint(-90.21720732039695, 41.24645826853556);
obj.addPoint(-93.8100911247011, 31.239422199367638);

let simpleCheck = obj.checkSimple();

let convexityCheck = obj.checkConvex();

console.log(simpleCheck);
console.log(convexityCheck);

console.log(obj.dividePolygon(3));

let longestSideBisector = obj.longestSideBisector();

console.log(longestSideBisector.LengthOfBisector);
console.log(longestSideBisector);

module.exports = testAddon;