const testAddon = require('./build/Debug/DividePolygon.node');

var obj = testAddon.Polygon();

obj.addPoint(10.5323543, 20.1233434);

console.log(testAddon.Polygon());

module.exports = testAddon;